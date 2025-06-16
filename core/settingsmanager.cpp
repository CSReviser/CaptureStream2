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

#include "settingsmanager.h"

SettingsManager::SettingsManager()
    : settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())
{
#ifdef Q_OS_MACOS
    QString iniPath = Utility::ConfigLocationPath();
#else
    QString iniPath = Utility::applicationBundlePath();
#endif
    iniPath += QDir::separator() + QStringLiteral("CaptureStream2.ini");

    settings = QSettings(iniPath, QSettings::IniFormat);
}

void SettingsManager::load() {
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
}

void SettingsManager::save() {
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
}

void SettingsManager::load() {
	QSettings settings;
	m_checkBoxSettings.clear();

	for (int i = 0; i < kCheckBoxKeys.size(); ++i) {
		QString key = kCheckBoxKeys[i];
		bool def = kCheckBoxDefaults[i];
		bool val = settings.value(key, def).toBool();
		m_checkBoxSettings.append({ key, val, def });
	}
}

void SettingsManager::save() {
	QSettings settings;
	for (const auto& entry : m_checkBoxSettings) {
		settings.setValue(entry.key, entry.value);
	}
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





void SettingsManager::load() {
    // チェックボックス読み込み
    for (int i = 0; i < kCheckBoxKeys.size(); ++i) {
        QString key = kCheckBoxKeys[i];
        bool defVal = kCheckBoxDefaults[i];
        checkBoxStates[key] = settings.value(key, defVal).toBool();
    }

    // テキストコンボボックス読み込み
    for (int i = 0; i < kTextComboBoxKeys.size(); ++i) {
        QString key = kTextComboBoxKeys[i];
        QString defVal = kTextComboBoxDefaults[i];
        textComboBoxValues[key] = settings.value(key, defVal).toString();
    }

    // 他の設定も必要なら同様に読み込む
    saveFolder = settings.value("save_folder", "").toString();
    ffmpegFolder = settings.value("ffmpeg_folder", "").toString();
    fileName1 = settings.value("file_name1", "%k_%Y_%M_%D.m4a").toString();
    fileName2 = settings.value("file_name2", "%f").toString();
}

void SettingsManager::save() {
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
