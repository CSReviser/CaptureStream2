// core/episodeinfo.h
#pragma once
#include <QString>
#include <QDate>

struct EpisodeInfo {
    QString inputUrl;

    QString rawTitle;
    QString kouza;

    QDate   date;      // 🔥 統一
    QString nendo;     // 表示用（Formatter用）

    QString fileId;    // 元ファイル名ベース
    QString thumbnailPath;
};