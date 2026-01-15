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
#include <QMap>

// 固定番組用（enabled のみ INI に保存される）
//  id / title を固定値として保持
struct ProgramInfo {
    QString key;      // iniファイルのキー名
    bool    enabled;  // enabled の初期値
    QString id;       // 番組ID（固定）
    QString title;    // 表示タイトル（固定）
};

// ユーザー編集可能番組用（INI に保存される）
// enabled / id / title をそれぞれ個別キーとして管理
struct ProgramInfoEditable {
    // enabled
    QString keyEnabled;
    bool    enabledDefault;

    // id
    QString keyId;
    QString idDefault;

    // title
    QString keyTitle;
    QString titleDefault;
};

struct CheckBox {
    // enabled
    QString keyEnabled;
    bool    enabledDefault;
};



namespace Constants {

    // ===== アプリ情報 =====
    inline const QString AppName = "CaptureStream2";
    inline const QString AppVersion = "2026/01/13";

    // ===== INI ファイル名 =====
    inline const QString IniFileName = "CaptureStream2.ini";
    
    // ===== QSettings グループ =====
    inline const QString SETTING_GROUP_MainWindow = "MainWindow";
    inline const QString SETTING_GROUP_CustomizeDialog = "CustomizeDialog";
    inline const QString SETTING_GROUP_MessageWindow = "MessageWindow";

    // ===== 拡張子　設定キー デフォルト値 =====
    inline const QString KEY_AudioExtension = "audio_extension";
    inline const QString DEFAULT_AudioExtension = "m4a";

    // ===== フォルダ設定キー =====
    inline const QString KEY_SaveFolder     = "save_folder";
    inline const QString KEY_FfmpegFolder   = "ffmpeg_folder";

    // ===== 固定の講座番組 設定キー デフォルト値 =====
    // INI に保存されるタイトルとは別に、
    // アプリ内部で使う固定の対応表がある場合に使用
    inline const ProgramInfo EnglishPrograms[] = {
        {"basic0", false,    "GGQY3M1929_01", "小学生の基礎英語"},
        {"basic1", false,    "148W8XX226_01", "中学生の基礎英語 レベル１"},
        {"basic2", false,    "83RW6PK3GG_01", "中学生の基礎英語 レベル２"},
        {"kaiwa", false, "PMMJ59J6N2_01","ラジオ英会話"},
        {"enjoy", false,     "BR8Z3NX7XM_01",   "エンジョイ・シンプル・イングリッシュ"},
        {"timetrial", false, "8Z6XJ6J415_01", "英会話タイムトライアル" },
        {"business1", false, "368315KKP8_01", "ラジオビジネス英語" },
        {"gendai", false, "77RQWQX1L6_01", "ニュースで学ぶ「現代英語」" }
    };

    // ===== 固定の講座番組 カテゴリの数 =====
    constexpr int EnglishCount = std::size(EnglishPrograms);

    // ===== 任意設定の講座番組 設定キー デフォルト値 =====
    inline const ProgramInfoEditable OptionalPrograms[] = {
        {
            "optional_1", false,
            "optional1",      "XQ487ZM61K_01",
            "opt_title1",   "まいにちフランス語"
        },
        {
            "optional_2", false,
            "optional2",      "N8PZRZ9WQY_01",
            "opt_title2",   "まいにちドイツ語"
        },
        {
            "optional_3", false,
            "optional3",      "LJWZP7XVMX_01",
            "opt_title3",   "まいにちイタリア語"
        },
        {
            "optional_4", false,
            "optional4",      "NRZWXVGQ19_01",
            "opt_title4",   "まいにちスペイン語"
        },
        {
            "optional_5", false,
            "optional5",      "YRLK72JZ7Q_01",
            "opt_title5",   "まいにちロシア語"
        },
        {
            "optional_6", false,
            "optional6",      "N13V9K157Y_01",
            "opt_title6",   "ポルトガル語"
        },
        {
            "optional_7", false,
            "optional7",      "983PKQPYN7_01",
            "opt_title7",   "まいにち中国語"
        },
        {
            "optional_8", false,
            "optional8",      "LR47WW9K14_01",
            "opt_title8",   "まいにちハングル講座"
        }
    };

    // ===== 任意設定の講座番組 カテゴリの数 =====
    constexpr int OptionalCount = std::size(OptionalPrograms);

    // ===== 特番 設定キー デフォルト値 =====
    inline const ProgramInfoEditable SpecPrograms[] = {
        {
            "special_1", false,
            "special1",      "6LPPKP6W8Q_01",
            "spec_title1",   "やさしい日本語"
        },
        {
            "special_2", false,
            "special2",      "WKMNWGMN6R_01",
            "spec_title2",   "アラビア語講座"
        },
        {
            "special_3", false,
            "special3",      "GLZQ4M519X_01",
            "spec_title3",   "Asian View"
        },
        {
            "special_4", false,
            "special4",      "4MY6Q8XP88_01",
            "spec_title4",   "Living in Japan"
        }
    };

    // ===== 特番 カテゴリの数 =====
    constexpr int SpecialCount  = std::size(SpecPrograms);
    
    // ===== 特番 設定キー デフォルト値 =====    
    inline const CheckBox checkBoxes[] = {
		{ "skip", true },
		{ "this_week", true },
		{ "detailed_message", false },
		{ "koza_separation", true },
		{ "multi_gui", true },
		{ "name_space", false },
		{ "tag_space", false },
		{ "thumbnail", false }
    };

    // ===== チェックボックスフラグの数 =====
    constexpr int CheckBoxCount =   = std::size(checkBoxes);
    
    // ===== 固定の URL などがある場合はここに追加 =====
    // const QString BaseApiUrl = "https://example.com/api/";
}
