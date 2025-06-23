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

#pragma once

#include <QString>
#include <QStringList>
#include <QMap>

namespace AppSettings {

// アプリバージョン
inline constexpr auto VERSION = "2025/06/08";

// QSettingsグループ/キー
inline constexpr auto SETTING_GROUP = "MainWindow";
inline constexpr auto SETTING_GEOMETRY = "geometry";
inline constexpr auto SETTING_WINDOWSTATE = "windowState";
inline constexpr auto SETTING_MAINWINDOW_POSITION = "Mainwindow_Position";
inline constexpr auto SETTING_SAVE_FOLDER = "save_folder";
inline constexpr auto SETTING_FFMPEG_FOLDER = "ffmpeg_folder";
inline constexpr auto SETTING_SCRAMBLE = "scramble";
inline constexpr auto SETTING_SCRAMBLE_URL1 = "scramble_url1";
inline constexpr auto SETTING_KOZA_SEPARATION = "koza_separation";
inline constexpr auto SETTING_MULTI_GUI = "multi_gui";
inline constexpr auto SETTING_NAME_SPACE = "name_space";
inline constexpr auto SETTING_TAG_SPACE = "tag_space";

// ファイル名／タイトルのデフォルト書式
inline constexpr auto SETTING_FILE_NAME1 = "FILE_NAME1";
inline constexpr auto SETTING_FILE_NAME2 = "FILE_NAME2";
inline constexpr auto SETTING_TITLE1 = "FILE_TITLE1";
inline constexpr auto SETTING_TITLE2 = "FILE_TITLE2";
inline constexpr auto FILE_NAME1 = "%k_%Y_%M_%D";
inline constexpr auto FILE_NAME2 = "%k_%Y_%M_%D";
inline constexpr auto FILE_TITLE1 = "%f";
inline constexpr auto FILE_TITLE2 = "%k_%Y_%M_%D";

// スクランブルURL
inline constexpr auto SCRAMBLE_URL1 = "http://www47.atwiki.jp/jakago/pub/scramble.xml";
inline constexpr auto SCRAMBLE_URL2 = "http://cdn47.atwikiimg.com/jakago/pub/scramble.xml";

// 動作フラグ
inline constexpr bool KOZA_SEPARATION_FLAG = true;
inline constexpr bool NAME_SPACE_FLAG = true;
inline constexpr bool TAG_SPACE_FLAG = false;
inline constexpr bool MULTI_GUI_FLAG = false;

// UI調整
inline constexpr int X11_WINDOW_VERTICAL_INCREMENT = 5;

// GUI用スタイルシート
#if defined(Q_OS_WIN)
inline constexpr auto STYLE_SHEET = "stylesheet-win.qss";
#elif defined(Q_OS_MACOS)
inline constexpr auto STYLE_SHEET = "stylesheet-mac.qss";
#else
inline constexpr auto STYLE_SHEET = "stylesheet-ubu.qss";
#endif

// オプショナルな番組設定キーとID
inline constexpr const char* SETTING_OPTIONAL_KEYS[] = {
    "optional1", "optional2", "optional3", "optional4", "optional5",
    "optional6", "optional7", "optional8", "optional9", "optionala"
};

inline constexpr const char* OPTIONAL_IDS[] = {
    "XQ487ZM61K_01", "N8PZRZ9WQY_01", "LJWZP7XVMX_01", "NRZWXVGQ19_01", "YRLK72JZ7Q_01",
    "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01", "XQ487ZM61K_01", "N8PZRZ9WQY_01"
};

inline constexpr const char* Program_TITLES[] = {
    "まいにちフランス語", "まいにちドイツ語", "まいにちイタリア語", "まいにちスペイン語", "まいにちロシア語",
    "ポルトガル語", "まいにち中国語", "まいにちハングル講座", "まいにちフランス語", "まいにちドイツ語"
};

// 特別番組
inline constexpr const char* SETTING_SPECIAL_KEYS[] = {
    "special1", "special2", "special3", "special4"
};

inline constexpr const char* SPECIAL_IDS[] = {
    "6LPPKP6W8Q_01", "WKMNWGMN6R_01", "GLZQ4M519X_01", "4MY6Q8XP88_01"
};

inline constexpr const char* Special_TITLES[] = {
    "やさしい日本語", "アラビア語講座", "Asian View", "Living in Japan"
};

// JSON/APIパス
inline const QString prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
inline const QString suffix = "listdataflv.xml";
inline const QString json_prefix = "https://www.nhk.or.jp/radioondemand/json/";

inline const QList<QString> kCheckBoxKeys = {
    "basic0", "basic1", "basic2",
    "timetrial", "enjoy", "kaiwa",
    "business1", "gendai",
    "optional_1", "optional_2", "optional_3", "optional_4",
    "optional_5", "optional_6", "optional_7", "optional_8",
    "special_1", "special_2", "special_3", "special_4",
    "skip", "this_week", "detailed_message", "thumbnail"
};

inline const QList<bool> kCheckBoxDefaults = {
    false, false, false,
    false, false, false,
    false, false,
    false, false, false, false,
    false, false, false, false,
    false, false, false, false,
    true, true, false, false
};

inline const QList<QString> kTextComboBoxKeys = {
    "audio_extension"
};

inline const QList<QString> kTextComboBoxDefaults = {
    "m4a"
};

// optionalN キー
inline const QStringList kOptionalIdKeys = {
    "optional1", "optional2", "optional3", "optional4",
    "optional5", "optional6", "optional7", "optional8"
};

inline const QStringList kOptionalTitleKeys = {
    "opt_title1", "opt_title2", "opt_title3", "opt_title4",
    "opt_title5", "opt_title6", "opt_title7", "opt_title8"
};

// specialN キー
inline const QStringList kSpecialIdKeys = {
    "special1", "special2", "special3", "special4"
};

inline const QStringList kSpecialTitleKeys = {
    "spec_title1", "spec_title2", "spec_title3", "spec_title4"
};

// デフォルト値（例：タイトル/ID）
inline const QStringList kOptionalDefaultTitles = {
    "Program_TITLE1", "Program_TITLE2", "Program_TITLE3", "Program_TITLE4",
    "Program_TITLE5", "Program_TITLE6", "Program_TITLE7", "Program_TITLE8"
};

inline const QStringList kOptionalDefaultIds = {
    "OPTIONAL1", "OPTIONAL2", "OPTIONAL3", "OPTIONAL4",
    "OPTIONAL5", "OPTIONAL6", "OPTIONAL7", "OPTIONAL8"
};

inline const QStringList kSpecialDefaultTitles = {
    "Special_TITLE1", "Special_TITLE2", "Special_TITLE3", "Special_TITLE4"
};

inline const QStringList kSpecialDefaultIds = {
    "SPECIAL1", "SPECIAL2", "SPECIAL3", "SPECIAL4"
};

    struct Data {
        QMap<QString, QString> idMap;
        QMap<QString, QString> nameMap;
        QMap<QString, QString> thumbnailMap;
    };


} // namespace AppSettings

#pragma once
#include <QString>
#include <QList>

namespace AppSettings {

    inline constexpr auto SETTING_KOZA_SEPARATION = "koza_separation";
    inline constexpr bool KOZA_SEPARATION_DEFAULT = true;

    inline constexpr auto SETTING_SAVE_FOLDER = "save_folder";
    inline constexpr auto DEFAULT_SAVE_FOLDER = "Downloads";

    // ...他のキーやデフォルトも同様にここへ
}