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

// core/outputpathbuilder.cpp
#include "outputpathbuilder.h"
#include "legacyformatengine.h"
#include <QDir>

// =========================
// サニタイズ
// =========================

QString OutputPathBuilder::sanitize(const QString& s)
{
    QString out = s;

    static const QStringList illegalChars = {
        "/", "\\", ":", "*", "?", "\"",
        "<", ">", "|", "#", "{", "}",
        "%", "&", "~"
    };

    for (const auto& c : illegalChars) {
        out.replace(c, "_");
    }

    return out.trimmed();
}

// =========================
// メイン
// =========================

QString OutputPathBuilder::buildSubDir(
    const QString& format,
    const EpisodeInfo& ep)
{
    // 🔥 XML特別処理
    if (ep.isXml) {
        QString dir =
            QString::fromUtf8("[前週]/") + ep.kouza;

        return sanitize(dir);
    }

    // 🔷 通常（JSON）
    if (format.isEmpty())
        return "";

    LegacyFormatInput in;
    in.format = format;
    in.kouza  = ep.kouza;
    in.hdate  = ep.date.toString("MMdd");
    in.file   = ep.fileId;
    in.nendo  = ep.nendo;
    in.dupnmb = ep.dupnmb;
    in.checkIllegal = true;

    QString dir = LegacyFormatEngine::formatName(in);

    return sanitize(dir);
}

/*
// =========================
// サブフォルダ構築
// =========================

QString OutputPathBuilder::buildSubDir(
    const QString& format,
    const EpisodeInfo& ep)
{
    if (format.isEmpty())
        return "";

    LegacyFormatInput in;
    in.format = format;
    in.kouza  = ep.kouza;
    in.hdate  = ep.date.toString("MMdd");
    in.file   = ep.fileId;
    in.nendo  = ep.nendo;
    in.dupnmb = ep.dupnmb;
    in.checkIllegal = true;

    QString dir = LegacyFormatEngine::formatName(in);

    return sanitize(dir);
}

QString OutputPathBuilder::build(
    const OutputPathConfig& cfg,
    const QString& fileNameBase,
    const EpisodeInfo& ep)
{
    QString baseDir = cfg.rootDir;

    // 🔷 サブフォルダ
    QString subDir = buildSubDir(cfg.subDirFormat, ep);

    QString fullDir = baseDir;
    if (!subDir.isEmpty()) {
        fullDir = QDir(baseDir).filePath(subDir);
    }

    // 🔷 ファイル名
    QString fileName = sanitize(fileNameBase);

    // 🔷 拡張子
    QString ext = cfg.extension;
    if (!ext.startsWith(".")) {
        ext = "." + ext;
    }

    QString fullPath =
        QDir(fullDir).filePath(fileName + ext);

    return fullPath;
}
*/
