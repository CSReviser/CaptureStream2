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
#include <QDir>
#include <QProcess>
#include <QFileInfo>
#include <QCoreApplication>

Settings::Settings()
{
    optionals.resize(Constants::getOptionalCount());
    specials.resize(Constants::getSpecCount());
    titleFormat.resize(Constants::getItemCount());
    fileNameFormat.resize(Constants::getItemCount());
}

Settings& Settings::instance()
{
    static Settings inst;
    return inst;
}

void Settings::load()
{
    QSettings ini(iniFilePath(), QSettings::IniFormat);
    
    // ===== MainWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // English / Optional / Spec / Feature をすべて読み込む
    // English
    for (int i = 0; i < Constants::getEnglishCount(); ++i) {
        loadProgramDefinition(Constants::EnglishPrograms[i], ini);
    }
    // Optional
    for (int i = 0; i < Constants::getOptionalCount(); ++i) {
        loadProgramDefinition(Constants::OptionalPrograms[i], ini);
    }
    // Spec
    for (int i = 0; i < Constants::getSpecCount(); ++i) {
        loadProgramDefinition(Constants::SpecPrograms[i], ini);
    }
    // Feature
    for (int i = 0; i < Constants::getFeatureCount(); ++i) {
        loadProgramDefinition(Constants::FeatureSettings[i], ini);
    }


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
    mainWindowPos = ini.value("pos", QPoint()).toPoint();
    mainWindowSize = ini.value("size", QSize()).toSize();

    ini.endGroup();
 
     // ===== 初期値設定（未設定の場合のみ） =====
    initDefaultSaveFolder();

    // ===== 妥当性チェック（存在しないフォルダなら空にする） =====
    validateSaveFolder();
       
    // ===== 初回起動時の OS 別初期化 =====
    initDefaultFfmpegFolder();

    // 妥当性確認（壊れたパスなら空にする）
    if (!isValidFfmpegFolder(ffmpegFolder)) {
        ffmpegFolder.clear();
    }

    // ===== MessageWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    messageWindowGeometry = ini.value("geometry").toByteArray();
    messageWindowPos = ini.value("pos", QPoint()).toPoint();
    messageWindowSize = ini.value("size", QSize()).toSize();
    ini.endGroup();

    // ===== ScrambleDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::getOptionalCount(); ++i)
        optionals[i] = ini.value(QString("optional%1").arg(i + 1), "").toString();
    ini.endGroup();

    // ===== Settingsdialog =====
    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::getSpecCount(); ++i)
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
    if (settingsDeleted)
        return;
        
    QSettings ini(iniFilePath(), QSettings::IniFormat);

    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);

    // English / Optional / Spec / Feature をすべて保存
    // English
    for (int i = 0; i < Constants::getEnglishCount(); ++i) {
        saveProgramDefinition(Constants::EnglishPrograms[i], ini);
    }

    // Optional
    for (int i = 0; i < Constants::getOptionalCount(); ++i) {
        saveProgramDefinition(Constants::OptionalPrograms[i], ini);
    }

    // Spec
    for (int i = 0; i < Constants::getSpecCount(); ++i) {
        saveProgramDefinition(Constants::SpecPrograms[i], ini);
    }

    // Feature
    for (int i = 0; i < Constants::getFeatureCount(); ++i) {
        saveProgramDefinition(Constants::FeatureSettings[i], ini);
    }

    ini.setValue(Constants::KEY_AudioExtension, audioExtension);

    if (saveFolder.isNull()) ini.remove(Constants::KEY_SaveFolder);
    else ini.setValue(Constants::KEY_SaveFolder, saveFolder);

    if (ffmpegFolder.isNull()) ini.remove(Constants::KEY_FfmpegFolder);
    else ini.setValue(Constants::KEY_FfmpegFolder, ffmpegFolder);

    ini.setValue("geometry", mainWindowGeometry);
    if (!mainWindowPos.isNull())
        ini.setValue("pos", mainWindowPos);
    else
        ini.remove("pos");

    if (mainWindowSize.isValid())
        ini.setValue("size", mainWindowSize);
    else
        ini.remove("size");

    ini.endGroup();

    // ===== MessageWindow =====
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    ini.setValue("geometry", messageWindowGeometry);
    if (!messageWindowPos.isNull())
        ini.setValue("pos", messageWindowPos);
    else
        ini.remove("pos");
    if (messageWindowSize.isValid())
        ini.setValue("size", messageWindowSize);
    else
        ini.remove("size");
    ini.endGroup();

    // ===== ScrambleDialog =====
    ini.beginGroup(Constants::SETTING_GROUP_ScrambleDialog);
    for (int i = 0; i < Constants::getOptionalCount(); ++i)
        ini.setValue(QString("optional%1").arg(i + 1), optionals[i]);
    ini.endGroup();

    // ===== Settingsdialog =====
    ini.beginGroup(Constants::SETTING_GROUP_Settingsdialog);
    for (int i = 0; i < Constants::getSpecCount(); ++i)
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
 * ProgramDefinition 読み込み
 * ============================================================ */
void Settings::loadProgramDefinition(const Constants::ProgramDefinition &p, QSettings &ini)
{
    // checked
    checked[p.keyChecked] =
        ini.value(p.keyChecked, p.checkedDefault).toBool();

    // id
    if (p.hasId) {
        if (p.saveId) {
            ids[p.keyId] = ini.value(p.keyId, p.idDefault).toString();
        } else {
            ids[p.keyId] =  QString::fromUtf8(p.idDefault);
        }
    }

    // label
    if (p.hasLabel) {
        if (p.saveLabel) {
//          labels[p.keyLabel] = ini.value(p.keyLabel, p.labelDefault).toString();
            QString raw  = ini.value(p.keyLabel, p.labelDefault).toString();
            // 旧版 ini の混入対策：UI 状態（✓）を除去
            raw.remove( QString::fromUtf8("✓ ") );
            raw.remove( QString::fromUtf8("✓") );
            raw.remove(QChar(0x2713)); // ✓

            labels[p.keyLabel] = raw;
        } else {
            labels[p.keyLabel] = QString::fromUtf8(p.labelDefault);
        }
    }
}

/* ============================================================
 * ProgramDefinition 保存
 * ============================================================ */
void Settings::saveProgramDefinition(const Constants::ProgramDefinition &p, QSettings &ini)
{
    // checked
    ini.setValue(p.keyChecked, checked[p.keyChecked]);

    // id
    if (p.saveId)
        ini.setValue(p.keyId, ids[p.keyId]);

    // label
    if (p.saveLabel)
        ini.setValue(p.keyLabel, labels[p.keyLabel]);
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
 *  CheckBox features
 * ============================================================ */
bool Settings::tagSpaceFlag()
{
    return instance().checked[Constants::KEY_TAG_SPACE];
}

bool Settings::nameSpaceFlag()
{
    return instance().checked[Constants::KEY_NAME_SPACE];
}

bool Settings::multiGuiFlag()
{
    return instance().checked[Constants::KEY_MULTI_GUI];
}

bool Settings::kozaSeparationFlag()
{
    return instance().checked[Constants::KEY_KOZA_SEPARATION];
}

void Settings::setTagSpaceFlag(bool flag)
{
    instance().checked[Constants::KEY_TAG_SPACE] = flag;
}

void Settings::setNameSpaceFlag(bool flag)
{
    instance().checked[Constants::KEY_NAME_SPACE] = flag;
}

void Settings::setMultiGuiFlag(bool flag)
{
    instance().checked[Constants::KEY_MULTI_GUI] = flag;
}

void Settings::setKozaSeparationFlag(bool flag)
{
    instance().checked[Constants::KEY_KOZA_SEPARATION] = flag;
}

void Settings::loadMainWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry,
                             const QPoint &pos,
                             const QSize &size)
{
    if (settingsDeleted)
        return;

    mainWindowGeometry = geometry;
    mainWindowPos = pos;
    mainWindowSize = size;
    
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MainWindow);
    
    ini.setValue("geometry", geometry);
    ini.setValue("pos", pos);
    ini.setValue("size", size);
    
    ini.endGroup();
}

void Settings::loadMessageWindow()
{
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMessageWindow(const QByteArray &geometry,
                                 const QPoint &pos,
                                 const QSize &size)
{
    if (settingsDeleted)
        return;
        
    messageWindowGeometry = geometry;
    messageWindowPos = pos;
    messageWindowSize = size;
    
    QSettings ini(Constants::IniFileName, QSettings::IniFormat);
    ini.beginGroup(Constants::SETTING_GROUP_MessageWindow);

    ini.setValue("geometry", geometry);
    ini.setValue("pos", pos);
    ini.setValue("size", size);
    
    ini.endGroup();
}

void Settings::initDefaultSaveFolder()
{
    if (!saveFolder.isEmpty())
        return;  // すでに設定済みなら何もしない

#ifdef Q_OS_WIN
    saveFolder = QCoreApplication::applicationDirPath();
#elif defined(Q_OS_MAC)
//    saveFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    saveFolder.clear();
#elif defined(Q_OS_LINUX)
    saveFolder = QCoreApplication::applicationDirPath();
#else
    saveFolder = QDir::homePath();
#endif

    // 最後は必ず末尾にセパレータを付ける
    if (!saveFolder.endsWith(QDir::separator()))
        saveFolder += QDir::separator();
}

void Settings::validateSaveFolder()
{
    if (saveFolder.isEmpty())
        return;

    QDir dir(saveFolder);

    // フォルダが存在しない場合は空にする
    if (!dir.exists()) {
        saveFolder.clear();
        return;
    }

    // 書き込み可能かどうかの最低限チェック
    QFileInfo testFile(dir.filePath(".__cs2_test__"));
    QFile f(testFile.absoluteFilePath());

    if (f.open(QIODevice::WriteOnly)) {
        f.close();
        f.remove();  // テストファイル削除
    } else {
        // 書き込み不可 → 空にする
        saveFolder.clear();
    }
}

void Settings::initDefaultFfmpegFolder()
{
    if (!ffmpegFolder.isEmpty())
        return;  // すでに設定済み

    // OS別に自動探索
    QString detected = autoDetectFfmpeg();
    if (!detected.isEmpty()) {
        ffmpegFolder = detected;
        return;
    }

    // 見つからなければ空のまま（MainWindow がダイアログを出す）
    ffmpegFolder.clear();
}

QString Settings::autoDetectFfmpeg()
{
    QProcess process;
    QString ffmpegPath;

#ifdef Q_OS_WIN
    process.start("cmd.exe", QStringList() << "/c" << "where" << "ffmpeg");
#else
    process.start("which", QStringList() << "ffmpeg");
#endif
    process.waitForFinished();

    ffmpegPath = QString::fromUtf8(process.readAllStandardOutput())
                     .split("\n").first().trimmed();

    if (!QFileInfo::exists(ffmpegPath)) {
#ifdef Q_OS_MAC
        QString arch = QSysInfo::buildCpuArchitecture();
        if (arch == "x86_64") {
            ffmpegPath = "/usr/local/bin/ffmpeg";
        } else if (arch == "arm64") {
            ffmpegPath = "/opt/homebrew/bin/ffmpeg";
            if (!QFile::exists(ffmpegPath))
                ffmpegPath = "/usr/local/bin/ffmpeg";
        }
#elif defined(Q_OS_LINUX)
        ffmpegPath = "/usr/bin/ffmpeg";
#elif defined(Q_OS_WIN)
        ffmpegPath = "C:\\Program Files\\ffmpeg\\bin\\ffmpeg.exe";
        if (!QFile::exists(ffmpegPath))
            ffmpegPath = "C:\\ffmpeg\\bin\\ffmpeg.exe";
#endif
    }

    if (QFile::exists(ffmpegPath))
        return QFileInfo(ffmpegPath).absolutePath();

    return QString();
}

bool Settings::isValidFfmpegFolder(const QString& folder) const
{
    if (folder.isEmpty())
        return false;

    QDir dir(folder);
    if (!dir.exists())
        return false;

#ifdef Q_OS_WIN
    QString exe = dir.filePath("ffmpeg.exe");
#else
    QString exe = dir.filePath("ffmpeg");
#endif

    if (!QFileInfo::exists(exe))
        return false;

    return canExecuteFfmpeg(exe);
}

bool Settings::canExecuteFfmpeg(const QString& ffmpegPath) const
{
    QProcess p;
    p.start(ffmpegPath, {"-version"});
    if (!p.waitForFinished(1500))  // タイムアウト短めでOK
        return false;

    return (p.exitStatus() == QProcess::NormalExit);
}

QString Settings::detectFfmpegFolder()
{
    return autoDetectFfmpeg();   // private 関数を内部で呼ぶ
}

QString Settings::iniFilePath()
{
#ifdef Q_OS_MACOS
    QString dir =
        QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    return dir + QDir::separator() + Constants::IniFileName;
#else
    QString dir = QCoreApplication::applicationDirPath();
    return dir + QDir::separator() + Constants::IniFileName;
#endif
}

bool Settings::settingsDeleted = false;

bool Settings::deleteSettingsFile()
{
    QString path = iniFilePath();

    if (QFile::exists(path))
        QFile::remove(path);

    settingsDeleted = true;
    return true;
}

