// core/outputpathbuilder.h
#pragma once
#include <QString>
#include "episodeinfo.h"

struct OutputPathConfig {
    QString rootDir;      // 保存先
    QString subDirFormat; // 例: "%k/%N"
    QString extension;    // mp3 / m4a
};

class OutputPathBuilder {
public:
    static QString build(
        const OutputPathConfig& cfg,
        const QString& fileNameBase,
        const EpisodeInfo& ep);

private:
    static QString buildSubDir(
        const QString& format,
        const EpisodeInfo& ep);

    static QString sanitize(const QString& s);
};