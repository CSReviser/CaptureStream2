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