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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>

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

    settings.endGroup();    
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
    
    settings.endGroup();
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

            QString program_name = getProgram_name(title, corner_name);
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

        QNetworkRequest request{QUrl(fullUrl)};
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

QString SettingsManager::getProgram_name( QString title, QString corner_name ) {
	QString attribute = title.replace( "　", " " );
		
	if ( !(corner_name.isNull()  || corner_name.isEmpty()) ) {
		if( corner_name.contains( "曜日放送", Qt::CaseInsensitive ) || corner_name.contains( "曜放送", Qt::CaseInsensitive ) || corner_name.contains( "特集", Qt::CaseInsensitive )){
			attribute = title + "-" + corner_name;
		} else {
			attribute = corner_name;
		}
	}
	for (ushort i = 0xFF1A; i < 0xFF5F; ++i) {
		attribute = attribute.replace(QChar(i), QChar(i - 0xFEE0));
	}
	for (ushort i = 0xFF10; i < 0xFF1A; ++i) {
		attribute = attribute.replace( QChar(i - 0xFEE0), QChar(i) );
	}

	attribute = attribute.remove( "【らじる文庫】" ).remove( "より" ).remove( "カルチャーラジオ " ).remove( "【恋する朗読】" ).remove( "【ラジオことはじめ】" ).remove( "【生朗読！】" );
        attribute.replace( QString::fromUtf8( "初級編" ), QString::fromUtf8( "【初級編】" ) ); attribute.replace( QString::fromUtf8( "入門編" ), QString::fromUtf8( "【入門編】" ) );
        attribute.replace( QString::fromUtf8( "中級編" ), QString::fromUtf8( "【中級編】" ) ); attribute.replace( QString::fromUtf8( "応用編" ), QString::fromUtf8( "【応用編】" ) );
	return attribute;
}

SettingsManager::SettingsManager(const QString& iniPath)
    : m_settings(iniPath, QSettings::IniFormat) {}

void SettingsManager::loadSettings() {
    m_settings.beginGroup("MainWindow");
    s.basic0 = m_settings.value("basic0", false).toBool();
    s.basic1 = m_settings.value("basic1", false).toBool();
    s.basic2 = m_settings.value("basic2", false).toBool();
    s.business1 = m_settings.value("business1", false).toBool();
    s.detailed_message = m_settings.value("detailed_message", false).toBool();
    s.enjoy = m_settings.value("enjoy", false).toBool();
    s.gendai = m_settings.value("gendai", false).toBool();
    s.kaiwa = m_settings.value("kaiwa", true).toBool();
    s.timetrial = m_settings.value("timetrial", false).toBool();
    s.skip = m_settings.value("skip", true).toBool();
    s.this_week = m_settings.value("this_week", true).toBool();
    s.thumbnail = m_settings.value("thumbnail", false).toBool();
    s.tag_space = m_settings.value("tag_space", false).toBool();

    for (int i = 0; i < 8; ++i)
        s.optional_flags[i] = m_settings.value(QString("optional_%1").arg(i+1), false).toBool();

    for (int i = 0; i < 4; ++i)
        s.special_flags[i] = m_settings.value(QString("special_%1").arg(i+1), false).toBool();

    s.audio_extension = m_settings.value("audio_extension", "m4a").toString();
    s.ffmpeg_folder = m_settings.value("ffmpeg_folder", "").toString();
    s.save_folder = m_settings.value("save_folder", "").toString();

    for (int i = 0; i < 8; ++i) {
        s.opt_titles[i] = QString::fromUtf8(m_settings.value(QString("opt_title%1").arg(i+1)).toByteArray());
        s.opt_ids[i] = m_settings.value(QString("optional%1").arg(i+1)).toString();
    }

    for (int i = 0; i < 4; ++i) {
        s.spec_titles[i] = QString::fromUtf8(m_settings.value(QString("spec_title%1").arg(i+1)).toByteArray());
        s.spec_ids[i] = m_settings.value(QString("special%1").arg(i+1)).toString();
    }

    m_settings.endGroup();
}

void SettingsManager::saveSettings() {
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("basic0", s.basic0);
    m_settings.setValue("basic1", s.basic1);
    m_settings.setValue("basic2", s.basic2);
    m_settings.setValue("business1", s.business1);
    m_settings.setValue("detailed_message", s.detailed_message);
    m_settings.setValue("enjoy", s.enjoy);
    m_settings.setValue("gendai", s.gendai);
    m_settings.setValue("kaiwa", s.kaiwa);
    m_settings.setValue("timetrial", s.timetrial);
    m_settings.setValue("skip", s.skip);
    m_settings.setValue("this_week", s.this_week);
    m_settings.setValue("thumbnail", s.thumbnail);
    m_settings.setValue("tag_space", s.tag_space);

    for (int i = 0; i < 8; ++i)
        m_settings.setValue(QString("optional_%1").arg(i+1), s.optional_flags[i]);

    for (int i = 0; i < 4; ++i)
        m_settings.setValue(QString("special_%1").arg(i+1), s.special_flags[i]);

    m_settings.setValue("audio_extension", s.audio_extension);
    m_settings.setValue("ffmpeg_folder", s.ffmpeg_folder);
    m_settings.setValue("save_folder", s.save_folder);

    for (int i = 0; i < 8; ++i) {
        m_settings.setValue(QString("opt_title%1").arg(i+1), s.opt_titles[i].toUtf8());
        m_settings.setValue(QString("optional%1").arg(i+1), s.opt_ids[i]);
    }

    for (int i = 0; i < 4; ++i) {
        m_settings.setValue(QString("spec_title%1").arg(i+1), s.spec_titles[i].toUtf8());
        m_settings.setValue(QString("special%1").arg(i+1), s.spec_ids[i]);
    }

    m_settings.endGroup();
}

/*
#include "settingsmanager.h"
#include <QSettings>
#include <QDebug>

SettingsManager::SettingsManager(AppSettings* appSettings)
    : appSettings(appSettings)
{
    // 初期化は loadSettings() を明示的に呼び出して行う
}

void SettingsManager::loadSettings(const QString& filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);

    // 通常設定の読み込み
    appSettings->enableFFmpegLog = settings.value("Settings/enableFFmpegLog", false).toBool();
    appSettings->autoStartRecording = settings.value("Settings/autoStartRecording", false).toBool();
    appSettings->saveDirectory = settings.value("Settings/saveDirectory", "").toString();
    appSettings->ffmpegPath = settings.value("Settings/ffmpegPath", "").toString();

    // チェックボックス系
    appSettings->checkBoxValues.clear();
    const int checkBoxCount = settings.beginReadArray("CheckBoxes");
    for (int i = 0; i < checkBoxCount; ++i) {
        settings.setArrayIndex(i);
        QString key = settings.value("key").toString();
        bool value = settings.value("value", false).toBool();
        appSettings->checkBoxValues[key] = value;
    }
    settings.endArray();

    // コンボボックス系
    appSettings->comboBoxIndices.clear();
    const int comboBoxCount = settings.beginReadArray("ComboBoxes");
    for (int i = 0; i < comboBoxCount; ++i) {
        settings.setArrayIndex(i);
        QString key = settings.value("key").toString();
        int index = settings.value("index", 0).toInt();
        appSettings->comboBoxIndices[key] = index;
    }
    settings.endArray();

    // IDマップの読み込み
    appSettings->id_map.clear();
    const int idMapCount = settings.beginReadArray("IdMap");
    for (int i = 0; i < idMapCount; ++i) {
        settings.setArrayIndex(i);
        QString key = settings.value("key").toString();
        QString value = settings.value("value").toString();
        appSettings->id_map[key] = value;
    }
    settings.endArray();

    // タイトルマップの読み込み
    appSettings->name_map.clear();
    const int nameMapCount = settings.beginReadArray("NameMap");
    for (int i = 0; i < nameMapCount; ++i) {
        settings.setArrayIndex(i);
        QString key = settings.value("key").toString();
        QString value = settings.value("value").toString();
        appSettings->name_map[key] = value;
    }
    settings.endArray();

    // サムネイルマップの読み込み
    appSettings->thumbnail_map.clear();
    const int thumbnailCount = settings.beginReadArray("ThumbnailMap");
    for (int i = 0; i < thumbnailCount; ++i) {
        settings.setArrayIndex(i);
        QString key = settings.value("key").toString();
        QString value = settings.value("value").toString();
        appSettings->thumbnail_map[key] = value;
    }
    settings.endArray();
}

void SettingsManager::saveSettings(const QString& filePath)
{
    QSettings settings(filePath, QSettings::IniFormat);

    // 通常設定の保存
    settings.setValue("Settings/enableFFmpegLog", appSettings->enableFFmpegLog);
    settings.setValue("Settings/autoStartRecording", appSettings->autoStartRecording);
    settings.setValue("Settings/saveDirectory", appSettings->saveDirectory);
    settings.setValue("Settings/ffmpegPath", appSettings->ffmpegPath);

    // チェックボックス系の保存
    settings.beginWriteArray("CheckBoxes");
    int i = 0;
    for (auto it = appSettings->checkBoxValues.begin(); it != appSettings->checkBoxValues.end(); ++it, ++i) {
        settings.setArrayIndex(i);
        settings.setValue("key", it.key());
        settings.setValue("value", it.value());
    }
    settings.endArray();

    // コンボボックス系の保存
    settings.beginWriteArray("ComboBoxes");
    i = 0;
    for (auto it = appSettings->comboBoxIndices.begin(); it != appSettings->comboBoxIndices.end(); ++it, ++i) {
        settings.setArrayIndex(i);
        settings.setValue("key", it.key());
        settings.setValue("index", it.value());
    }
    settings.endArray();

    // IDマップの保存
    settings.beginWriteArray("IdMap");
    i = 0;
    for (auto it = appSettings->id_map.begin(); it != appSettings->id_map.end(); ++it, ++i) {
        settings.setArrayIndex(i);
        settings.setValue("key", it.key());
        settings.setValue("value", it.value());
    }
    settings.endArray();

    // タイトルマップの保存
    settings.beginWriteArray("NameMap");
    i = 0;
    for (auto it = appSettings->name_map.begin(); it != appSettings->name_map.end(); ++it, ++i) {
        settings.setArrayIndex(i);
        settings.setValue("key", it.key());
        settings.setValue("value", it.value());
    }
    settings.endArray();

    // サムネイルマップの保存
    settings.beginWriteArray("ThumbnailMap");
    i = 0;
    for (auto it = appSettings->thumbnail_map.begin(); it != appSettings->thumbnail_map.end(); ++it, ++i) {
        settings.setArrayIndex(i);
        settings.setValue("key", it.key());
        settings.setValue("value", it.value());
    }
    settings.endArray();
}
*/
/*
#include "settingsmanager.h"
#include <QSettings>
#include <QStandardPaths>
#include <QFileInfo>

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent)
{
    loadSettings();
}

void SettingsManager::loadSettings() {
    QSettings settings;

    // CheckBox の状態を読み込み
    for (int i = 0; i < AppSettings::kCheckBoxKeys.size(); ++i) {
        const QString& key = AppSettings::kCheckBoxKeys[i];
        bool defaultValue = (i < AppSettings::kCheckBoxDefaults.size()) ? AppSettings::kCheckBoxDefaults[i] : false;
        checkBoxStates[key] = settings.value(key, defaultValue).toBool();
    }

    // ComboBox（テキスト型）の状態を読み込み
    for (int i = 0; i < AppSettings::kTextComboBoxKeys.size(); ++i) {
        const QString& key = AppSettings::kTextComboBoxKeys[i];
        const QString& defaultValue = (i < AppSettings::kTextComboBoxDefaults.size()) ? AppSettings::kTextComboBoxDefaults[i] : "";
        textComboBoxValues[key] = settings.value(key, defaultValue).toString();
    }

    // optionalIdMap 読み込み
    for (int i = 0; i < AppSettings::kOptionalIdKeys.size(); ++i) {
        const QString& key = AppSettings::kOptionalIdKeys[i];
        const QString& defaultValue = (i < AppSettings::kOptionalDefaultIds.size()) ? AppSettings::kOptionalDefaultIds[i] : "";
        optionalIdMap[key] = settings.value(key, defaultValue).toString();
    }

    // optionalTitleMap 読み込み
    for (int i = 0; i < AppSettings::kOptionalTitleKeys.size(); ++i) {
        const QString& key = AppSettings::kOptionalTitleKeys[i];
        const QString& defaultValue = (i < AppSettings::kOptionalDefaultTitles.size()) ? AppSettings::kOptionalDefaultTitles[i] : "";
        optionalTitleMap[key] = settings.value(key, defaultValue).toString();
    }

    // specialIdMap 読み込み
    for (int i = 0; i < AppSettings::kSpecialIdKeys.size(); ++i) {
        const QString& key = AppSettings::kSpecialIdKeys[i];
        const QString& defaultValue = (i < AppSettings::kSpecialDefaultIds.size()) ? AppSettings::kSpecialDefaultIds[i] : "";
        specialIdMap[key] = settings.value(key, defaultValue).toString();
    }

    // specialTitleMap 読み込み
    for (int i = 0; i < AppSettings::kSpecialTitleKeys.size(); ++i) {
        const QString& key = AppSettings::kSpecialTitleKeys[i];
        const QString& defaultValue = (i < AppSettings::kSpecialDefaultTitles.size()) ? AppSettings::kSpecialDefaultTitles[i] : "";
        specialTitleMap[key] = settings.value(key, defaultValue).toString();
    }
}

void SettingsManager::saveSettings() {
    QSettings settings;

    for (auto it = checkBoxStates.constBegin(); it != checkBoxStates.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }

    for (auto it = textComboBoxValues.constBegin(); it != textComboBoxValues.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }

    for (auto it = optionalIdMap.constBegin(); it != optionalIdMap.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }

    for (auto it = optionalTitleMap.constBegin(); it != optionalTitleMap.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }

    for (auto it = specialIdMap.constBegin(); it != specialIdMap.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }

    for (auto it = specialTitleMap.constBegin(); it != specialTitleMap.constEnd(); ++it) {
        settings.setValue(it.key(), it.value());
    }
}

void SettingsManager::resetToDefaults() {
    for (int i = 0; i < AppSettings::kCheckBoxKeys.size(); ++i) {
        checkBoxStates[AppSettings::kCheckBoxKeys[i]] = AppSettings::kCheckBoxDefaults[i];
    }

    for (int i = 0; i < AppSettings::kTextComboBoxKeys.size(); ++i) {
        textComboBoxValues[AppSettings::kTextComboBoxKeys[i]] = AppSettings::kTextComboBoxDefaults[i];
    }

    for (int i = 0; i < AppSettings::kOptionalIdKeys.size(); ++i) {
        optionalIdMap[AppSettings::kOptionalIdKeys[i]] = AppSettings::kOptionalDefaultIds[i];
    }

    for (int i = 0; i < AppSettings::kOptionalTitleKeys.size(); ++i) {
        optionalTitleMap[AppSettings::kOptionalTitleKeys[i]] = AppSettings::kOptionalDefaultTitles[i];
    }

    for (int i = 0; i < AppSettings::kSpecialIdKeys.size(); ++i) {
        specialIdMap[AppSettings::kSpecialIdKeys[i]] = AppSettings::kSpecialDefaultIds[i];
    }

    for (int i = 0; i < AppSettings::kSpecialTitleKeys.size(); ++i) {
        specialTitleMap[AppSettings::kSpecialTitleKeys[i]] = AppSettings::kSpecialDefaultTitles[i];
    }
}

const QMap<QString, bool>& SettingsManager::getCheckBoxStates() const {
    return checkBoxStates;
}

const QMap<QString, QString>& SettingsManager::getTextComboBoxValues() const {
    return textComboBoxValues;
}

const QMap<QString, QString>& SettingsManager::getOptionalIdMap() const {
    return optionalIdMap;
}

const QMap<QString, QString>& SettingsManager::getOptionalTitleMap() const {
    return optionalTitleMap;
}

const QMap<QString, QString>& SettingsManager::getSpecialIdMap() const {
    return specialIdMap;
}

const QMap<QString, QString>& SettingsManager::getSpecialTitleMap() const {
    return specialTitleMap;
}

QString SettingsManager::applicationBundlePath() {
#if defined(Q_OS_MACOS)
    QString path = QCoreApplication::applicationDirPath();
    if (path.contains(".app"))
        return path.section(".app", 0, 0).append(".app");
#endif
    return QCoreApplication::applicationDirPath();
}
*/
