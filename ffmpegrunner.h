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

#pragma once

#include <QString>
#include <QStringList>
#include <functional>
#include <atomic>
#include <QProcess>

struct FfmpegRunRequest
{
    QString program;
    QStringList args;

    int maxRetry = 3;
    int baseDelayMs = 1000;
    int idleTimeoutMs = 30000;

    QString finalPath;
    QString saveFolder;
    QString extension;
};

class FfmpegRunner
{
public:
    struct Result {
        int exitCode = -1;
        bool success = false;
        bool canceled = false;
        int attempts = 0;
        QString lastLog;
    };

    using LogCallback = std::function<void(const QString&)>;

public:
    FfmpegRunner();

    // ★ 修正
    Result run(const FfmpegRunRequest& plan);

    void requestCancel();
    void setLogCallback(LogCallback cb);
	
private:
    int runOnce(const FfmpegRunRequest& plan, QString& outLog);

    bool shouldRetry(int exitCode, const QString& log) const;
    bool isPermanentError(const QString& log) const;

    QProcess proc;
    QString makeTempPath(const FfmpegRunRequest& plan) const;

    bool safeReplace(const QString& tempPath, const QString& finalPath) const;

    std::atomic<bool> m_cancelRequested { false };
    std::atomic<bool> m_running { false };

    LogCallback m_logCallback;
    
    bool removeFileForce(const QString& path);
    
    static QString buildCommandString(const QString& program, const QStringList& args);
};
