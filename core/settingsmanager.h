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


struct SettingEntry {
	QString key;
	QVariant value;
	QVariant defaultValue;
};
class SettingsManager : public QObject {
    Q_OBJECT

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
    
    const QList<SettingEntry>& checkBoxSettings() const;
    void updateCheckBoxValue(const QString& key, bool value);
    static QString applicationBundlePath();
    
    // 設定保持構造体
    QMap<QString, bool> checkBoxStates;
    QMap<QString, QString> textComboBoxValues;

    explicit SettingsManager(QObject* parent = nullptr);

    AppSettings::Data& data();
    const AppSettings::Data& data() const;

    void initializeMaps(const QStringList& kozaList);
    void fetchKozaSeries(const QStringList& kozaList);

signals:
    void mapInitializationFinished();
private:
    QSettings settings;
    QList<SettingEntry> m_checkBoxSettings;
    QNetworkAccessManager* m_networkManager;
    AppSettings::Data m_data;
};

#ifndef SETTINGSMANAGER_H

