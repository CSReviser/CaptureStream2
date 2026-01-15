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
 
    // ===== その他設定（null 許容）=====

    // audioExtension は null 不要（常に文字列）
    audioExtension = ini.value(Constants::KEY_AudioExtension, Constants::DEFAULT_AudioExtension).toString();

    // saveFolder（キーが無ければ null）
    {
        QVariant v = ini.value(Constants::KEY_SaveFolder);
        saveFolder = v.isValid() ? v.toString() : QString();  // null QString
    }

    // ffmpegFolder（キーが無ければ null）
    {
        QVariant v = ini.value(Constants::KEY_FfmpegFolder);
        ffmpegFolder = v.isValid() ? v.toString() : QString();  // null QString
    }

    // MainWindow geometry
    mainWindowGeometry = ini.value("geometry").toByteArray();

    ini.endGroup();

    // MessageWindow
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    messageWindowGeometry = ini.value("geometry").toByteArray();
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

    // ===== その他設定（null 許容）=====

    ini.setValue(Constants::KEY_AudioExtension, audioExtension);

    // saveFolder が null → キー削除
    if (saveFolder.isNull()) {
        ini.remove(Constants::KEY_SaveFolder);
    } else {
        ini.setValue(Constants::KEY_SaveFolder, saveFolder);
    }

    // ffmpegFolder が null → キー削除
    if (ffmpegFolder.isNull()) {
        ini.remove(Constants::KEY_FfmpegFolder);
    } else {
        ini.setValue(Constants::KEY_FfmpegFolder, ffmpegFolder);
    }

    ini.setValue("geometry", mainWindowGeometry);

    ini.endGroup();

    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    ini.setValue("geometry", messageWindowGeometry);
    ini.endGroup();
}

void Settings::loadMainWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry)
{
    mainWindowGeometry = geometry;
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    ini.setValue("geometry", geometry);
    ini.endGroup();
}

void Settings::loadMessageWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMessageWindow(const QByteArray &geometry)
{
    messageWindowGeometry = geometry;
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
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




#pragma once
#include <QString>
#include <QMap>

class Settings
{
public:
    // ===== English（固定番組）=====
    QMap<QString, bool> englishEnabled;   // key → enabled

    // ===== Optional（ユーザー編集可能）=====
    QMap<QString, bool> optionalEnabled;
    QMap<QString, QString> optionalId;
    QMap<QString, QString> optionalTitle;

    // ===== Spec（特番）=====
    QMap<QString, bool> specEnabled;
    QMap<QString, QString> specId;
    QMap<QString, QString> specTitle;

    // ===== CheckBox =====
    QMap<QString, bool> checkBoxEnabled;

    // ===== その他 =====
    QString saveFolder;
    QString ffmpegFolder;
    QString audioExtension;

public:
    void load();
    void save();
};







#include "settings.h"
#include "constants.h"
#include <QSettings>

void Settings::load()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    // ===== English（固定番組）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];
        englishEnabled[p.key] =
            ini.value(p.key + "_enabled", p.enabled).toBool();
    }

    // ===== Optional（ユーザー編集可能）=====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optionalEnabled[p.keyEnabled] =
            ini.value(p.keyEnabled, p.enabledDefault).toBool();

        optionalId[p.keyId] =
            ini.value(p.keyId, p.idDefault).toString();

        optionalTitle[p.keyTitle] =
            ini.value(p.keyTitle, p.titleDefault).toString();
    }

    // ===== Spec（特番）=====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        specEnabled[p.keyEnabled] =
            ini.value(p.keyEnabled, p.enabledDefault).toBool();

        specId[p.keyId] =
            ini.value(p.keyId, p.idDefault).toString();

        specTitle[p.keyTitle] =
            ini.value(p.keyTitle, p.titleDefault).toString();
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &c = Constants::checkBoxes[i];
        checkBoxEnabled[c.keyEnabled] =
            ini.value(c.keyEnabled, c.enabledDefault).toBool();
    }

    // ===== その他 =====
    saveFolder = ini.value(Constants::KEY_SaveFolder, "").toString();
    ffmpegFolder = ini.value(Constants::KEY_FfmpegFolder, "").toString();
    audioExtension = ini.value(Constants::KEY_AudioExtension,
                               Constants::DEFAULT_AudioExtension).toString();
}

void Settings::save()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    // ===== English（固定番組）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];
        ini.setValue(p.key + "_enabled", englishEnabled[p.key]);
    }

    // ===== Optional（ユーザー編集可能）=====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        ini.setValue(p.keyEnabled, optionalEnabled[p.keyEnabled]);
        ini.setValue(p.keyId,      optionalId[p.keyId]);
        ini.setValue(p.keyTitle,   optionalTitle[p.keyTitle]);
    }

    // ===== Spec（特番）=====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        ini.setValue(p.keyEnabled, specEnabled[p.keyEnabled]);
        ini.setValue(p.keyId,      specId[p.keyId]);
        ini.setValue(p.keyTitle,   specTitle[p.keyTitle]);
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &c = Constants::checkBoxes[i];
        ini.setValue(c.keyEnabled, checkBoxEnabled[c.keyEnabled]);
    }

    // ===== その他 =====
    ini.setValue(Constants::KEY_SaveFolder, saveFolder);
    ini.setValue(Constants::KEY_FfmpegFolder, ffmpegFolder);
    ini.setValue(Constants::KEY_AudioExtension, audioExtension);
}
