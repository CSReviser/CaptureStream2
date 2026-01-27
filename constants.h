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
#include <QMultiMap>
#include <QStringList>
#include <QVector>

// 固定番組用（enabled のみ INI に保存される）
//  id / title を固定値として保持
struct ProgramInfo {
    QString key;        // iniファイルのキー名
    bool    enabled;    // enabled の初期値
    QString id;         // 番組ID（固定）
    QString title;      // 表示タイトル（固定）
    QString objectName; // UI の objectName
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
    
    QString objectName; // UI の objectName
};

struct CheckBoxSettings {
    // enabled
    QString keyEnabled;
    bool    enabledDefault;
    
    QString objectName; // UI の objectName
};

namespace Constants {

    // ===== アプリ情報 =====
    inline const QString AppName = "語学講座CS2";
    inline const QString AppVersion = "2026/01/27";

    // ===== INI ファイル名 =====
    inline const QString IniFileName = "CaptureStream2.ini";
    
    // ===== QSettings グループ =====
    inline const QString SETTING_GROUP_MainWindow = "MainWindow";
    inline const QString SETTING_GROUP_CustomizeDialog = "CustomizeDialog";
    inline const QString SETTING_GROUP_MessageWindow = "MessageWindow";
    inline const QString SETTING_GROUP_ScrambleDialog = "ScrambleDialog";
    inline const QString SETTING_GROUP_Settingsdialog = "Settingsdialog";
    
    // ===== 拡張子　設定キー デフォルト値 =====
    inline const QString KEY_AudioExtension = "audio_extension";
    inline const QString DEFAULT_AudioExtension = "m4a";

    // ===== フォルダ設定キー =====
    // ===== デフォルト値 キーが無ければ null を settings で設定 =====
    inline const QString KEY_SaveFolder     = "save_folder";
    inline const QString KEY_FfmpegFolder   = "ffmpeg_folder";

    // ===== 固定の講座番組 設定キー／デフォルト値 =====
    // INI に保存されるタイトルとは別に、
    // アプリ内部で使う固定の対応表がある場合に使用
    
    inline const QString KEY_basic0 = "basic0";
    inline const QString KEY_basic1 = "basic1";
    inline const QString KEY_basic2 = "basic2";
    inline const QString KEY_timetrial = "timetrial";
    inline const QString KEY_enjoy = "enjoy";
    inline const QString KEY_kaiwa =  "kaiwa";
    inline const QString KEY_business = "business1";
    inline const QString KEY_gendai = "gendai";
    
    inline const ProgramInfo EnglishPrograms[] = {
        {"basic0", false,    "GGQY3M1929_01", "小学生の基礎英語", "toolButton_basic0"},
        {KEY_basic1, false,    "148W8XX226_01", "中学生の基礎英語 【レベル１】", "toolButton_basic1"},
        {KEY_basic2, false,    "83RW6PK3GG_01", "中学生の基礎英語 【レベル２】", "toolButton_basic2"},
        {KEY_kaiwa, false, "PMMJ59J6N2_01","ラジオ英会話", "toolButton_kaiwa"},
        {KEY_enjoy, false,     "BR8Z3NX7XM_01",   "エンジョイ・シンプル・イングリッシュ", "toolButton_enjoy"},
        {KEY_timetrial, false, "8Z6XJ6J415_01", "英会話タイムトライアル", "toolButton_timetrial" },
        {KEY_business, false, "368315KKP8_01", "ラジオビジネス英語", "toolButton_business1" },
        {KEY_gendai, false, "77RQWQX1L6_01", "ニュースで学ぶ「現代英語」", "toolButton_gendai" }
    };

    // ===== 固定の講座番組 カテゴリの数 =====
    constexpr int EnglishCount = std::size(EnglishPrograms);

    // ===== 任意設定の講座番組 設定キー デフォルト値 =====
    inline const ProgramInfoEditable OptionalPrograms[] = {
        {
            "optional_1", false,
            "optional1",      "XQ487ZM61K_01",
            "opt_title1",   "まいにちフランス語",
            "toolButton_optional1"
        },
        {
            "optional_2", false,
            "optional2",      "N8PZRZ9WQY_01",
            "opt_title2",   "まいにちドイツ語",
            "toolButton_optional2"
        },
        {
            "optional_3", false,
            "optional3",      "LJWZP7XVMX_01",
            "opt_title3",   "まいにちイタリア語",
            "toolButton_optional3"
        },
        {
            "optional_4", false,
            "optional4",      "NRZWXVGQ19_01",
            "opt_title4",   "まいにちスペイン語",
            "toolButton_optional4"
        },
        {
            "optional_5", false,
            "optional5",      "YRLK72JZ7Q_01",
            "opt_title5",   "まいにちロシア語",
            "toolButton_optional5"
        },
        {
            "optional_6", false,
            "optional6",      "N13V9K157Y_01",
            "opt_title6",   "ポルトガル語",
            "toolButton_optional6"
        },
        {
            "optional_7", false,
            "optional7",      "983PKQPYN7_01",
            "opt_title7",   "まいにち中国語",
            "toolButton_optional7"
        },
        {
            "optional_8", false,
            "optional8",      "LR47WW9K14_01",
            "opt_title8",   "まいにちハングル講座",
            "toolButton_optional8"
        }
    };

    // ===== 任意設定の講座番組 カテゴリの数 =====
    constexpr int OptionalCount = std::size(OptionalPrograms);

    // ===== 特番 設定キー デフォルト値 =====
    inline const ProgramInfoEditable SpecPrograms[] = {
        {
            "special_1", false,
            "special1",      "6LPPKP6W8Q_01",
            "spec_title1",   "やさしい日本語",
            "toolButton_special1"
        },
        {
            "special_2", false,
            "special2",      "WKMNWGMN6R_01",
            "spec_title2",   "アラビア語講座",
            "toolButton_special2"
        },
        {
            "special_3", false,
            "special3",      "GLZQ4M519X_01",
            "spec_title3",   "Asian View",
            "toolButton_special3"
        },
        {
            "special_4", false,
            "special4",      "4MY6Q8XP88_01",
            "spec_title4",   "Living in Japan",
            "toolButton_special4"
        }
    };

    // ===== 特番 カテゴリの数 =====
    constexpr int SpecialCount  = std::size(SpecPrograms);
    
    // ===== チェックボックスフラグの 設定キー デフォルト値 =====
    inline const QString KEY_KOZA_SEPARATION = "koza_separation";
    inline const QString KEY_MULTI_GUI = "multi_gui";
    inline const QString KEY_NAME_SPACE = "name_space";
    inline const QString KEY_TAG_SPACE = "tag_space";
    inline const CheckBoxSettings CheckBoxSettings[] = {
		{ "skip", true, "toolButton_skip" },
		{ "this_week", true, "checkBox_this_week" },
		{ "detailed_message", false, "toolButton_detailed_message" },
		{ KEY_KOZA_SEPARATION, true, "" },
		{ KEY_MULTI_GUI, false, "" },
		{ KEY_NAME_SPACE, true, "" },
		{ KEY_TAG_SPACE, true, "" },
		{ "thumbnail", false, "checkBox_thumbnail" }
    };

    // ===== チェックボックスフラグの数 =====
    constexpr int CheckBoxCount = std::size(CheckBoxSettings);
    
    // ===== 固定の URL などがある場合はここに追加 =====
    // const QString BaseApiUrl = "https://example.com/api/";
    inline const QString prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
    inline const QString suffix = "listdataflv.xml";
    inline const QString json_prefix = "https://www.nhk.or.jp/radioondemand/json/";   
    
     // ===== 講座番組ID =====   
   inline const QMap<QString, QString> map = { 
         { "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
         { "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
         { "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
         { "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
         { "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
         { "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
         { "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
         { "77RQWQX1L6_01", "english/gendaieigo" },	// ニュースで学ぶ「現代英語」
         { "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
         { "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
         { "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
         { "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
         { "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
         { "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
         { "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
         { "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
         { "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
         { "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
         { "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
         { "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
         { "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
         { "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
         { "XQ487ZM61K_01", "french/kouza3" },		// まいにちフランス語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza3" },		// まいにちドイツ語 入門編/初級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza3" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza3" },		// まいにちイタリア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza3" },		// まいにちロシア語 入門編/初級編/応用編
         { "983PKQPYN7_s1", "chinese/kouza4" },		// まいにち中国語
         { "LR47WW9K14_s1", "hangeul/kouza4" },		// まいにちハングル講座
};

     // ===== 講座番組ID 分離ID(_x1、_y1) =====   	
   inline const QMultiMap<QString, QString> multimap = { 
         { "77RQWQX1L6_01", "english/gendaieigo" },	// ニュースで学ぶ「現代英語」
         { "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
         { "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
         { "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
         { "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
         { "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
         { "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
         { "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
         { "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
         { "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
         { "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
         { "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
         { "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
         { "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
         { "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
         { "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
         { "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
         { "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
         { "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
         { "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
         { "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
         { "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
         { "XQ487ZM61K_01", "french/kouza" },		// まいにちフランス語 入門編/初級編/応用編
         { "XQ487ZM61K_01", "french/kouza2" },		// まいにちフランス語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza" },		// まいにちドイツ語 入門編/初級編/応用編
         { "N8PZRZ9WQY_01", "german/kouza2" },		// まいにちドイツ語 入門編/初級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "NRZWXVGQ19_01", "spanish/kouza2" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza" },		// まいにちイタリア語 入門編/初級編/応用編
         { "LJWZP7XVMX_01", "italian/kouza2" },		// まいにちイタリア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza" },		// まいにちロシア語 入門編/初級編/応用編
         { "YRLK72JZ7Q_01", "russian/kouza2" },		// まいにちロシア語 入門編/初級編/応用編
         { "983PKQPYN7_s1", "chinese/kouza" },		// まいにち中国語
         { "LR47WW9K14_s1", "hangeul/kouza" },		// まいにちハングル講座
};	

     // ===== 講座番組ID 複合ID(_s1) =====  
   inline const QMultiMap<QString, QString> multimap1 = { 
         { "983PKQPYN7_s1", "983PKQPYN7_01" },		// まいにち中国語
         { "LR47WW9K14_s1", "LR47WW9K14_01" },		// まいにちハングル講座
         { "6LPPKP6W8Q_s1", "6LPPKP6W8Q_01" },		// やさしい日本語
         { "6LPPKP6W8Q_s1", "D6RM27PGVM_01" },		// Learn Japanese from the News
         { "6LPPKP6W8Q_s1", "4MY6Q8XP88_01" },		// Living in Japan
};	
 

    // ===== 任意設定の講座番組 プリセット値 =====
// 1セットは常に8つ
static constexpr int OPT_PRESET_SIZE = OptionalCount;

// プリセットは増減可能（行を増やすだけでOK）
inline QVector<QStringList> OPT_PRESETS = {
    { "XQ487ZM61K_x1", "XQ487ZM61K_y1", "N8PZRZ9WQY_x1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_x1", "LJWZP7XVMX_y1", "NRZWXVGQ19_x1", "NRZWXVGQ19_y1" },
 //まいにちフランス語 入門編, //まいにちフランス語 応用編, //まいにちドイツ語 入門編／初級編, //まいにちドイツ語 応用編, //まいにちイタリア語 入門編, //まいにちイタリア語 応用編, //まいにちスペイン語 入門編／初級編 //まいにちスペイン語 中級編／応用編   
    { "983PKQPYN7_01", "GLZQ4M519X_01", "LR47WW9K14_01", "6LPPKP6W8Q_01", "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "WKMNWGMN6R_01", "N13V9K157Y_01" },
//まいにち中国語, //Asian View, //まいにちハングル講座, //やさしい日本語, //まいにちロシア語 入門編, //まいにちロシア語 応用編, //アラビア語講座  //ポルトガル語
    { "XQ487ZM61K_x1", "N8PZRZ9WQY_x1", "LJWZP7XVMX_x1", "NRZWXVGQ19_x1", "YRLK72JZ7Q_x1", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語 入門編, //まいにちドイツ語 入門編／初級編, //まいにちイタリア語 入門編, //まいにちスペイン語 入門編／初級編, //まいにちロシア語 入門編, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "XQ487ZM61K_y1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_y1", "NRZWXVGQ19_y1", "YRLK72JZ7Q_y1", "N13V9K157Y_01", "GLZQ4M519X_01", "WKMNWGMN6R_01" },
//まいにちフランス語 応用編, //まいにちドイツ語 応用編, //まいにちイタリア語 応用編, //まいにちスペイン語 中級編／応用編, //まいにちロシア語 応用編, //ポルトガル語, //Asian View  //アラビア語講座
    { "XQ487ZM61K_01", "N8PZRZ9WQY_01", "LJWZP7XVMX_01", "NRZWXVGQ19_01", "YRLK72JZ7Q_01", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語, //まいにちドイツ語, //まいにちイタリア語, //まいにちスペイン語, //まいにちロシア語, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "4MY6Q8XP88_01", "GLZQ4M519X_01", "6LPPKP6W8Q_01", "YR96XR51MZ_01", "X4X6N1XG8Z_01", "D85RZVGX7W_01", "LRK2VXPK5X_01", "M65G6QLKMY_01" },
//Living in Japan, //Asian View, //やさしい日本語, //朗読の世界, //青春アドベンチャー, //新日曜名作座, //朗読  //FMシアター 
    { "R5XR783QK3_01", "NJZR87XYYV_01", "5L3859P515_01", "566V9ZMX35_01", "YR96XR51MZ_01", "X78J5NKWM9_01", "MVYJ6PRZMX_01", "JWQ88ZVWQK_01" }
//おしゃべりな古典教室, //日曜カルチャー, //古典講読 //日曜討論, //朗読の世界 //こころをよむ, //アナウンサー百年百話  //宗教の時間
};

    // ===== 特番 プリセット値 =====
// 1セットは常に4つ
static constexpr int PRESET_SIZE = SpecialCount;

// プリセットは増減可能（行を増やすだけでOK）
inline QVector<QStringList> PRESETS = {
    { "6LPPKP6W8Q_01", "WKMNWGMN6R_01", "GLZQ4M519X_01", "4MY6Q8XP88_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "983PKQPYN7_01", "LR47WW9K14_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "983PKQPYN7_01", "LR47WW9K14_01", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "GLZQ4M519X_01", "X7R2P2PW5P_02", "L6ZQ2NX1NL_01", "34PY344RPJ_01" },
    { "X4X6N1XG8Z_01", "D85RZVGX7W_01", "YR96XR51MZ_01", "M65G6QLKMY_01" },
    { "R5XR783QK3_01", "X78J5NKWM9_01", "5L3859P515_01", "JWQ88ZVWQK_01" }
};

// FILE NAME、TITLEのkey/デフォルト値
struct Item {
    const char* key;
    const char* defaultValue;
};

static const Item TITLE_ITEMS[] = {
    { "customized_title1", "%f" },
    { "customized_title2", "%k_%Y_%M_%D" }
};

static const Item FILENAME_ITEMS[] = {
    { "customized_file_name1", "%k_%Y_%M_%D" },
    { "customized_file_name2", "%k_%Y_%M_%D" }
};

static const int ITEM_COUNT = std::size(FILENAME_ITEMS);;

    static const QStringList COURSES = {
        QStringLiteral("json"),
        QStringLiteral("xml")
    };

    // FILE NAME、TITLEのプリセット（UI ラジオボタン用）
struct CustomizePreset {
    const char* value;
    const char* label;   // UI に表示する名前（必要なら）
};

inline const CustomizePreset FILENAME_PRESETS[] = {
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};

constexpr int FILENAME_PRESET_COUNT = std::size(FILENAME_PRESETS);

    
        
                static const QString DEFAULT_FILENAME  = "%k_%Y_%M_%D";
    static const QString DEFAULT_FILENAME1 = "%f_%Y_%M_%D";
    static const QString DEFAULT_FILENAME2 = "%k_%Y-%M-%D";
    static const QString DEFAULT_FILENAME3 = "%h";
    static const QString DEFAULT_FILENAME4 = "%f";
    static const QString DEFAULT_FILENAME5 = "%k_%h";
    static const QString DEFAULT_FILENAME6 = "%y%M%D_%k%x";


}
