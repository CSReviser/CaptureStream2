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

#include "ffmpegcommandbuilder.h"
#include "thumbnailoptionsbuilder.h"
#include <QDir>
#include <QUrl>

QStringList FfmpegCommandBuilder::build(
    const RecordingRequest& req,
    const FfmpegCapabilities& caps,
    const QString& outputPath = QString())
{
    QStringList args;

    // =========================
    // 入力
    // =========================
    args << "-y";  // 上書き許可（開発中は必須）

    if (req.input.httpSeekable && caps.httpSeekableSupported) {
        args << "-http_seekable" << "0";
    }

    if (req.input.inputPath.isEmpty()) {
        return {}; // 異常
    }

    QUrl url(req.input.inputPath);

    if (url.isValid() && url.scheme().startsWith("http")) {
        args << "-i" << req.input.inputPath;
    } else {
        args << "-i" << QDir::toNativeSeparators(req.input.inputPath);
    }

    // サムネイル埋め込み
    args << ThumbnailOptionsBuilder::buildInput(req);

    // =========================
    // コンテナチェック（最小）
    // =========================
    if (req.container != Container::MP3 &&
        req.container != Container::M4A &&
        req.container != Container::AAC) {
        return {};
    }

    // =========================
    // 音声エンコード
    // =========================
    if (req.format.copyCodec) {
        args << "-c:a" << "copy";
    } else {
        args << "-c:a" << req.format.codec;
        // ビットレート
        if (!req.format.bitrate.isEmpty()) {
            args << "-b:a" << req.format.bitrate;
        }
        // チャンネル
        if (req.format.channels > 0) {
            args << "-ac" << QString::number(req.format.channels);
        }
        // サンプルレート（指定があれば）
        if (!req.format.sampleRate.isEmpty()) {
            args << "-ar" << req.format.sampleRate;
        }
    }

    // =========================
    // M4Aコンテナオプション
    // =========================
    if (req.container == Container::M4A &&
        req.format.copyCodec) {
        args << "-bsf:a" << "aac_adtstoasc";
    }

    // =========================
    // メタデータ
    // =========================
    if (!req.meta.title.isEmpty()) {
        args << "-metadata" << "title=" + req.meta.title;
    }

    if (!req.meta.artist.isEmpty()) {
        args << "-metadata" << "artist=" + req.meta.artist;
    }

    if (!req.meta.album.isEmpty()) {
        args << "-metadata" << "album=" + req.meta.album;
    }

    if (!req.meta.date.isEmpty()) {
        args << "-metadata" << "date=" + req.meta.date;
    }

    if (!req.meta.genre.isEmpty()) {
        args << "-metadata" << "genre=" + req.meta.genre;
    }

    // =========================
    // サムネイル埋め込み
    // =========================
    args << ThumbnailOptionsBuilder::buildOutput(req);

    // =========================
    // MP3コンテナオプション（出力直前へ移動）
    // =========================
    if (req.container == Container::MP3) {
        if (req.useId3v2) {
            args << "-id3v2_version" << "3";
        }

        if (!req.writeXing) {
            args << "-write_xing" << "0";
        }
    }

    // =========================
    // 追加オプションフック（将来用）
    // =========================
    if (!req.extraOutputOptions.isEmpty()) {
        args << req.extraOutputOptions;
    }
    
    // =========================
    // 出力
    // =========================
    if (req.includeOutputPath) {
        if (outputPath.isEmpty()) return {};
        args << QDir::toNativeSeparators(outputPath);
    }

    return args;
}
