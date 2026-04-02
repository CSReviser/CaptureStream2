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

#include "thumbnailoptionsbuilder.h"

QStringList ThumbnailOptionsBuilder::buildInput(const RecordingRequest& req)
{
    QStringList args;

    if (!req.thumbnail.enabled)
        return args;

    if (req.thumbnail.imagePath.isEmpty())
        return args;

    // 画像を追加入力として渡す
    args << "-i" << req.thumbnail.imagePath;

    return args;
}

QStringList ThumbnailOptionsBuilder::buildOutput(const RecordingRequest& req)
{
    QStringList args;

    if (!req.thumbnail.enabled)
        return args;

    if (req.thumbnail.imagePath.isEmpty())
        return args;

    if (req.container == Container::MP3 ||
        req.container == Container::M4A) {

        args << "-map" << "0:a";
        args << "-map" << "1:v";

        args << "-map_metadata" << "0";

        // 音声はBuilder側に任せる

        args << "-c:v" << "mjpeg";
        args << "-disposition:v" << "attached_pic";
    }

    return args;
}
