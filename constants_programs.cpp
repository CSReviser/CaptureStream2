#include "constants_programs.h"
#include "constants_core.h" // KEY_... などの参照用

namespace Constants {

// ===== English（固定番組） =====
const ProgramDefinition EnglishPrograms[] = {
    { ProgramDefinition::Kind::English, "basic0", false, "basic0_keyId", "GGQY3M1929_01", false, true, "basic0_keyLabel", "小学生の基礎英語", false, true, "toolButton_basic0" },
    { ProgramDefinition::Kind::English, "basic1", false, "basic1_keyId", "148W8XX226_01", false, true, "basic1_keyLabel", "中学生の基礎英語 【レベル１】", false, true, "toolButton_basic1" },
    { ProgramDefinition::Kind::English, "basic2", false, "basic2_keyId", "83RW6PK3GG_01", false, true, "basic2_keyLabel", "中学生の基礎英語 【レベル２】", false, true, "toolButton_basic2" },
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
    { ProgramDefinition::Kind::Spec, "special_1", false, "special1", "6LPPKP6W8Q_01", true, true, "spec_title1", "やさしい日本語", true, true, "toolButton_special1" },
    { ProgramDefinition::Kind::Spec, "special_2", false, "special2", "WKMNWGMN6R_01", true, true, "spec_title2", "アラビア語講座", true, true, "toolButton_special2" },
    { ProgramDefinition::Kind::Spec, "special_3", false, "special3", "GLZQ4M519X_01", true, true, "spec_title3", "Asian View", true, true, "toolButton_special3" },
    { ProgramDefinition::Kind::Spec, "special_4", false, "special4", "4MY6Q8XP88_01", true, true, "spec_title4", "Living in Japan", true, true, "toolButton_special4" }
};
const int SpecCount = sizeof(SpecPrograms) / sizeof(SpecPrograms[0]);

// ===== 講座番組ID Map =====
const QMap<QString, QString>& getMap() {
    static const QMap<QString, QString> instance = { 
        { "GGQY3M1929_01", "english/basic0" }, { "148W8XX226_01", "english/basic1" },
        { "83RW6PK3GG_01", "english/basic2" }, { "8Z6XJ6J415_01", "english/timetrial" },
        { "PMMJ59J6N2_01", "english/kaiwa" }, { "368315KKP8_01", "english/business1" },
        { "BR8Z3NX7XM_01", "english/enjoy" }, { "77RQWQX1L6_01", "english/gendaieigo" },
        // ... (以下、元のQMapデータをすべてここに記述)
    };
    return instance;
}

// ===== プリセット等（省略して記載しますが、同様に static で保持） =====
const std::vector<QStringList>& getOptPresets() {
    static const std::vector<QStringList> instance = {
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
    return instance;
}

const std::vector<QStringList>& getPresets() {
    static const std::vector<QStringList> instance = {
    { "6LPPKP6W8Q_01", "WKMNWGMN6R_01", "GLZQ4M519X_01", "4MY6Q8XP88_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "983PKQPYN7_01", "LR47WW9K14_01" },
    { "YRLK72JZ7Q_x1", "YRLK72JZ7Q_y1", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "983PKQPYN7_01", "LR47WW9K14_01", "WKMNWGMN6R_01", "N13V9K157Y_01" },
    { "GLZQ4M519X_01", "X7R2P2PW5P_02", "L6ZQ2NX1NL_01", "34PY344RPJ_01" },
    { "X4X6N1XG8Z_01", "D85RZVGX7W_01", "YR96XR51MZ_01", "M65G6QLKMY_01" },
    { "R5XR783QK3_01", "X78J5NKWM9_01", "5L3859P515_01", "JWQ88ZVWQK_01" }
};
    return instance;
}

const QStringList& getCourses() {
    static const QStringList instance = { "json", "xml" };
    return instance;
}

// ===== その他（Item, CustomizePreset）の実体 =====
const Item TITLE_ITEMS[] = { { KEY_CUSTOMIZED_TITLE1, "%f" }, { KEY_CUSTOMIZED_TITLE2, "%k_%Y_%M_%D" } };
const Item FILENAME_ITEMS[] = { { KEY_CUSTOMIZED_FILENAME1, "%k_%Y_%M_%D" }, { KEY_CUSTOMIZED_FILENAME2, "%k_%Y_%M_%D" } };
const int ITEM_COUNT = sizeof(FILENAME_ITEMS) / sizeof(FILENAME_ITEMS[0]);
    int getItemCount() { return sizeof(FILENAME_ITEMS) / sizeof(FILENAME_ITEMS[0]); }
    
const CustomizePreset FILENAME_PRESETS[] = { { "%k_%Y_%M_%D", "Preset 0" }, { "%f_%Y_%M_%D", "Preset 1" }, /* ... */ };
const int FILENAME_PRESET_COUNT = sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]);

const CustomizePreset TITLE_PRESETS[] = { { "%k_%Y_%M_%D", "Preset 0" }, { "%f_%Y_%M_%D", "Preset 1" }, /* ... */ };
const int TITLE_PRESETS_COUNT = sizeof(TITLE_PRESETS) / sizeof(TITLE_PRESETS[0]);

    // --- カウント関数の実装：呼び出された瞬間に sizeof で計算して返す ---
    int getEnglishCount()  { return sizeof(EnglishPrograms) / sizeof(EnglishPrograms[0]); }
    int getOptionalCount() { return sizeof(OptionalPrograms) / sizeof(OptionalPrograms[0]); }
    int getSpecCount()     { return sizeof(SpecPrograms) / sizeof(SpecPrograms[0]); }
    

// getPresetsCount なども必要であれば追加
int getOptPresetSize() { return static_cast<int>(getOptPresets().size()); }
int getPresetSize()    { return static_cast<int>(getPresets().size()); }

// プリセット等の個数も sizeof で
int getFilenamePresetCount() { return sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]); }
int getTitlePresetCount()    { return sizeof(TITLE_PRESETS) / sizeof(TITLE_PRESETS[0]); }

} // namespace Constants

