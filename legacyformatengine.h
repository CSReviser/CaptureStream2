// core/legacyformatengine.h
#pragma once
#include <QString>

struct LegacyFormatInput {
    QString format;
    QString kouza;
    QString hdate;
    QString file;
    QString nendo;
    QString dupnmb;
    bool checkIllegal = true;
};

class LegacyFormatEngine {
public:
    static QString formatName(const LegacyFormatInput& in);
};