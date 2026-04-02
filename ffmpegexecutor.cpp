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

#include "ffmpegexecutor.h"

FfmpegResult FfmpegExecutor::run(const QString& program,
                                 const QStringList& args,
                                 int timeoutMs)
{
    FfmpegResult result;

    QProcess process;

    // =========================
    // プロセス設定
    // =========================
    process.setProgram(program);
    process.setArguments(args);

    // stdout / stderr を分離
    process.setProcessChannelMode(QProcess::SeparateChannels);

    // =========================
    // 起動
    // =========================
    process.start();

    if (!process.waitForStarted(5000)) {
        result.started = false;
        result.processError = process.error();
        return result;
    }

    result.started = true;

    // =========================
    // 実行待ち
    // =========================
    bool finished = false;

    if (timeoutMs < 0) {
        // 無制限（基本これ）
        finished = process.waitForFinished(-1);
    } else {
        finished = process.waitForFinished(timeoutMs);
    }

    // =========================
    // タイムアウト対応
    // =========================
    if (!finished) {
        process.kill();
        process.waitForFinished(3000);

        result.exitCode = -1;
        result.processError = QProcess::Timedout;
        result.stdOut = process.readAllStandardOutput();
        result.stdErr = process.readAllStandardError();
        return result;
    }

    // =========================
    // 結果取得
    // =========================
    result.exitCode = process.exitCode();
    result.processError = process.error();

    result.stdOut = process.readAllStandardOutput();
    result.stdErr = process.readAllStandardError();

    return result;
}
