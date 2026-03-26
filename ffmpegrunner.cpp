#include "FfmpegRunner.h"

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

FfmpegRunner::Result FfmpegRunner::run(const FfmpegRunRequest& req)
{
    Result result;

    if (m_running) {
        result.exitCode = -100;
        return result;
    }

    m_running = true;
    m_cancelRequested = false;

    for (int attempt = 1; attempt <= req.maxRetry; ++attempt) {

        if (m_cancelRequested) {
            result.canceled = true;
            break;
        }

        QString log;
        int code = runOnce(req, log);

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

        if (attempt < req.maxRetry) {

            int delay = req.baseDelayMs * attempt;

            if (code == -3) { // timeout
                delay += req.baseDelayMs;
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

int FfmpegRunner::runOnce(const FfmpegRunRequest& req, QString& outLog)
{
    QString tempPath = makeTempPath(req);

    QStringList args = req.args;

    if (!args.isEmpty()) {
        args[args.size() - 1] = tempPath;
    }

    QProcess proc;
    proc.setProcessChannelMode(QProcess::MergedChannels);
    proc.start(req.program, args);

    if (!proc.waitForStarted()) {
        outLog = "Failed to start ffmpeg";
        return -1;
    }

    QElapsedTimer lastActivity;
    lastActivity.start();

    while (proc.state() == QProcess::Running) {

        if (m_cancelRequested) {
            proc.kill();
            proc.waitForFinished();
            QFile::remove(tempPath);
            return -2;
        }

        if (!proc.waitForReadyRead(100)) {

            if (lastActivity.elapsed() > req.idleTimeoutMs) {
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

        if (!safeReplace(tempPath, req.finalPath)) {
            outLog += "\n[replace failed]";
            return -4;
        }

        return 0;
    }

    QFile::remove(tempPath);
    return exitCode;
}

QString FfmpegRunner::makeTempPath(const FfmpegRunRequest& req) const
{
    QString name =
        QUuid::createUuid().toString(QUuid::WithoutBraces)
        + "." + req.extension;

    return QDir(req.saveFolder).filePath(name);
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