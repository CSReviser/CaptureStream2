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
}

Settings& Settings::instance()
{
    static Settings inst;
    return inst;
}

void Settings::load()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    // ===== MainWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // English / Optional / Spec / Flag をすべて読み込む
    for (const auto &p : Constants::EnglishPrograms) loadProgramEntry(p, ini);
    for (const auto &p : Constants::OptionalPrograms) loadProgramEntry(p, ini);
    for (const auto &p : Constants::SpecPrograms)     loadProgramEntry(p, ini);
    for (const auto &p : Constants::FlagSettings)     loadProgramEntry(p, ini);

    // audioExtension
    audioExtension = ini.value(Constants::KEY_AudioExtension,
                               Constants::DEFAULT_AudioExtension).toString();

    // saveFolder（null 許容）
    {
        QVariant v = ini.value(Constants::KEY_SaveFolder);
        saveFolder = v.isValid() ? v.toString() : QString();
    }

    // ffmpegFolder（null 許容）
    {
        QVariant v = ini.value(Constants::KEY_FfmpegFolder);
        ffmpegFolder = v.isValid() ? v.toString() : QString();
    }

    mainWindowGeometry = ini.value("geometry").toByteArray();

    ini.endGroup();

    // ===== MessageWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();

    // ===== ScrambleDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i)
        optionals[i] = ini.value(QString("optional%1").arg(i + 1), "").toString();
    ini.endGroup();

    // ===== Settingsdialog =====
    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        specials[i] = ini.value(QString("special%1").arg(i + 1), "").toString();
    ini.endGroup();

    // ===== CustomizeDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_CustomizeDialog);
    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        const auto &t = Constants::TITLE_ITEMS[i];
        titleFormat[i] = ini.value(t.key, t.defaultValue).toString();

        const auto &f = Constants::FILENAME_ITEMS[i];
        fileNameFormat[i] = ini.value(f.key, f.defaultValue).toString();
    }
    ini.endGroup();
}

void Settings::save()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // English / Optional / Spec / Flag をすべて保存
    for (const auto &p : Constants::EnglishPrograms) saveProgramEntry(p, ini);
    for (const auto &p : Constants::OptionalPrograms) saveProgramEntry(p, ini);
    for (const auto &p : Constants::SpecPrograms)     saveProgramEntry(p, ini);
    for (const auto &p : Constants::FlagSettings)     saveProgramEntry(p, ini);

    ini.setValue(Constants::KEY_AudioExtension, audioExtension);

    if (saveFolder.isNull()) ini.remove(Constants::KEY_SaveFolder);
    else ini.setValue(Constants::KEY_SaveFolder, saveFolder);

    if (ffmpegFolder.isNull()) ini.remove(Constants::KEY_FfmpegFolder);
    else ini.setValue(Constants::KEY_FfmpegFolder, ffmpegFolder);

    ini.setValue("geometry", mainWindowGeometry);

    ini.endGroup();

    // ===== MessageWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    ini.setValue("geometry", messageWindowGeometry);
    ini.endGroup();

    // ===== ScrambleDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i)
        ini.setValue(QString("optional%1").arg(i + 1), optionals[i]);
    ini.endGroup();

    // ===== Settingsdialog =====
    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        ini.setValue(QString("special%1").arg(i + 1), specials[i]);
    ini.endGroup();

    // ===== CustomizeDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_CustomizeDialog);
    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        const auto &t = Constants::TITLE_ITEMS[i];
        ini.setValue(t.key, titleFormat[i]);

        const auto &f = Constants::FILENAME_ITEMS[i];
        ini.setValue(f.key, fileNameFormat[i]);
    }
    ini.endGroup();
}

/* ============================================================
 * ProgramEntry 読み込み
 * ============================================================ */
void Settings::loadProgramEntry(const Constants::ProgramEntry &p, QSettings &ini)
{
    // enabled
    enabled[p.keyEnabled] =
        ini.value(p.keyEnabled, p.enabledDefault).toBool();

    // id
    if (!p.keyId.isEmpty())
        ids[p.keyId] = ini.value(p.keyId, p.idDefault).toString();

    // title
    if (!p.keyTitle.isEmpty())
        titles[p.keyTitle] = ini.value(p.keyTitle, p.titleDefault).toString();
}

/* ============================================================
 * ProgramEntry 保存
 * ============================================================ */
void Settings::saveProgramEntry(const Constants::ProgramEntry &p, QSettings &ini)
{
    ini.setValue(p.keyEnabled, enabled[p.keyEnabled]);

    if (!p.keyId.isEmpty())
        ini.setValue(p.keyId, ids[p.keyId]);

    if (!p.keyTitle.isEmpty())
        ini.setValue(p.keyTitle, titles[p.keyTitle]);
}

/* ============================================================
 *  CustomizeDialog API
 * ============================================================ */
QString Settings::getTitleFormat(int index)
{
    return instance().titleFormat[index];
}

QString Settings::getFileNameFormat(int index)
{
    return instance().fileNameFormat[index];
}

void Settings::setTitleFormatValue(int index, const QString &value)
{
    instance().titleFormat[index] = value;
}

void Settings::setFileNameFormatValue(int index, const QString &value)
{
    instance().fileNameFormat[index] = value;
}

/* ============================================================
 *  CheckBox flags
 * ============================================================ */
bool Settings::tagSpaceFlag()
{
    return instance().enabled[Constants::KEY_TAG_SPACE];
}

bool Settings::nameSpaceFlag()
{
    return instance().enabled[Constants::KEY_NAME_SPACE];
}

bool Settings::multiGuiFlag()
{
    return instance().enabled[Constants::KEY_MULTI_GUI];
}

bool Settings::kozaSeparationFlag()
{
    return instance().enabled[Constants::KEY_KOZA_SEPARATION];
}

void Settings::setTagSpaceFlag(bool flag)
{
    instance().enabled[Constants::KEY_TAG_SPACE] = flag;
}

void Settings::setNameSpaceFlag(bool flag)
{
    instance().enabled[Constants::KEY_NAME_SPACE] = flag;
}

void Settings::setMultiGuiFlag(bool flag)
{
    instance().enabled[Constants::KEY_MULTI_GUI] = flag;
}

void Settings::setKozaSeparationFlag(bool flag)
{
    instance().enabled[Constants::KEY_KOZA_SEPARATION] = flag;
}

void Settings::loadMainWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry)
{
    mainWindowGeometry = geometry;
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
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



/*
#include "settings.h"
#include <QSettings>

Settings::Settings()
{
    // 何もせず load() に任せる
}

Settings& Settings::instance()
{
    static Settings inst;
    return inst;
}

void Settings::load()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

     // ===== English（固定番組）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];
        englishEnabled[p.key] =
            ini.value(p.key, p.enabled).toBool();
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
        const auto &c = Constants::CheckBoxSettings[i];
        checkBoxEnabled[c.keyEnabled] =
            ini.value(c.keyEnabled, c.enabledDefault).toBool();
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

    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i) {
        optionals[i] = ini.value(QString("optional%1").arg(i + 1), "").toString();
    }
    ini.endGroup();

    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::PRESET_SIZE; ++i) {
        specials[i] = ini.value(QString("special%1").arg(i + 1), "").toString();
    }
    ini.endGroup();

    // ===== CustomizeDialog: TITLE / FILENAME =====
    ini.beginGroup(Constants::SETTING_GROUP_CustomizeDialog);

    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        const auto &t = Constants::TITLE_ITEMS[i];
        titleFormat[i] = ini.value(t.key, t.defaultValue).toString();

        const auto &f = Constants::FILENAME_ITEMS[i];
        fileNameFormat[i] = ini.value(f.key, f.defaultValue).toString();
    }

    ini.endGroup();
    
    buildUnifiedEnabled();

}

void Settings::save()
{
    syncEnabledBack();

    QSettings ini(Constants::IniFileName, QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // ===== English（固定番組）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];
        ini.setValue(p.key, englishEnabled[p.key]);
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
        const auto &c = Constants::CheckBoxSettings[i];
        ini.setValue(c.keyEnabled, checkBoxEnabled[c.keyEnabled]);
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

    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i) {
        ini.setValue(QString("optional%1").arg(i + 1), optionals[i]);
    }
    ini.endGroup();

    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::PRESET_SIZE; ++i) {
        ini.setValue(QString("special%1").arg(i + 1), specials[i]);
    }
    ini.endGroup();
    
    // ===== CustomizeDialog: TITLE / FILENAME =====
    ini.beginGroup(Constants::SETTING_GROUP_CustomizeDialog);

    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        const auto &t = Constants::TITLE_ITEMS[i];
        ini.setValue(t.key, titleFormat[i]);

        const auto &f = Constants::FILENAME_ITEMS[i];
        ini.setValue(f.key, fileNameFormat[i]);
    }

    ini.endGroup();

}

void Settings::loadMainWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry)
{
    mainWindowGeometry = geometry;
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
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

void Settings::buildUnifiedEnabled()
{
    enabled.clear();

    // English
    for (const auto& p : Constants::EnglishPrograms) {
        enabled[p.key] = englishEnabled[p.key];
    }

    // Optional
    for (const auto& p : Constants::OptionalPrograms) {
        enabled[p.keyEnabled] = optionalEnabled[p.keyEnabled];
    }

    // Spec
    for (const auto& p : Constants::SpecPrograms) {
        enabled[p.keyEnabled] = specEnabled[p.keyEnabled];
    }

    // CheckBox
    for (const auto& c : Constants::CheckBoxSettings) {
        enabled[c.keyEnabled] = checkBoxEnabled[c.keyEnabled];
    }
}


void Settings::syncEnabledBack()
{
    // English
    for (const auto& p : Constants::EnglishPrograms) {
        englishEnabled[p.key] = enabled[p.key];
    }

    // Optional
    for (const auto& p : Constants::OptionalPrograms) {
        optionalEnabled[p.keyEnabled] = enabled[p.keyEnabled];
    }

    // Spec
    for (const auto& p : Constants::SpecPrograms) {
        specEnabled[p.keyEnabled] = enabled[p.keyEnabled];
    }

    // CheckBox
    for (const auto& c : Constants::CheckBoxSettings) {
        checkBoxEnabled[c.keyEnabled] = enabled[c.keyEnabled];
    }
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
*/
/* ============================================================
 *  CustomizeDialog API
 * ============================================================ */
/*
QString Settings::getTitleFormat(int index)
{
    return instance().titleFormat[index];
}

QString Settings::getFileNameFormat(int index)
{
    return instance().fileNameFormat[index];
}

void Settings::setTitleFormatValue(int index, const QString &value)
{
    instance().titleFormat[index] = value;
}

void Settings::setFileNameFormatValue(int index, const QString &value)
{
    instance().fileNameFormat[index] = value;
}
*/
/* ============================================================
 *  CheckBox flags
 * ============================================================ */
/*
bool Settings::tagSpaceFlag()
{
    return instance().checkBoxEnabled[Constants::KEY_TAG_SPACE];
}

bool Settings::nameSpaceFlag()
{
    return instance().checkBoxEnabled[Constants::KEY_NAME_SPACE];
}

bool Settings::multiGuiFlag()
{
    return instance().checkBoxEnabled[Constants::KEY_MULTI_GUI];
}

bool Settings::kozaSeparationFlag()
{
    return instance().checkBoxEnabled[Constants::KEY_KOZA_SEPARATION];
}

void Settings::setTagSpaceFlag(bool flag)
{
    instance().checkBoxEnabled[Constants::KEY_TAG_SPACE] = flag;
}

void Settings::setNameSpaceFlag(bool flag)
{
    instance().checkBoxEnabled[Constants::KEY_NAME_SPACE] = flag;
}

void Settings::setMultiGuiFlag(bool flag)
{
    instance().checkBoxEnabled[Constants::KEY_MULTI_GUI] = flag;
}

void Settings::setKozaSeparationFlag(bool flag)
{
    instance().checkBoxEnabled[Constants::KEY_KOZA_SEPARATION] = flag;
}

void Settings::syncEnabled()
{
    enabled.clear();

    for (auto it = specEnabled.begin(); it != specEnabled.end(); ++it)
        enabled[it.key()] = it.value();

    for (auto it = optionalEnabled.begin(); it != optionalEnabled.end(); ++it)
        enabled[it.key()] = it.value();

    for (auto it = englishEnabled.begin(); it != englishEnabled.end(); ++it)
        enabled[it.key()] = it.value();
}

void Settings::setSpecEnabled(const QString &key, bool value)
{
    specEnabled[key] = value;
    syncEnabled();
}

void Settings::setOptionalEnabled(const QString &key, bool value)
{
    optionalEnabled[key] = value;
    syncEnabled();
}

void Settings::setEnglishEnabled(const QString &key, bool value)
{
    englishEnabled[key] = value;
    syncEnabled();
}
*/
