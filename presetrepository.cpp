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

#include "presetrepository.h"

namespace {

// =========================
// Audio Presets（内部専用）
// =========================

AudioFormat aacCopy()
{
    return {
        .codec = "copy",
        .bitrate = "",
        .channels = 2,
        .sampleRate = "",
        .copyCodec = true
    };
}

AudioFormat mp3_128k_stereo()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "128k",
        .channels = 2,
        .sampleRate = "",
        .copyCodec = false
    };
}

AudioFormat mp3_64k_stereo()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "64k",
        .channels = 2,
        .sampleRate = "",
        .copyCodec = false
    };
}

AudioFormat mp3_48k_stereo()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "48k",
        .channels = 2,
        .sampleRate = "",
        .copyCodec = false
    };
}

AudioFormat mp3_40k_stereo()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "40k",
        .channels = 2,
        .sampleRate = "32000",
        .copyCodec = false
    };
}

AudioFormat mp3_32k_stereo()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "32k",
        .channels = 2,
        .sampleRate = "32000",
        .copyCodec = false
    };
}

AudioFormat mp3_40k_mono()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "40k",
        .channels = 1,
        .sampleRate = "32000",
        .copyCodec = false
    };
}

AudioFormat mp3_32k_mono()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "32k",
        .channels = 1,
        .sampleRate = "32000",
        .copyCodec = false
    };
}

AudioFormat mp3_24k_mono()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "24k",
        .channels = 1,
        .sampleRate = "22050",
        .copyCodec = false
    };
}

AudioFormat mp3_16k_mono()
{
    return {
        .codec = "libmp3lame",
        .bitrate = "16k",
        .channels = 1,
        .sampleRate = "22050",
        .copyCodec = false
    };
}

} // namespace

bool PresetRepository::resolve(const QString& key, RecordingRequest& req)
{
    // --- 初期化（重要：前回の状態を消す） ---
    req.format = {};
    req.container = Container::MP3;
    req.writeXing = false;
    req.useId3v2 = false;

    // =========================
    // AAC
    // =========================
    if (key == "aac") {
        req.format = aacCopy();
        req.container = Container::AAC;
        return true;
    }

    // =========================
    // M4A
    // =========================
    if (key == "m4a") {
        req.format = aacCopy();
        req.container = Container::M4A;
        req.useId3v2 = true;
        return true;
    }

    // =========================
    // MP3 Stereo
    // =========================
    if (key == "mp3") {
        req.format = mp3_64k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    if (key == "mp3-128k-S") {
        req.format = mp3_128k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    if (key == "mp3-64k-S") {
        req.format = mp3_64k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    if (key == "mp3-48k-S") {
        req.format = mp3_48k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    if (key == "mp3-40k-S") {
        req.format = mp3_40k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }
    
    if (key == "mp3-32k-S") {
        req.format = mp3_32k_stereo();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    // =========================
    // MP3 Mono
    // =========================
    if (key == "mp3-40k-M") {
        req.format = mp3_40k_mono();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    if (key == "mp3-24k-M") {
        req.format = mp3_24k_mono();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }
    
    if (key == "mp3-16k-M") {
        req.format = mp3_16k_mono();
        req.container = Container::MP3;
        req.useId3v2 = true;
        req.writeXing = false;
        return true;
    }

    // =========================
    // 未定義キー
    // =========================
    return false;
}
