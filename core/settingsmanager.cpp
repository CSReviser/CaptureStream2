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

#include <QCoreApplication>
#include <QDir>
#include "settingsmanager.h"
#include "Utility.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QtNetwork>

SettingsManager::SettingsManager()
    : settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
    QString iniPath = applicationBundlePath();
    iniPath += QDir::separator() + QStringLiteral("CaptureStream2.ini");
    QSettings settings = QSettings(iniPath, QSettings::IniFormat);
}

void SettingsManager::load() {
    settings.beginGroup( "MainWindow" );
    
    saveFolder = settings.value(AppSettings::SETTING_SAVE_FOLDER, "").toString();
    ffmpegFolder = settings.value(AppSettings::SETTING_FFMPEG_FOLDER, "").toString();

    fileName1 = settings.value(AppSettings::SETTING_FILE_NAME1, AppSettings::FILE_NAME1).toString();
    fileName2 = settings.value(AppSettings::SETTING_FILE_NAME2, AppSettings::FILE_NAME2).toString();
    title1 = settings.value(AppSettings::SETTING_TITLE1, AppSettings::FILE_TITLE1).toString();
    title2 = settings.value(AppSettings::SETTING_TITLE2, AppSettings::FILE_TITLE2).toString();

    scrambleEnabled = settings.value(AppSettings::SETTING_SCRAMBLE, true).toBool();
    scrambleUrl1 = settings.value(AppSettings::SETTING_SCRAMBLE_URL1, AppSettings::SCRAMBLE_URL1).toString();

    kozaSeparation = settings.value(AppSettings::SETTING_KOZA_SEPARATION, AppSettings::KOZA_SEPARATION_FLAG).toBool();
    nameSpace = settings.value(AppSettings::SETTING_NAME_SPACE, AppSettings::NAME_SPACE_FLAG).toBool();
    tagSpace = settings.value(AppSettings::SETTING_TAG_SPACE, AppSettings::TAG_SPACE_FLAG).toBool();
    multiGui = settings.value(AppSettings::SETTING_MULTI_GUI, AppSettings::MULTI_GUI_FLAG).toBool();

    // オプショナル番組
    for (int i = 0; i < 10; ++i) {
        const QString key = AppSettings::SETTING_OPTIONAL_KEYS[i];
        QString id = settings.value(key, AppSettings::OPTIONAL_IDS[i]).toString();
        QString title = AppSettings::Program_TITLES[i];
        optionalIdMap[key] = id;
        optionalTitleMap[key] = title;
    }

    // 特別番組
    for (int i = 0; i < 4; ++i) {
        const QString key = AppSettings::SETTING_SPECIAL_KEYS[i];
        QString id = settings.value(key, AppSettings::SPECIAL_IDS[i]).toString();
        QString title = AppSettings::Special_TITLES[i];
        specialIdMap[key] = id;
        specialTitleMap[key] = title;
    }
    
    QSettings settings;
    m_checkBoxSettings.clear();

    for (int i = 0; i < AppSettings::kCheckBoxKeys.size(); ++i) {
	QString key = AppSettings::kCheckBoxKeys[i];
	bool def = AppSettings::kCheckBoxDefaults[i];
	bool val = settings.value(key, def).toBool();
	m_checkBoxSettings.append({ key, val, def });
    }
	
    // チェックボックス読み込み
    for (int i = 0; i < AppSettings::kCheckBoxKeys.size(); ++i) {
        QString key = AppSettings::kCheckBoxKeys[i];
        bool defVal = AppSettings::kCheckBoxDefaults[i];
        checkBoxStates[key] = settings.value(key, defVal).toBool();
    }

    // テキストコンボボックス読み込み
    for (int i = 0; i < AppSettings::kTextComboBoxKeys.size(); ++i) {
        QString key = AppSettings::kTextComboBoxKeys[i];
        QString defVal = AppSettings::kTextComboBoxDefaults[i];
        textComboBoxValues[key] = settings.value(key, defVal).toString();
    }

    // 他の設定も必要なら同様に読み込む
    saveFolder = settings.value("save_folder", "").toString();
    ffmpegFolder = settings.value("ffmpeg_folder", "").toString();
    fileName1 = settings.value("file_name1", "%k_%Y_%M_%D.m4a").toString();
    fileName2 = settings.value("file_name2", "%f").toString();
    
}

void SettingsManager::save() {
    settings.beginGroup( "MainWindow" );
    
    settings.setValue(AppSettings::SETTING_SAVE_FOLDER, saveFolder);
    settings.setValue(AppSettings::SETTING_FFMPEG_FOLDER, ffmpegFolder);

    settings.setValue(AppSettings::SETTING_FILE_NAME1, fileName1);
    settings.setValue(AppSettings::SETTING_FILE_NAME2, fileName2);
    settings.setValue(AppSettings::SETTING_TITLE1, title1);
    settings.setValue(AppSettings::SETTING_TITLE2, title2);

    settings.setValue(AppSettings::SETTING_SCRAMBLE, scrambleEnabled);
    settings.setValue(AppSettings::SETTING_SCRAMBLE_URL1, scrambleUrl1);

    settings.setValue(AppSettings::SETTING_KOZA_SEPARATION, kozaSeparation);
    settings.setValue(AppSettings::SETTING_NAME_SPACE, nameSpace);
    settings.setValue(AppSettings::SETTING_TAG_SPACE, tagSpace);
    settings.setValue(AppSettings::SETTING_MULTI_GUI, multiGui);

    for (int i = 0; i < 10; ++i) {
        const QString key = AppSettings::SETTING_OPTIONAL_KEYS[i];
        settings.setValue(key, optionalIdMap.value(key, AppSettings::OPTIONAL_IDS[i]));
    }

    for (int i = 0; i < 4; ++i) {
        const QString key = AppSettings::SETTING_SPECIAL_KEYS[i];
        settings.setValue(key, specialIdMap.value(key, AppSettings::SPECIAL_IDS[i]));
    }
    
	QSettings settings;
	for (const auto& entry : m_checkBoxSettings) {
		settings.setValue(entry.key, entry.value);
	}
	
    for (const auto& key : checkBoxStates.keys()) {
        settings.setValue(key, checkBoxStates[key]);
    }

    for (const auto& key : textComboBoxValues.keys()) {
        settings.setValue(key, textComboBoxValues[key]);
    }

    settings.setValue("save_folder", saveFolder);
    settings.setValue("ffmpeg_folder", ffmpegFolder);
    settings.setValue("file_name1", fileName1);
    settings.setValue("file_name2", fileName2);	
}

void SettingsManager::updateCheckBoxValue(const QString& key, bool value) {
	for (auto& entry : m_checkBoxSettings) {
		if (entry.key == key) {
			entry.value = value;
			break;
		}
	}
}

const QList<SettingEntry>& SettingsManager::checkBoxSettings() const {
	return m_checkBoxSettings;
}

QString SettingsManager::applicationBundlePath() {

#ifdef Q_OS_LINUX
    QString basePath;
    // AppImage 環境変数が存在すれば AppImage 実行中
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty()) {
        // AppImage 実行：本体のある場所を保存先とする
        QFileInfo fi(appImagePath);
        basePath = fi.absolutePath();
	basePath += QDir::separator();
        return basePath;
    } 
 #endif
    
	QString result = QCoreApplication::applicationDirPath();
#ifdef Q_OS_MACOS				//Macのffmpegパス不正対策　2022/04/13
	QString result = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/";
	result += QDir::separator();
	return result;
#endif
	result += QDir::separator();
	return result;
}

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this)) {}

AppSettings::Data& SettingsManager::data() {
    return m_data;
}

const AppSettings::Data& SettingsManager::data() const {
    return m_data;
}

void SettingsManager::initializeMaps(const QStringList& kozaList) {
    QUrl url("https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/corners/new_arrivals");
    QNetworkRequest request(url);
    QNetworkReply* reply = m_networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response_data = reply->readAll();
        reply->deleteLater();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
        QJsonArray jsonArray = jsonResponse.object()["corners"].toArray();

        for (const QJsonValue& value : jsonArray) {
            QJsonObject obj = value.toObject();
            QString title = obj["title"].toString();
            QString corner_name = obj["corner_name"].toString();
            QString series_site_id = obj["series_site_id"].toString();
            QString corner_site = obj["corner_site_id"].toString();
            QString thumbnail_url = obj["thumbnail_url"].toString();

            QString program_name = Utility::getProgram_name3(title, corner_name);
            QString url_id = series_site_id + "_" + corner_site;

            m_data.idMap.insert(url_id, program_name);
            m_data.nameMap.insert(program_name, url_id);
            m_data.thumbnailMap.insert(url_id, thumbnail_url);
        }

        fetchKozaSeries(kozaList);
    });
}

void SettingsManager::fetchKozaSeries(const QStringList& kozaList) {
    for (const QString& koza : kozaList) {
        if (!m_data.nameMap.contains(koza)) continue;

        QString url = m_data.nameMap[koza];
        int l = url.length() != 13 ? url.length() - 3 : 10;
        QString fullUrl = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
                          url.left(l) + "&corner_site_id=" + url.right(2);

        QNetworkRequest request(QUrl(fullUrl));
        QNetworkReply* reply = m_networkManager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {
            QByteArray response_data = reply->readAll();
            reply->deleteLater();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
            QJsonArray jsonArray = jsonResponse.object()["episodes"].toArray();

            for (const QJsonValue& value : jsonArray) {
                QJsonObject obj = value.toObject();
                QString file_title = obj["program_title"].toString();

                QString temp1, temp2;
                if (file_title.contains("入門編")) {
                    temp1 = koza + "【入門編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("初級編")) {
                    temp1 = koza + "【初級編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("応用編")) {
                    temp1 = koza + "【応用編】";
                    temp2 = url.left(l) + "_y1";
                }
                if (file_title.contains("中級編")) {
                    temp1 = koza + "【中級編】";
                    temp2 = url.left(l) + "_y1";
                }

                if (!temp1.isEmpty() && !temp2.isEmpty()) {
                    m_data.nameMap.insert(temp1, temp2);
                    m_data.idMap.insert(temp2, temp1);
                }
            }

            if (koza == kozaList.last()) {
                emit mapInitializationFinished();
            }
        });
    }
}
