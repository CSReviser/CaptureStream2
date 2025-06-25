/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2025 CSReviser Team

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

#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#pragma once

#include <QString>
#include <QStringList>
#include <QMap>
#include <QSettings>

class SettingsManager
{
public:
    SettingsManager();

    // 設定の読み書き
    void loadSettings();
    void saveSettings();
    void resetToDefaults();

    // チェックボックス・テキストComboBoxの状態
    QMap<QString, bool> checkBoxStates;
    QMap<QString, QString> textComboBoxValues;

    // 一般設定
    QString saveFolder;
    QString ffmpegFolder;
    QString fileName1;
    QString fileName2;
    QString title1;
    QString title2;
    QString scrambleUrl1;
    QString audioExtension;

    bool scrambleEnabled;
    bool kozaSeparation;
    bool nameSpace;
    bool tagSpace;
    bool multiGui;

    // 番組マップ（タイトルとID）
    QMap<QString, QString> optionalIdMap;     // optional1〜optional8
    QMap<QString, QString> optionalTitleMap;
    QMap<QString, QString> specialIdMap;      // special1〜special4
    QMap<QString, QString> specialTitleMap;
    QMap<QString, QString> nameMap;
    QMap<QString, QString> thumbnailMap;

    // 状態更新・初期化
    void updateCheckBoxValue(const QString& key, bool value);
    void updateTextComboBoxValue(const QString& key, const QString& value);
    void initializeMaps(const QStringList& kozaList);
    void fetchKozaSeries(const QStringList& kozaList);
    QString getProgramName(const QString& title, const QString& cornerName);

    // ゲッター（参照）
    const QMap<QString, bool>& getCheckBoxStates() const;
    const QMap<QString, QString>& getTextComboBoxValues() const;
    const QMap<QString, QString>& getOptionalIdMap() const;
    const QMap<QString, QString>& getOptionalTitleMap() const;
    const QMap<QString, QString>& getSpecialIdMap() const;
    const QMap<QString, QString>& getSpecialTitleMap() const;

    // 補助
    static QString applicationBundlePath();

private:
    QSettings settings;
    void loadDefaultValues();
};

#endif // SETTINGSMANAGER_H

/*
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#pragma once

#include <QString>
#include <QStringList>
#include <QMap>
#include <QSettings>
#include <QVariant>
#include <QStandardPaths>
#include "appsettings.h"
#include <QObject>
#include <QNetworkAccessManager>



class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject* parent = nullptr);

    // 読み書きAPI
    void loadSettings();
    void saveSettings();
    void resetToDefaults();

    // アプリ設定
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

    // 番組マップ
    QMap<QString, QString> optionalIdMap;  // optional1〜optionala のキーとID
    QMap<QString, QString> optionalTitleMap;
    QMap<QString, QString> specialIdMap;   // special1〜special4
    QMap<QString, QString> specialTitleMap;
    QMap<QString, QString> nameMap;
    QMap<QString, QString> thumbnailMap;

 
     // 設定保持構造体
     // UI連携用
    QMap<QString, bool> checkBoxStates;
    QMap<QString, QString> textComboBoxValues;
 //   const QList<SettingEntry>& checkBoxSettings() const;
    void updateCheckBoxValue(const QString& key, bool value);

    // その他機能
    void initializeMaps(const QStringList& kozaList);
    void fetchKozaSeries(const QStringList& kozaList);
    QString getProgram_name(QString title, QString corner_name);
    static QString applicationBundlePath();
 
    const QMap<QString, bool>& getCheckBoxStates() const;
    const QMap<QString, QString>& getTextComboBoxValues() const;
    const QMap<QString, QString>& getOptionalIdMap() const;
    const QMap<QString, QString>& getOptionalTitleMap() const;
    const QMap<QString, QString>& getSpecialIdMap() const;
    const QMap<QString, QString>& getSpecialTitleMap() const;

    // 設定項目（実データ）-- あなたが提示した内容と同等
    bool basic0 = false;
    bool basic1 = false;
    bool basic2 = false;
    bool business1 = false;
    bool detailed_message = false;
    bool enjoy = false;
    bool gendai = false;
    bool kaiwa = true;
    bool koza_separation = true;
    bool multi_gui = true;
    bool name_space = true;
    bool optional_flags[8] = { false };
    bool special_flags[4] = { false };
    bool skip = true;
    bool this_week = true;
    bool thumbnail = false;
    bool timetrial = false;
    bool tag_space = false;

    QString audio_extension = "m4a";
    QString ffmpeg_folder;
    QString save_folder;

    QString opt_titles[8];
    QString opt_ids[8];
    QString spec_titles[4];
    QString spec_ids[4];


signals:
    void mapInitializationFinished();
    
private:
//    QSettings settings;
//   QList<SettingEntry> m_checkBoxSettings;
//    QNetworkAccessManager* m_networkManager;
};

//#ifndef SETTINGSMANAGER_H

#endif // SETTINGSMANAGER_H


*/

