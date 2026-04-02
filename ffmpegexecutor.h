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
#include <QProcess>

// =========================
// 実行結果
// =========================
struct FfmpegResult {
    bool started = false;

    int exitCode = -1;
    QProcess::ProcessError processError = QProcess::UnknownError;

    QString stdOut;
    QString stdErr;
};

// =========================
// Executor
// =========================
class FfmpegExecutor
{
public:
    static FfmpegResult run(const QString& program,
                            const QStringList& args,
                            int timeoutMs = -1); // -1 = 無制限
};
