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
#include "constants.h"
#include <QStringList>
#include <QVector>
#include <QByteArray>

class Settings
{
public:
    Settings();

    // 永続設定の読み書き
    void load();
    void save();

    // ===== 英語講座（固定：enabled のみ保存）=====
    bool englishEnabled[Constants::EnglishCount];

    // ===== Optional（editable：enabled, id, title を保存）=====
    QString optionalId[Constants::OptionalCount];
    QString optionalTitle[Constants::OptionalCount];
    bool    optionalEnabled[Constants::OptionalCount];

    // ===== Spec（editable：enabled, id, title を保存）=====
    QString specId[Constants::SpecialCount];
    QString specTitle[Constants::SpecialCount];
    bool    specEnabled[Constants::SpecialCount];

    // ===== CheckBox（enabled のみ保存）=====
    bool checkBoxEnabled[Constants::CheckBoxCount];

    // ウィンドウ状態
    void loadMainWindow();
    void saveMainWindow(const QByteArray &geometry);

    void loadMessageWindow();
    void saveMessageWindow(const QByteArray &geometry);

    // ===== 基本設定 =====
    QString audioExtension;
    QString ffmpegFolder;
    QString saveFolder;

    bool skip = false;
    bool thumbnail = false;
    bool tagSpace = false;
    bool nameSpace = false;
    bool kozaSeparation = false;
    bool multiGui = false;
    bool thisWeek = false;
    bool timetrial = false;
    bool detailedMessage = false;

    // ===== basic / business / enjoy / gendai / kaiwa =====
    bool basic0 = false;
    bool basic1 = false;
    bool basic2 = false;
    bool business1 = false;
    bool enjoy = false;
    bool gendai = false;
    bool kaiwa = false;

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
};

#pragma once
#include <QString>
#include <QSettings>
#include "constants.h"

class Settings
{
public:
    Settings();

    void load();
    void save();

    // ===== 英語講座 =====
    bool englishEnabled[Constants::EnglishCount];

    // ===== Optional =====
    QString optionalId[Constants::OptionalCount];
    QString optionalTitle[Constants::OptionalCount];
    bool    optionalEnabled[Constants::OptionalCount];

    // ===== Spec =====
    QString specId[Constants::SpecialCount];
    QString specTitle[Constants::SpecialCount];
    bool    specEnabled[Constants::SpecialCount];

    // ===== CheckBox =====
    bool checkBoxEnabled[Constants::CheckBoxCount];

    // ===== その他設定（null 許容）=====
    QString audioExtension;   // null 不要（常に文字列）
    QString saveFolder;       // null 許容
    QString ffmpegFolder;     // null 許容
};

