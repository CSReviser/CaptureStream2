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

    // ===== アプリ情報 =====
    inline const QString AppName = "語学講座ＣＳ２";
    inline const QString AppVersion = "2026/01/29";

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

/*
 * ProgramDefinition
 * ------------------------------------------------------------
 * English / Optional / Spec / Feature をすべて統合した構造体。
 *
 * 目的：
 *   - 設定方法が異なる4種類のボタンを、最終的に一元データとして扱う
 *   - constants.h の定義を一本化し、同期ズレを防ぐ
 *
 * 各種別の意味：
 *   English : 固定番組（id/label が固定、checked のみ INI 保存）
 *   Optional: 任意設定番組（checked/id/label を INI 保存）
 *   Spec    : Optional と同じだが UI 上は別カテゴリ
 *   Feature : チェックボックス、コンボボックスの各種設定
 *   チェックボックス、コンボボックスの区別は
 *   objectNameに下記文字列を含むことで識別可能
 *   toolButton : コンボボックス
 *   checkBox   : チェックボックス、コンボボックス
 *
 * 空文字("") の扱い：
 *   - English の keyId/keyLabel は空（固定値なので保存不要）
 *   - Feature の id/label は空（番組IDを持たない）
 */
struct ProgramDefinition {
    enum class Kind {
        English,   // 固定番組
        Optional,  // 任意設定番組
        Spec,      // 特番
        Feature    // チェックボックス
    };

    Kind kind;

    // checked の保存キーとデフォルト値
    QString keyChecked;
    bool    checkedDefault;

    // id の保存キーとデフォルト値（English/Feature は空）
    QString keyId;
    QString idDefault;

    // label の保存キーとデフォルト値（English は固定値、Feature は空）
    QString keyLabel;
    QString labelDefault;

    // UI の objectName（Feature で空の場合もある）
    QString objectName;
};


/* ============================================================
 * English（固定番組）
 * ------------------------------------------------------------
 * id/label は固定値で、INI に保存されるのは checked のみ。
 * keyId/keyLabel は空文字でよい。
 * ========================================================== */
inline const ProgramDefinition EnglishPrograms[] = {
    { ProgramDefinition::Kind::English,
      "basic0", false,
      "", "GGQY3M1929_01",
      "", "小学生の基礎英語",
      "toolButton_basic0" },

    { ProgramDefinition::Kind::English,
      "basic1", false,
      "", "148W8XX226_01",
      "", "中学生の基礎英語 【レベル１】",
      "toolButton_basic1" },

    { ProgramDefinition::Kind::English,
      "basic2", false,
      "", "83RW6PK3GG_01",
      "", "中学生の基礎英語 【レベル２】",
      "toolButton_basic2" },

    { ProgramDefinition::Kind::English,
      "kaiwa", false,
      "", "PMMJ59J6N2_01",
      "", "ラジオ英会話",
      "toolButton_kaiwa" },

    { ProgramDefinition::Kind::English,
      "enjoy", false,
      "", "BR8Z3NX7XM_01",
      "", "エンジョイ・シンプル・イングリッシュ",
      "toolButton_enjoy" },

    { ProgramDefinition::Kind::English,
      "timetrial", false,
      "", "8Z6XJ6J415_01",
      "", "英会話タイムトライアル",
      "toolButton_timetrial" },

    { ProgramDefinition::Kind::English,
      "business1", false,
      "", "368315KKP8_01",
      "", "ラジオビジネス英語",
      "toolButton_business1" },

    { ProgramDefinition::Kind::English,
      "gendai", false,
      "", "77RQWQX1L6_01",
      "", "ニュースで学ぶ「現代英語」",
      "toolButton_gendai" }
};
    // ===== 固定の講座番組 カテゴリの数 =====
constexpr int EnglishCount = std::size(EnglishPrograms);


/* ============================================================
 * Optional（任意設定番組）
 * ------------------------------------------------------------
 * checked / id / label の3つを INI に保存する。
 * ========================================================== */
inline const ProgramDefinition OptionalPrograms[] = {
    { ProgramDefinition::Kind::Optional,
      "optional_1", false,
      "optional1", "XQ487ZM61K_01",
      "opt_title1", "まいにちフランス語",
      "toolButton_optional1" },

    { ProgramDefinition::Kind::Optional,
      "optional_2", false,
      "optional2", "N8PZRZ9WQY_01",
      "opt_title2", "まいにちドイツ語",
      "toolButton_optional2" },

    { ProgramDefinition::Kind::Optional,
      "optional_3", false,
      "optional3", "LJWZP7XVMX_01",
      "opt_title3", "まいにちイタリア語",
      "toolButton_optional3" },

    { ProgramDefinition::Kind::Optional,
      "optional_4", false,
      "optional4", "NRZWXVGQ19_01",
      "opt_title4", "まいにちスペイン語",
      "toolButton_optional4" },

    { ProgramDefinition::Kind::Optional,
      "optional_5", false,
      "optional5", "YRLK72JZ7Q_01",
      "opt_title5", "まいにちロシア語",
      "toolButton_optional5" },

    { ProgramDefinition::Kind::Optional,
      "optional_6", false,
      "optional6", "N13V9K157Y_01",
      "opt_title6", "ポルトガル語",
      "toolButton_optional6" },

    { ProgramDefinition::Kind::Optional,
      "optional_7", false,
      "optional7", "983PKQPYN7_01",
      "opt_title7", "まいにち中国語",
      "toolButton_optional7" },

    { ProgramDefinition::Kind::Optional,
      "optional_8", false,
      "optional8", "LR47WW9K14_01",
      "opt_title8", "まいにちハングル講座",
      "toolButton_optional8" }
};
    // ===== 任意設定の講座番組 カテゴリの数 =====
constexpr int OptionalCount = std::size(OptionalPrograms);


/* ============================================================
 * Spec（特番）
 * ------------------------------------------------------------
 * Optional と同じ構造だが UI 上は別カテゴリ。
 * ========================================================== */
inline const ProgramDefinition SpecPrograms[] = {
    { ProgramDefinition::Kind::Spec,
      "special_1", false,
      "special1", "6LPPKP6W8Q_01",
      "spec_title1", "やさしい日本語",
      "toolButton_special1" },

    { ProgramDefinition::Kind::Spec,
      "special_2", false,
      "special2", "WKMNWGMN6R_01",
      "spec_title2", "アラビア語講座",
      "toolButton_special2" },

    { ProgramDefinition::Kind::Spec,
      "special_3", false,
      "special3", "GLZQ4M519X_01",
      "spec_title3", "Asian View",
      "toolButton_special3" },

    { ProgramDefinition::Kind::Spec,
      "special_4", false,
      "special4", "4MY6Q8XP88_01",
      "spec_title4", "Living in Japan",
      "toolButton_special4" }
};
    // ===== 任意設定の講座番組 カテゴリの数 =====
constexpr int SpecCount = std::size(SpecPrograms);


/* ============================================================
 * Feature（チェックボックス）
 * ------------------------------------------------------------
 * checked のみ保存する。
 * id は不要なので空文字。checkBoxはlabelも空文字。
 * objectName が同一のエントリは、同一の UI ウィジェットを共有する。
 * （複数の設定値が 1 つの UI 状態に紐づくケースを想定）
 * ========================================================== */
inline const ProgramDefinition FeatureSettings[] = {
    { ProgramDefinition::Kind::Feature,
      "skip", true,
      "", "", "", "既存のファイルはスキップ",
      "toolButton_skip" },

    { ProgramDefinition::Kind::Feature,
      "this_week", true,
      "", "", "", "",
      "checkBox_this_week" },

    { ProgramDefinition::Kind::Feature,
      "thumbnail", false,
      "", "", "", "サムネ付",
      "checkBox_thumbnail" },

    { ProgramDefinition::Kind::Feature,
      "koza_separation", true,
      "", "", "", "",
      "checkBox_koza_separation" },

    { ProgramDefinition::Kind::Feature,
      "multi_gui", false,
      "", "", "", "",
      "checkBox_multi_gui" },

    { ProgramDefinition::Kind::Feature,
      "name_space", true,
      "", "", "", "",
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "tag_space", true,
      "", "", "", "",
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "detailed_message", false,
      "", "", "", "",
      "toolButton_detailed_message" }
};
    // ===== チェックボックスフラグの数 =====
constexpr int FeatureCount = std::size(FeatureSettings);

  
    inline const QString KEY_basic0 = "basic0";
    inline const QString KEY_basic1 = "basic1";
    inline const QString KEY_basic2 = "basic2";
    inline const QString KEY_timetrial = "timetrial";
    inline const QString KEY_enjoy = "enjoy";
    inline const QString KEY_kaiwa =  "kaiwa";
    inline const QString KEY_business = "business1";
    inline const QString KEY_gendai = "gendai";
 
    inline const QString KEY_KOZA_SEPARATION = "koza_separation";
    inline const QString KEY_MULTI_GUI = "multi_gui";
    inline const QString KEY_NAME_SPACE = "name_space";
    inline const QString KEY_TAG_SPACE = "tag_space"; 
    
/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ------------------------------------------------------------
 * ini ファイルに保存されない RuntimeConfig で使用する Flag。
 * RuntimeConfig 生成時に default で初期化され、
 * Settings / GUI / CLI によって上書きされる。
 * Feature と重複する場合は後からの値が優先される。
 * ========================================================== */      
   struct FlagEntry {
    QString keyFlag;	// "nogui" など
    bool flagDefault;	// 初期値
};

    inline const QString KEY_NOGUI 	= "nogui";		// CLI: -nogui
    inline const QString KEY_LAST_WEEK 	= "last_week";		// GUI: [前週]、CLI: -z
    inline const QString KEY_BOTH_WEEKS	= "both_weeks";		// CLI: -b
    inline const QString KEY_PROGRAM_LIST = "program_list";	// GUI: 番組一覧表示

inline const FlagEntry FlagTable[] = {
    { KEY_NOGUI, 	false },	// CLI: -nogui = true
    { KEY_LAST_WEEK, 	false },	// [前週]チェック = true
    { KEY_BOTH_WEEKS, 	false },	// CLI: -b = true
    { KEY_PROGRAM_LIST, false },	// 番組一覧表示 = true
    { "featureX",  true  } 	// ini に保存される Feature でもよい
}; 
     // ===== フラグの数 =====
constexpr int FlagCount = std::size(FlagTable);   
    
    
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

inline const QString KEY_CUSTOMIZED_TITLE1 	= "customized_title1";
inline const QString KEY_CUSTOMIZED_TITLE2 	= "customized_title2";

inline const Item TITLE_ITEMS[] = {
    { KEY_CUSTOMIZED_TITLE1, "%f" },
    { KEY_CUSTOMIZED_TITLE2, "%k_%Y_%M_%D" }
};

inline const QString KEY_CUSTOMIZED_FILENAME1 	= "customized_file_name1";
inline const QString KEY_CUSTOMIZED_FILENAME2 	= "customized_file_name2";

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
