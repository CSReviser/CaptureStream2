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

// core/episodeformatter.cpp
#include "episodeformatter.h"
#include "legacyformatengine.h"

QString EpisodeFormatter::buildHdate(const QDate& date)
{
    return QString("%1%2")
        .arg(date.month(), 2, 10, QChar('0'))
        .arg(date.day(),   2, 10, QChar('0'));
}

QString EpisodeFormatter::applyKouzaRules(
    const EpisodeInfo& ep,
    const RuntimeConfig& cfg)
{
    QString kouza = ep.kouza;

    if (!cfg.kozaSeparation)
        return kouza;

    auto add = [&](const QString& s) {
        return cfg.nameSpace ? "【" + s + "】" : " " + s;
    };

    if (ep.rawTitle.contains("入門")) kouza += add("入門編");
    if (ep.rawTitle.contains("初級")) kouza += add("初級編");
    if (ep.rawTitle.contains("中級")) kouza += add("中級編");
    if (ep.rawTitle.contains("応用")) kouza += add("応用編");

    return kouza;
}

QString EpisodeFormatter::buildAlbum(
    QString album,
    const QString& kouza,
    const QString& format)
{
    if (!format.contains("%x", Qt::CaseInsensitive))
        return album;

    album.remove("まいにち");

    if (kouza.contains("レベル１")) album = "L1_" + album.remove("レベル１");
    if (kouza.contains("レベル２")) album = "L2_" + album.remove("レベル２");

    if (kouza.contains("入門")) album = "入門_" + album.remove("入門編");
    if (kouza.contains("初級")) album = "初級_" + album.remove("初級編");
    if (kouza.contains("中級")) album = "中級_" + album.remove("中級編");
    if (kouza.contains("応用")) album = "応用_" + album.remove("応用編");

    return album;
}

FormattedEpisode EpisodeFormatter::format(
    const EpisodeInfo& ep,
    const RuntimeConfig& cfg)
{
    FormattedEpisode out;

    QString kouza = applyKouzaRules(ep, cfg);

    LegacyFormatInput in;
    in.kouza = kouza;
    in.hdate = buildHdate(ep.date);
    in.file  = ep.fileId;
    in.nendo = ep.nendo;
    in.dupnmb = "";
    in.checkIllegal = true;

    in.format = cfg.titleFormat;
    out.title = LegacyFormatEngine::formatName(in);

    in.format = cfg.fileFormat;
    out.fileNameBase = LegacyFormatEngine::formatName(in);

    out.album = buildAlbum(kouza, kouza, cfg.fileFormat);

    return out;
}
