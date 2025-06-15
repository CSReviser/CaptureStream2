#pragma once

#include <QString>
#include <QStringList>
#include <QMap>
#include <QSettings>
#include "AppSettings.h"

class SettingsManager {
public:
    SettingsManager();
    void load();
    void save();

    // 公開プロパティ（GUI/CLI 両対応のため public にする）
    QString saveFolder;
    QString ffmpegFolder;
    QString fileName1;
    QString fileName2;
    QString title1;
    QString title2;

    bool scrambleEnabled;
    QString scrambleUrl1;

    bool kozaSeparation;
    bool nameSpace;
    bool tagSpace;
    bool multiGui;

    QMap<QString, QString> optionalIdMap;  // optional1〜optionala のキーとID
    QMap<QString, QString> optionalTitleMap;

    QMap<QString, QString> specialIdMap;   // special1〜special4
    QMap<QString, QString> specialTitleMap;

private:
    QSettings settings;
};