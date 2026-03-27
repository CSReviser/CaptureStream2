/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
	NHK radio language courses.
	CaptureStream2 is a modified version of CaptureStream, originally 
	developed by jakago.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-2.0.html>.
*/

#include "ffmpegrunner.h"

#include <QProcess>
#include <QThread>
#include <QElapsedTimer>
#include <QDir>
#include <QFile>
#include <QUuid>
#include <QRandomGenerator>

FfmpegRunner::FfmpegRunner()
{
}

void FfmpegRunner::setLogCallback(LogCallback cb)
{
    m_logCallback = std::move(cb);
}

void FfmpegRunner::requestCancel()
{
    m_cancelRequested = true;
}

FfmpegRunner::Result FfmpegRunner::run(const FfmpegRunRequest& plan)
{
    Result result;

    if (m_running) {
        result.exitCode = -100;
        return result;
    }

    m_running = true;
    m_cancelRequested = false;

    for (int attempt = 1; attempt <= plan.maxRetry; ++attempt) {

        if (m_cancelRequested) {
            result.canceled = true;
            break;
        }

        QString log;
        int code = runOnce(plan, log);

        result.attempts = attempt;
        result.lastLog = log;
        result.exitCode = code;

        if (code == 0) {
            result.success = true;
            break;
        }

        if (m_cancelRequested) {
            result.canceled = true;
            break;
        }

        if (!shouldRetry(code, log)) {
            break;
        }

        if (attempt < plan.maxRetry) {

            int delay = plan.baseDelayMs * attempt;

            if (code == -3) { // timeout
                delay += plan.baseDelayMs;
            }

            delay += QRandomGenerator::global()->bounded(200);

            if (m_logCallback) {
                m_logCallback(QString("[retry] attempt=%1 delay=%2ms")
                              .arg(attempt)
                              .arg(delay));
            }

            QThread::msleep(delay);
        }
    }

    m_running = false;
    return result;
}

int FfmpegRunner::runOnce(const FfmpegRunRequest& plan, QString& outLog)
{
    QString tempPath = makeTempPath(plan);

    QStringList args = plan.args;
    
    args << tempPath; // Builderが入れてない前提で使う
/*
    if (!args.isEmpty()) {
        args[args.size() - 1] = tempPath;
    }
*/
    QProcess proc;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(plan.program, args);

    if (!proc.waitForStarted()) {
        outLog = "Failed to start ffmpeg";
        return -1;
    }

    QElapsedTimer lastActivity;
    lastActivity.start();


QString cmd = buildCommandString(plan.program, args);

if (m_logCallback) {
    m_logCallback("[ffmpeg cmd] " + cmd);
}

    while (proc.state() == QProcess::Running) {

        if (m_cancelRequested) {
            proc.kill();
            proc.waitForFinished();
            QFile::remove(tempPath);
            return -2;
        }

        if (!proc.waitForReadyRead(100)) {

            if (lastActivity.elapsed() > plan.idleTimeoutMs) {
                proc.kill();
                proc.waitForFinished();
                QFile::remove(tempPath);
                outLog += "\n[timeout]";
                return -3;
            }

            continue;
        }

        QByteArray data = proc.readAll();
        QString text = QString::fromLocal8Bit(data);

        outLog += text;
        lastActivity.restart();

        if (m_logCallback) {
            m_logCallback(text);
        }
    }

    proc.waitForFinished();

    int exitCode = proc.exitCode();

    if (exitCode == 0) {

        if (!safeReplace(tempPath, plan.finalPath)) {
            outLog += "\n[replace failed]";
            removeFileForce(tempPath); 
            return -4;
        }

        return 0;
    }

    removeFileForce(tempPath);  
    return exitCode;
}

QString FfmpegRunner::makeTempPath(const FfmpegRunRequest& plan) const
{
    QString name =
        QUuid::createUuid().toString(QUuid::WithoutBraces)
        + "." + plan.extension;

    return QDir(plan.saveFolder).filePath(name);
}

bool FfmpegRunner::safeReplace(const QString& tempPath,
                               const QString& finalPath) const
{
    QFile::remove(finalPath);

    if (QFile::rename(tempPath, finalPath)) {
        return true;
    }

    if (QFile::copy(tempPath, finalPath)) {
        QFile::remove(tempPath);
        return true;
    }

    return false;
}

bool FfmpegRunner::shouldRetry(int exitCode, const QString& log) const
{
    if (exitCode == 0)
        return false;

    if (exitCode == -2)
        return false;

    if (isPermanentError(log))
        return false;

    return true;
}

bool FfmpegRunner::isPermanentError(const QString& log) const
{
    return log.contains("Invalid argument", Qt::CaseInsensitive) ||
           log.contains("Unknown encoder", Qt::CaseInsensitive) ||
           log.contains("No such file", Qt::CaseInsensitive) ||
           log.contains("not found", Qt::CaseInsensitive);
}

bool FfmpegRunner::removeFileForce(const QString& path)
{
    for (int i = 0; i < 10; ++i) {

        if (!QFile::exists(path))
            return true;

        if (QFile::remove(path))
            return true;

        QThread::msleep(50);
    }

    return false;
}

QString FfmpegRunner::buildCommandString(const QString& program, const QStringList& args)
{
    QStringList escaped;

    for (const QString& arg : args) {
        // スペース対策
        if (arg.contains(' ') || arg.contains('"')) {
            QString a = arg;
            a.replace("\"", "\\\"");
            escaped << "\"" + a + "\"";
        } else {
            escaped << arg;
        }
    }

    return program + " " + escaped.join(" ");
}
