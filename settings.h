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
#include <QStandardPaths>
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

    // ===== ProgramDefinition の値（checked / id / label）=====
    // keyChecked → checked
    QMap<QString, bool> checked;

    // keyId → id
    QMap<QString, QString> ids;

    // keyLabel → label
    QMap<QString, QString> labels;

    // ===== optional / spec のプリセット =====
    QVector<QString> optionals;
    QVector<QString> specials;

    // ===== geometry =====
    QByteArray mainWindowGeometry;
    QByteArray messageWindowGeometry;

    // ===== CustomizeDialog =====
    QVector<QString> titleFormat;
    QVector<QString> fileNameFormat;

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
    
    QString detectFfmpegFolder();   // MainWindow から呼べる
    static bool deleteSettingsFile();
    
private:
    Settings();
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    static QString iniFilePath();
    void initDefaultSaveFolder();          // OS別初期値設定
    void validateSaveFolder();             // 妥当性チェック
    void initDefaultFfmpegFolder();
    QString autoDetectFfmpeg();   // OS別探索
    bool isValidFfmpegFolder(const QString& folder) const;
    bool canExecuteFfmpeg(const QString& ffmpegPath) const; 
     
    // 内部ヘルパー
    void loadProgramDefinition(const Constants::ProgramDefinition &p, QSettings &ini);
    void saveProgramDefinition(const Constants::ProgramDefinition &p, QSettings &ini);
};


