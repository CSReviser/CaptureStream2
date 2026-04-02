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

// =========================
// Container種別
// =========================
enum class Container {
    AAC,
    M4A,
    MP3
};

// =========================
// 音声フォーマット
// =========================
struct AudioFormat {
    QString codec;        // "libmp3lame" など
    QString bitrate;      // "128k"
    int channels = 2;     // 1 or 2
    QString sampleRate;   // "44100" など
    bool copyCodec = false;
};

// =========================
// メタデータ
// =========================
struct Metadata {
    QString title;
    QString artist;
    QString album;
    QString date;
    QString genre;
};

// =========================
// 入力オプション
// =========================
struct InputOptions {
    QString inputPath;        // URL or file

    QString userAgent;
    QString cookie;

    bool httpSeekable = false;
};

struct ThumbnailOptions {
    QString imagePath;     // カバー画像
    bool enabled = false;  // 有効/無効
};

// =========================
// RecordingRequest（本体）
// =========================
struct RecordingRequest {
    InputOptions input;
    AudioFormat format;
    ThumbnailOptions thumbnail;
    Metadata meta;
    
    QString extension;   // 🔥 追加（mp3 / m4a）
    QString presetKey;   // 🔥 追加（元の指

    Container container = Container::MP3;

    // コンテナ依存オプション
    bool writeXing = false;   // mp3用
    bool useId3v2 = false;    // mp3用

    QString outputPath;
    QStringList extraOutputOptions;
    bool includeOutputPath = false;  // 有効/無効
};
