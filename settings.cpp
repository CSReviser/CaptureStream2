/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2026 CSReviser Team

	This file is part of CaptureStream2, a recorder that supports HLS for 
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

#include "settings.h"
#include <QSettings>

Settings::Settings()
{
    // 何もせず load() に任せる
}

void Settings::load()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    // ===== 英語講座（enabled のみ）=====
    ini.beginGroup("mainWindow");
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        englishEnabled[i] = ini.value(def.key, def.enabled).toBool();
    }
    ini.endGroup();

    // ===== Optional（enabled, id, title）=====
    ini.beginGroup("optional");
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &def = Constants::OptionalPrograms[i];

        optionalEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
        optionalId[i]      = ini.value(def.keyId,      def.idDefault).toString();
        optionalTitle[i]   = ini.value(def.keyTitle,   def.titleDefault).toString();
    }
    ini.endGroup();

    // ===== Spec（enabled, id, title）=====
    ini.beginGroup("special");
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &def = Constants::SpecPrograms[i];

        specEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
        specId[i]      = ini.value(def.keyId,      def.idDefault).toString();
        specTitle[i]   = ini.value(def.keyTitle,   def.titleDefault).toString();
    }
    ini.endGroup();

    // ===== CheckBox =====
    ini.beginGroup("flags");
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &def = Constants::checkBoxes[i];
        checkBoxEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
    }
    ini.endGroup();
}




Settings::Settings()
{
    // optional / special の配列サイズを初期化
    optionalIds.resize(8);
    optionalFlags.resize(8);
    optionalTitles.resize(8);

    specialIds.resize(4);
    specialFlags.resize(4);
    specialTitles.resize(4);
}

void Settings::load()
{
    QSettings ini("settings.ini", QSettings::IniFormat);

    ini.beginGroup("MainWindow");

    audioExtension     = ini.value("audio_extension", "m4a").toString();
    ffmpegFolder       = ini.value("ffmpeg_folder").toString();
    saveFolder         = ini.value("save_folder").toString();

    skip              = ini.value("skip", false).toBool();
    thumbnail         = ini.value("thumbnail", false).toBool();
    tagSpace          = ini.value("tag_space", false).toBool();
    nameSpace         = ini.value("name_space", false).toBool();
    kozaSeparation    = ini.value("koza_separation", false).toBool();
    multiGui          = ini.value("multi_gui", false).toBool();
    thisWeek          = ini.value("this_week", false).toBool();
    timetrial         = ini.value("timetrial", false).toBool();
    detailedMessage   = ini.value("detailed_message", false).toBool();

    // basic 系
    basic0 = ini.value("basic0", false).toBool();
    basic1 = ini.value("basic1", false).toBool();
    basic2 = ini.value("basic2", false).toBool();
    business1 = ini.value("business1", false).toBool();
    enjoy = ini.value("enjoy", false).toBool();
    gendai = ini.value("gendai", false).toBool();
    kaiwa = ini.value("kaiwa", false).toBool();

    // optional（8 個）
    for (int i = 0; i < 8; i++) {
        optionalIds[i]    = ini.value(QString("optional%1").arg(i+1)).toString();
        optionalFlags[i]  = ini.value(QString("optional_%1").arg(i+1), false).toBool();
        optionalTitles[i] = ini.value(QString("opt_title%1").arg(i+1)).toByteArray();
    }

    // special（4 個）
    for (int i = 0; i < 4; i++) {
        specialIds[i]     = ini.value(QString("special%1").arg(i+1)).toString();
        specialFlags[i]   = ini.value(QString("special_%1").arg(i+1), false).toBool();
        specialTitles[i]  = ini.value(QString("spec_title%1").arg(i+1)).toByteArray();
    }

    // MainWindow geometry
    mainWindowGeometry = ini.value("geometry").toByteArray();

    ini.endGroup();

    // MessageWindow
    ini.beginGroup("MessageWindow");
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::save()
{
    QSettings ini("settings.ini", QSettings::IniFormat);

    ini.beginGroup("MainWindow");

    ini.setValue("audio_extension", audioExtension);
    ini.setValue("ffmpeg_folder", ffmpegFolder);
    ini.setValue("save_folder", saveFolder);

    ini.setValue("skip", skip);
    ini.setValue("thumbnail", thumbnail);
    ini.setValue("tag_space", tagSpace);
    ini.setValue("name_space", nameSpace);
    ini.setValue("koza_separation", kozaSeparation);
    ini.setValue("multi_gui", multiGui);
    ini.setValue("this_week", thisWeek);
    ini.setValue("timetrial", timetrial);
    ini.setValue("detailed_message", detailedMessage);

    ini.setValue("basic0", basic0);
    ini.setValue("basic1", basic1);
    ini.setValue("basic2", basic2);
    ini.setValue("business1", business1);
    ini.setValue("enjoy", enjoy);
    ini.setValue("gendai", gendai);
    ini.setValue("kaiwa", kaiwa);

    // optional（8 個）
    for (int i = 0; i < 8; i++) {
        ini.setValue(QString("optional%1").arg(i+1), optionalIds[i]);
        ini.setValue(QString("optional_%1").arg(i+1), optionalFlags[i]);
        ini.setValue(QString("opt_title%1").arg(i+1), optionalTitles[i]);
    }

    // special（4 個）
    for (int i = 0; i < 4; i++) {
        ini.setValue(QString("special%1").arg(i+1), specialIds[i]);
        ini.setValue(QString("special_%1").arg(i+1), specialFlags[i]);
        ini.setValue(QString("spec_title%1").arg(i+1), specialTitles[i]);
    }

    ini.setValue("geometry", mainWindowGeometry);

    ini.endGroup();

    ini.beginGroup("MessageWindow");
    ini.setValue("geometry", messageWindowGeometry);
    ini.endGroup();
}

void Settings::loadMainWindow()
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MainWindow");
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry)
{
    mainWindowGeometry = geometry;
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MainWindow");
    ini.setValue("geometry", geometry);
    ini.endGroup();
}

void Settings::loadMessageWindow()
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MessageWindow");
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMessageWindow(const QByteArray &geometry)
{
    messageWindowGeometry = geometry;
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MessageWindow");
    ini.setValue("geometry", geometry);
    ini.endGroup();
}

// ===== 結合済みを返す関数 =====

QStringList Settings::allProgramIds() const
{
    return optionalIds + specialIds;
}

QVector<bool> Settings::allProgramFlags() const
{
    return optionalFlags + specialFlags;
}

QStringList Settings::allProgramTitles() const
{
    return optionalTitles + specialTitles;
}






void Settings::save()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    // ===== 英語講座 =====
    ini.beginGroup("mainWindow");
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        ini.setValue(def.key, englishEnabled[i]);
    }
    ini.endGroup();

    // ===== Optional =====
    ini.beginGroup("optional");
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &def = Constants::OptionalPrograms[i];

        ini.setValue(def.keyEnabled, optionalEnabled[i]);
        ini.setValue(def.keyId,      optionalId[i]);
        ini.setValue(def.keyTitle,   optionalTitle[i]);
    }
    ini.endGroup();

    // ===== Spec =====
    ini.beginGroup("special");
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &def = Constants::SpecPrograms[i];

        ini.setValue(def.keyEnabled, specEnabled[i]);
        ini.setValue(def.keyId,      specId[i]);
        ini.setValue(def.keyTitle,   specTitle[i]);
    }
    ini.endGroup();

    // ===== CheckBox =====
    ini.beginGroup("flags");
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &def = Constants::checkBoxes[i];
        ini.setValue(def.keyEnabled, checkBoxEnabled[i]);
    }
    ini.endGroup();
}


void Settings::load()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // ===== 英語講座 =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        englishEnabled[i] = ini.value(def.key, def.enabled).toBool();
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &def = Constants::OptionalPrograms[i];

        optionalEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
        optionalId[i]      = ini.value(def.keyId,      def.idDefault).toString();
        optionalTitle[i]   = ini.value(def.keyTitle,   def.titleDefault).toString();
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &def = Constants::SpecPrograms[i];

        specEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
        specId[i]      = ini.value(def.keyId,      def.idDefault).toString();
        specTitle[i]   = ini.value(def.keyTitle,   def.titleDefault).toString();
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &def = Constants::checkBoxes[i];
        checkBoxEnabled[i] = ini.value(def.keyEnabled, def.enabledDefault).toBool();
    }

    ini.endGroup();
}

void Settings::save()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // ===== 英語講座 =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        ini.setValue(def.key, englishEnabled[i]);
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &def = Constants::OptionalPrograms[i];

        ini.setValue(def.keyEnabled, optionalEnabled[i]);
        ini.setValue(def.keyId,      optionalId[i]);
        ini.setValue(def.keyTitle,   optionalTitle[i]);
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &def = Constants::SpecPrograms[i];

        ini.setValue(def.keyEnabled, specEnabled[i]);
        ini.setValue(def.keyId,      specId[i]);
        ini.setValue(def.keyTitle,   specTitle[i]);
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &def = Constants::checkBoxes[i];
        ini.setValue(def.keyEnabled, checkBoxEnabled[i]);
    }

    ini.endGroup();
}

