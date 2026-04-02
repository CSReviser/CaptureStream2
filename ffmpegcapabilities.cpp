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

#include "ffmpegcapabilities.h"
#include <QDir>
#include <QProcess>
#include <QFileInfo>
#include <QCoreApplication>

FfmpegCapabilities FfmpegCapabilities::detect(const QString& ffmpegPath)
{
    FfmpegCapabilities caps;

    QProcess process;
    process.setProgram(ffmpegPath);

    process.setArguments({
    	"-http_seekable", "0", "-version", "0"
/*
        "-http_seekable", "0",
        "-f", "lavfi",
        "-i", "anullsrc",
        "-t", "0.1",
        "-f", "null",
        "-"
*/  
    });

    process.start();
    process.waitForFinished();

    QString err = process.readAllStandardError();

//    if (!err.contains("Option not found", Qt::CaseInsensitive) &&
//        !err.contains("Unrecognized option", Qt::CaseInsensitive))
    if (!err.contains("Option not found", Qt::CaseInsensitive) )
    {
        caps.httpSeekableSupported = true;
    }

    return caps;
}

QString FfmpegCapabilities::autoDetectFfmpeg()
{
    QProcess process;
    QString ffmpegPath;
    
    ffmpegPath = QCoreApplication::applicationDirPath();
    if (QFile::exists(ffmpegPath))
        return QFileInfo(ffmpegPath).absolutePath();

#ifdef Q_OS_WIN
    process.start("cmd.exe", QStringList() << "/c" << "where" << "ffmpeg");
#else
    process.start("which", QStringList() << "ffmpeg");
#endif
    process.waitForFinished();

    ffmpegPath = QString::fromUtf8(process.readAllStandardOutput())
                     .split("\n").first().trimmed();

    if (!QFileInfo::exists(ffmpegPath)) {
#ifdef Q_OS_MAC
        QString arch = QSysInfo::buildCpuArchitecture();
        if (arch == "x86_64") {
            ffmpegPath = "/usr/local/bin/ffmpeg";
        } else if (arch == "arm64") {
            ffmpegPath = "/opt/homebrew/bin/ffmpeg";
            if (!QFile::exists(ffmpegPath))
                ffmpegPath = "/usr/local/bin/ffmpeg";
        }
#elif defined(Q_OS_LINUX)
        ffmpegPath = "/usr/bin/ffmpeg";
#elif defined(Q_OS_WIN)
        ffmpegPath = "C:\\Program Files\\ffmpeg\\bin\\ffmpeg.exe";
        if (!QFile::exists(ffmpegPath))
            ffmpegPath = "C:\\ffmpeg\\bin\\ffmpeg.exe";
#endif
    }

    if (QFile::exists(ffmpegPath))
        return QFileInfo(ffmpegPath).absolutePath();

    return QString();
}

bool FfmpegCapabilities::isValidFfmpegFolder(const QString& folder) 
{
    if (folder.isEmpty())
        return false;

    QDir dir(folder);
    if (!dir.exists())
        return false;

#ifdef Q_OS_WIN
    QString exe = dir.filePath("ffmpeg.exe");
#else
    QString exe = dir.filePath("ffmpeg");
#endif

    if (!QFileInfo::exists(exe))
        return false;

    return canExecuteFfmpeg(exe);
}

bool FfmpegCapabilities::canExecuteFfmpeg(const QString& ffmpegPath)
{
    QProcess p;
    p.start(ffmpegPath, {"-version"});
    if (!p.waitForFinished(1500))  // タイムアウト短めでOK
        return false;

    return (p.exitStatus() == QProcess::NormalExit);
}

QString FfmpegCapabilities::detectFfmpegFolder()
{
    return autoDetectFfmpeg();   // private 関数を内部で呼ぶ
}

QString FfmpegCapabilities::findFfmpegPath() {
	QProcess process;
	QString ffmpegPath;

#ifdef Q_OS_WIN
	process.start("cmd.exe", QStringList() << "/c" << "where" << "ffmpeg");
#else
	process.start("which", QStringList() << "ffmpeg");
#endif
	process.waitForFinished();

	ffmpegPath = QString::fromUtf8(process.readAllStandardOutput()).split("\n").first().trimmed();

	if (!QFileInfo::exists(ffmpegPath)) {
#ifdef Q_OS_MAC
		QString arch = QSysInfo::buildCpuArchitecture();
		if (arch == "x86_64") {
			ffmpegPath = "/usr/local/bin/ffmpeg";
		} else if (arch == "arm64") {
			ffmpegPath = "/opt/homebrew/bin/ffmpeg";
			if (!QFile::exists(ffmpegPath)) {
				ffmpegPath = "/usr/local/bin/ffmpeg";
			}
		}
#elif defined(Q_OS_LINUX)
		ffmpegPath = "/usr/bin/ffmpeg";
#elif defined(Q_OS_WIN)
		ffmpegPath = "C:\\Program Files\\ffmpeg\\bin\\ffmpeg.exe";
		if (!QFile::exists(ffmpegPath)) {
			ffmpegPath = "C:\\ffmpeg\\bin\\ffmpeg.exe";
		}
#endif
	}

	if (QFile::exists(ffmpegPath)) {
		return QFileInfo(ffmpegPath).absolutePath();
	}
	return QString();
}
