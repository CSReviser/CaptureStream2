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
#include "constants_core.h"
#include "constants_programs.h"
#include "constants_flags.h"
#include "constants_cli.h"
#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStringList>
#include <QVector>

namespace Constants {




    
    // ===== 固定の URL などがある場合はここに追加 =====
    // inline constexpr auto BaseApiUrl = "https://example.com/api/";
    inline constexpr auto  prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
    inline constexpr auto  suffix = "listdataflv.xml";
    inline constexpr auto  json_prefix = "https://www.nhk.or.jp/radioondemand/json/";   
    
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
    constexpr int OPT_PRESET_SIZE = OptionalCount;

// プリセットは増減可能（行を増やすだけでOK）
inline const QVector<QStringList> OPT_PRESETS = {
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
    constexpr int PRESET_SIZE = SpecCount;

// プリセットは増減可能（行を増やすだけでOK）
inline const QVector<QStringList> PRESETS = {
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
    const QString key;
    const char* defaultValue;
};



inline const Item TITLE_ITEMS[] = {
    { KEY_CUSTOMIZED_TITLE1, "%f" },
    { KEY_CUSTOMIZED_TITLE2, "%k_%Y_%M_%D" }
};



inline const Item FILENAME_ITEMS[] = {
    { KEY_CUSTOMIZED_FILENAME1, "%k_%Y_%M_%D" },
    { KEY_CUSTOMIZED_FILENAME2, "%k_%Y_%M_%D" }
};

inline const int ITEM_COUNT = std::size(FILENAME_ITEMS);

    inline const QStringList COURSES = {
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


    // TITLEのプリセット（UI ラジオボタン用）
inline const CustomizePreset TITLE_PRESETS[] = {
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};

constexpr int TITLE_PRESETS_COUNT = std::size(TITLE_PRESETS);

    // CLIコマンドラインオプション
struct CliOption {
    const char* name;
    bool requiresValue;
    QString keyOption;	// GUI、Flagの キーと一致
    QString description;
};

inline const CliOption OPTION_TABLE[] = {
    { "-nogui", false,	KEY_NOGUI,		"GUI を起動せずに実行します" },
    { "-t",     true,	KEY_CUSTOMIZED_TITLE1,	"タイトルタグ形式を指定します" },
    { "-f",     true,	KEY_CUSTOMIZED_FILENAME1, "ファイル名形式を指定します" },
    { "-o",     true,	KEY_SaveFolder,		"保存フォルダのフルパスを指定します" },
    { "-e",     true,	KEY_AudioExtension,	"拡張子を指定します" },
    { "-z",     false,	KEY_LAST_WEEK,		"前週の動作を行います" },
    { "-b",     false,	KEY_BOTH_WEEKS,		"前週と当週の両方を実行します" },
    { "-s",     false,	KEY_KOZA_SEPARATION,	"応用編分離を有効にします" },
};

constexpr int OPTION_TABLE_COUNT = std::size(OPTION_TABLE);

}
