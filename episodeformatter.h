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

// core/episodeformatter.h
#pragma once
#include "episodeinfo.h"

struct RuntimeConfig {
    QString titleFormat;
    QString fileFormat;

    bool nameSpace = false;
    bool kozaSeparation = false;
    bool tagSpace = false;
};

struct FormattedEpisode {
    QString title;
    QString fileNameBase;
    QString album;
};

class EpisodeFormatter {
public:
    static FormattedEpisode format(
        const EpisodeInfo& ep,
        const RuntimeConfig& cfg);

private:
    static QString buildHdate(const QDate& date);
    static QString applyKouzaRules(
        const EpisodeInfo& ep,
        const RuntimeConfig& cfg);
    static QString buildAlbum(
        QString album,
        const QString& kouza,
        const QString& format);
};
