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
#pragma once
#include <QString>
#include <QSettings>
#include <QMap>
#include <QVector>
#include <QByteArray>
#include "constants.h"

class Settings
{
public:
    static Settings& instance();

    void load();
    void save();

    // ===== MainWindow / MessageWindow =====
    void loadMainWindow();
    void saveMainWindow(const QByteArray &geometry);

    void loadMessageWindow();
    void saveMessageWindow(const QByteArray &geometry);

    // ===== 基本設定 =====
    QString audioExtension;
    QString ffmpegFolder;
    QString saveFolder;

    // ===== ProgramEntry の値（checked / id / label）=====
    // keyChecked → checked
    QMap<QString, bool> checked;

    // keyId → id
    QMap<QString, QString> ids;

    // keyLabel → label
    QMap<QString, QString> labels;

    // ===== optional / spec のプリセット =====
    std::array<QString, Constants::OPT_PRESET_SIZE> optionals;
    std::array<QString, Constants::PRESET_SIZE> specials;

    // ===== geometry =====
    QByteArray mainWindowGeometry;
    QByteArray messageWindowGeometry;

    // ===== CustomizeDialog =====
    QString titleFormat[Constants::ITEM_COUNT];
    QString fileNameFormat[Constants::ITEM_COUNT];

    static QString getTitleFormat(int index);
    static QString getFileNameFormat(int index);

    static void setTitleFormatValue(int index, const QString &value);
    static void setFileNameFormatValue(int index, const QString &value);

    // ===== CheckBox features =====
    static bool tagSpaceFlag();
    static bool nameSpaceFlag();
    static bool multiGuiFlag();
    static bool kozaSeparationFlag();

    static void setTagSpaceFlag(bool flag);
    static void setNameSpaceFlag(bool flag);
    static void setMultiGuiFlag(bool flag);
    static void setKozaSeparationFlag(bool flag);

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    // 内部ヘルパー
    void loadProgramEntry(const Constants::ProgramEntry &p, QSettings &ini);
    void saveProgramEntry(const Constants::ProgramEntry &p, QSettings &ini);
};

/*
#pragma once
#include <QString>
#include <QSettings>
#include "constants.h"
#include <QStringList>
#include <QVector>
#include <QByteArray>
#include <QMap>


class Settings
{
public:
    static Settings& instance();

    // 永続設定の読み書き
    void load();
    void save();

    // ウィンドウ状態
    void loadMainWindow();
    void saveMainWindow(const QByteArray &geometry);

    void loadMessageWindow();
    void saveMessageWindow(const QByteArray &geometry);

    // ===== 基本設定 =====
    QString audioExtension;
    QString ffmpegFolder;
    QString saveFolder;

    // ===== optional（8 個）=====
    QStringList optionalIds;        // optional1〜8
    QVector<bool> optionalFlags;    // optional_1〜optional_8
    QStringList optionalTitles;     // opt_title1〜8

    // ===== special（4 個）=====
    QStringList specialIds;         // special1〜4
    QVector<bool> specialFlags;     // special_1〜special_4
    QStringList specialTitles;      // spec_title1〜4

    // ===== geometry =====
    QByteArray mainWindowGeometry;
    QByteArray messageWindowGeometry;

    // ===== 結合済みを返す便利関数 =====
    QStringList allProgramIds() const;
    QVector<bool> allProgramFlags() const;
    QStringList allProgramTitles() const;
    
    // ===== English（固定番組）=====
    QMap<QString, bool> englishChecked;   // key → checked

    // ===== Optional（ユーザー編集可能）=====
    QMap<QString, bool> optionalChecked;
    QMap<QString, QString> optionalId;
    QMap<QString, QString> optionalTitle;

    // ===== Spec（特番）=====
    QMap<QString, bool> specChecked;
    QMap<QString, QString> specId;
    QMap<QString, QString> specTitle;

    // ===== CheckBox =====
    QMap<QString, bool> checkBoxChecked;
    
    static bool tagSpaceFlag();
    static bool nameSpaceFlag();
    static bool multiGuiFlag();
    static bool kozaSeparationFlag();

    static void setTagSpaceFlag(bool flag);
    static void setNameSpaceFlag(bool flag);
    static void setMultiGuiFlag(bool flag);
    static void setKozaSeparationFlag(bool flag); 
    
    // ===== optionals1〜8 ===== 
    std::array<QString, Constants::OPT_PRESET_SIZE> optionals;
    
    // ===== special1〜4 ===== 
    std::array<QString, Constants::PRESET_SIZE>  specials;
    
    // 横断 checked キャッシュ（INI に保存しない）
    QMap<QString, bool> checked;

    void buildUnifiedChecked();   // load() の後に呼ぶ
    void syncCheckedBack();       // save() の前に呼ぶ

    static void initializeDefaults(); 
  
    static QString getTitleFormat(int index);
    static QString getFileNameFormat(int index);

    void setTitleFormatValue(int index, const QString &value);
    void setFileNameFormatValue(int index, const QString &value);
    
    void setSpecChecked(const QString &key, bool value);
    void setOptionalChecked(const QString &key, bool value);
    void setEnglishChecked(const QString &key, bool value);
    void syncChecked();

private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    QString titleFormat[Constants::ITEM_COUNT];
    QString fileNameFormat[Constants::ITEM_COUNT];


};
*/
