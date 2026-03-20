/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

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

#include "constants_programs.h"
#include "constants_core.h" // KEY_... などの参照用

namespace Constants {

// ===== English（固定番組） =====
const ProgramDefinition EnglishPrograms[] = {
    { ProgramDefinition::Kind::English, "basic0", false, "basic0_keyId", "GGQY3M1929_01", false, true, "basic0_keyLabel", "小学生の基礎英語", false, true, "toolButton_basic0" },
    { ProgramDefinition::Kind::English, "basic1", false, "basic1_keyId", "148W8XX226_01", false, true, "basic1_keyLabel", "基礎英語 【レベル１】", false, true, "toolButton_basic1" },
    { ProgramDefinition::Kind::English, "basic2", false, "basic2_keyId", "83RW6PK3GG_01", false, true, "basic2_keyLabel", "基礎英語 【レベル２】", false, true, "toolButton_basic2" },
    { ProgramDefinition::Kind::English, "kaiwa",  false, "kaiwa_keyId", "PMMJ59J6N2_01", false, true, "kaiwa_keyLabel", "ラジオ英会話", false, true, "toolButton_kaiwa" },
    { ProgramDefinition::Kind::English, "enjoy",  false, "enjoy_keyId", "BR8Z3NX7XM_01", false, true, "enjoy_keyLabel", "エンジョイ・シンプル・イングリッシュ", false, true, "toolButton_enjoy" },
    { ProgramDefinition::Kind::English, "timetrial", false, "timetrial_keyId", "8Z6XJ6J415_01", false, true, "timetrial_keyLabel", "英会話タイムトライアル", false, true, "toolButton_timetrial" },
    { ProgramDefinition::Kind::English, "business1", false, "business1_keyId", "368315KKP8_01", false, true, "business1_keyLabel", "ラジオビジネス英語", false, true, "toolButton_business1" },
    { ProgramDefinition::Kind::English, "gendai", false, "gendai_keyId", "77RQWQX1L6_01", false, true, "gendai_keyLabel", "ニュースで学ぶ「現代英語」", false, true, "toolButton_gendai" }
};
const int EnglishCount = sizeof(EnglishPrograms) / sizeof(EnglishPrograms[0]);

// ===== Optional（任意設定番組） =====
const ProgramDefinition OptionalPrograms[] = {
    { ProgramDefinition::Kind::Optional, "optional_1", false, "optional1", "XQ487ZM61K_01", true, true, "opt_title1", "まいにちフランス語", true, true, "toolButton_optional1" },
    { ProgramDefinition::Kind::Optional, "optional_2", false, "optional2", "N8PZRZ9WQY_01", true, true, "opt_title2", "まいにちドイツ語", true, true, "toolButton_optional2" },
    { ProgramDefinition::Kind::Optional, "optional_3", false, "optional3", "LJWZP7XVMX_01", true, true, "opt_title3", "まいにちイタリア語", true, true, "toolButton_optional3" },
    { ProgramDefinition::Kind::Optional, "optional_4", false, "optional4", "NRZWXVGQ19_01", true, true, "opt_title4", "まいにちスペイン語", true, true, "toolButton_optional4" },
    { ProgramDefinition::Kind::Optional, "optional_5", false, "optional5", "YRLK72JZ7Q_01", true, true, "opt_title5", "まいにちロシア語", true, true, "toolButton_optional5" },
    { ProgramDefinition::Kind::Optional, "optional_6", false, "optional6", "N13V9K157Y_01", true, true, "opt_title6", "ポルトガル語", true, true, "toolButton_optional6" },
    { ProgramDefinition::Kind::Optional, "optional_7", false, "optional7", "983PKQPYN7_01", true, true, "opt_title7", "まいにち中国語", true, true, "toolButton_optional7" },
    { ProgramDefinition::Kind::Optional, "optional_8", false, "optional8", "LR47WW9K14_01", true, true, "opt_title8", "まいにちハングル講座", true, true, "toolButton_optional8" }
};
const int OptionalCount = sizeof(OptionalPrograms) / sizeof(OptionalPrograms[0]);

// ===== Spec（特番） =====
const ProgramDefinition SpecPrograms[] = {
    { ProgramDefinition::Kind::Spec, "special_1", false, "special1", "Y538W57WJ6_01", true, true, "spec_title1", "英語コミュニケーションII", true, true, "toolButton_special1" },
    { ProgramDefinition::Kind::Spec, "special_2", false, "special2", "GJ7L5ZXRZK_01", true, true, "spec_title2", "英語コミュニケーションIII", true, true, "toolButton_special2" },
    { ProgramDefinition::Kind::Spec, "special_3", false, "special3", "32225VXYVL_01", true, true, "spec_title3", "論理・表現I", true, true, "toolButton_special3" },
    { ProgramDefinition::Kind::Spec, "special_4", false, "special4", "54N237Z2GX_01", true, true, "spec_title4", "言語文化", true, true, "toolButton_special4" }
};
const int SpecCount = sizeof(SpecPrograms) / sizeof(SpecPrograms[0]);

// ===== 講座番組ID Map =====
const QMap<QString, QString>& getMap() {
    static const QMap<QString, QString> instance = { 
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
    return instance;
}


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
 



// ===== プリセット等（省略して記載しますが、同様に static で保持） =====
const std::vector<QStringList>& getOptPresets() {
    static const std::vector<QStringList> instance = {
    { "XQ487ZM61K_x1", "XQ487ZM61K_y1", "N8PZRZ9WQY_x1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_x1", "LJWZP7XVMX_y1", "NRZWXVGQ19_x1", "NRZWXVGQ19_y1" },
 //まいにちフランス語 入門編, //まいにちフランス語 応用編, //まいにちドイツ語 入門編／初級編, //まいにちドイツ語 応用編, //まいにちイタリア語 入門編, //まいにちイタリア語 応用編, //まいにちスペイン語 入門編／初級編 //まいにちスペイン語 中級編／応用編   
    { "983PKQPYN7_01", "LR47WW9K14_01", "NRZWXVGQ19_x1", "NRZWXVGQ19_y1", "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "N8PZRZ9WQY_01", "N13V9K157Y_01" },
//まいにち中国語, //まいにちハングル講座, //まいにちスペイン語, //まいにちスペイン語, //まいにちロシア語 入門編, //まいにちロシア語 応用編, //まいにちドイツ語  //ポルトガル語
    { "XQ487ZM61K_x1", "N8PZRZ9WQY_x1", "LJWZP7XVMX_x1", "NRZWXVGQ19_x1", "YRLK72JZ7Q_x1", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語 入門編, //まいにちドイツ語 入門編／初級編, //まいにちイタリア語 入門編, //まいにちスペイン語 入門編／初級編, //まいにちロシア語 入門編, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "XQ487ZM61K_y1", "N8PZRZ9WQY_y1", "LJWZP7XVMX_y1", "NRZWXVGQ19_y1", "YRLK72JZ7Q_y1", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語 応用編, //まいにちドイツ語 応用編, //まいにちイタリア語 応用編, //まいにちスペイン語 中級編／応用編, //まいにちロシア語 応用編, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "XQ487ZM61K_01", "N8PZRZ9WQY_01", "LJWZP7XVMX_01", "NRZWXVGQ19_01", "YRLK72JZ7Q_01", "N13V9K157Y_01", "983PKQPYN7_01", "LR47WW9K14_01" },
//まいにちフランス語, //まいにちドイツ語, //まいにちイタリア語, //まいにちスペイン語, //まいにちロシア語, //ポルトガル語, //まいにち中国語  //まいにちハングル講座
    { "4M1RMVM8P1_01", "V34XVV71R2_08", "GLW7RX3PXL_01", "YR96XR51MZ_01", "X4X6N1XG8Z_01", "D85RZVGX7W_01", "LRK2VXPK5X_01", "M65G6QLKMY_01" },
//新書太閤記, //もっと、豊臣兄弟, //お話でてこい, //朗読の世界, //青春アドベンチャー, //新日曜名作座, //朗読  //FMシアター 
    { "R5XR783QK3_01", "NJZR87XYYV_01", "5L3859P515_01", "566V9ZMX35_01", "YR96XR51MZ_01", "X78J5NKWM9_01", "MVYJ6PRZMX_01", "JWQ88ZVWQK_01" }
//おしゃべりな古典教室, //日曜カルチャー, //古典講読 //日曜討論, //朗読の世界 //こころをよむ, //アナウンサー百年百話  //宗教の時間
};
    return instance;
}

const std::vector<QStringList>& getPresets() {
    static const std::vector<QStringList> instance = {
    { "Y538W57WJ6_01", "GJ7L5ZXRZK_01", "32225VXYVL_01", "54N237Z2GX_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "983PKQPYN7_01", "LR47WW9K14_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "983PKQPYN7_01", "N13V9K157Y_01" },
    { "983PKQPYN7_01", "LR47WW9K14_01", "LR47WW9K14_01", "N13V9K157Y_01" },
    { "J8792PY43V_20", "X7R2P2PW5P_02", "L6ZQ2NX1NL_01", "34PY344RPJ_01" },
    { "X4X6N1XG8Z_01", "D85RZVGX7W_01", "YR96XR51MZ_01", "M65G6QLKMY_01" },
    { "R5XR783QK3_01", "X78J5NKWM9_01", "5L3859P515_01", "JWQ88ZVWQK_01" }
};
    return instance;
}

// ===== その他（Item, CustomizePreset）の実体 =====
const Item TITLE_ITEMS[] = { { KEY_CUSTOMIZED_TITLE1, "%f" }, { KEY_CUSTOMIZED_TITLE2, "%k_%Y_%M_%D" } };
const Item FILENAME_ITEMS[] = { { KEY_CUSTOMIZED_FILENAME1, "%k_%Y_%M_%D" }, { KEY_CUSTOMIZED_FILENAME2, "%k_%Y_%M_%D" } };
const int ITEM_COUNT = sizeof(FILENAME_ITEMS) / sizeof(FILENAME_ITEMS[0]);
    int getItemCount() { return sizeof(FILENAME_ITEMS) / sizeof(FILENAME_ITEMS[0]); }
    
const CustomizePreset FILENAME_PRESETS[] = { 
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};
const int FILENAME_PRESET_COUNT = sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]);

const CustomizePreset TITLE_PRESETS[] = {
    { "%k_%Y_%M_%D",   "Preset 0" },
    { "%f_%Y_%M_%D",   "Preset 1" },
    { "%k_%Y-%M-%D",   "Preset 2" },
    { "%h",            "Preset 3" },
    { "%f",            "Preset 4" },
    { "%k_%h",         "Preset 5" },
    { "%y%M%D_%k%x",   "Preset 6" }
};
const int TITLE_PRESETS_COUNT = sizeof(TITLE_PRESETS) / sizeof(TITLE_PRESETS[0]);

const char* AUDIO_EXT_LIST[] = {
        "aac",
        "m4a",
        "mp3",
        "mp3-128k-S",
        "mp3-64k-S",
        "mp3-48k-S",
        "mp3-40k-S",
        "mp3-32k-S",
        "mp3-40k-M",
        "mp3-32k-M",
        "mp3-24k-M",
        "mp3-16k-M"        
};
const int AUDIO_EXT_COUNT = sizeof(AUDIO_EXT_LIST) / sizeof(AUDIO_EXT_LIST[0]);

    // --- カウント関数の実装：呼び出された瞬間に sizeof で計算して返す ---
    int getEnglishCount()  { return sizeof(EnglishPrograms) / sizeof(EnglishPrograms[0]); }
    int getOptionalCount() { return sizeof(OptionalPrograms) / sizeof(OptionalPrograms[0]); }
    int getSpecCount()     { return sizeof(SpecPrograms) / sizeof(SpecPrograms[0]); }
    int getAudioExtCount() { return sizeof(AUDIO_EXT_LIST) / sizeof(AUDIO_EXT_LIST[0]); }    

// getPresetsCount なども必要であれば追加
int getOptPresetSize() { return static_cast<int>(getOptPresets().size()); }
int getPresetSize()    { return static_cast<int>(getPresets().size()); }

// プリセット等の個数も sizeof で
int getFilenamePresetCount() { return sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]); }
int getTitlePresetCount()    { return sizeof(TITLE_PRESETS) / sizeof(TITLE_PRESETS[0]); }

const char* PROGRAM_KEYWORDS_ENGLISH[] = {
    "英語",
    "英会話",
    "イングリッシュ",
    "ボキャブライダー"
};

const int PROGRAM_KEYWORDS_ENGLISH_COUNT =
    sizeof(PROGRAM_KEYWORDS_ENGLISH) / sizeof(PROGRAM_KEYWORDS_ENGLISH[0]);

const char* PROGRAM_KEYWORDS_OTHER[] = {
    "まいにち",
    "中国語",
    "ハングル",
    "ポルトガル"
};

const int PROGRAM_KEYWORDS_OTHER_COUNT =
    sizeof(PROGRAM_KEYWORDS_OTHER) / sizeof(PROGRAM_KEYWORDS_OTHER[0]);

const char* PROGRAM_EXCLUDE_TAG = "【中級編】";

const OptionPresetLabel OPTION_LABEL[] = { 
    { "radioButton_0", "欧州（仏、独、伊、西）" },
    { "radioButton_1", "アジア、他（露、中、韓、葡）" },
    { "radioButton_2", "入門編、初級編" },
    { "radioButton_3", "応用編、ステップアップ" },
    { "radioButton_4", "欧州(仏,独,伊,西,露,葡) ＋ 中、韓" },
    { "radioButton_5", "その他" }
};
const int OPTION_LABEL_COUNT = sizeof(OPTION_LABEL) / sizeof(OPTION_LABEL[0]);
int getOptionLabelCount() { return sizeof(OPTION_LABEL) / sizeof(OPTION_LABEL[0]); }

const SpecPresetLabel SPEC_LABEL[] = { 
    { "radioButton", "高校講座（英語科）" },
    { "radioButton_1", "ロシア語 、中国語、ハングル講座" },
    { "radioButton_2", "ロシア語 、アラビア語、ポルトガル語" },
    { "radioButton_3", "中国語、ハングル講座、アラビア語、ポルトガル語" },
    { "radioButton_4", "ニュース" },
    { "radioButton_5", "ドラマ" }
};
const int SPEC_LABEL_COUNT = sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]);
int getSpecLabelCount() { return sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]); }

} // namespace Constants

