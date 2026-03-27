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
#include <QProcess>

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
