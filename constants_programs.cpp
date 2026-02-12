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
const QVector<QStringList>& getOptPresets() {
    static const QVector<QStringList> instance = { /* 元のデータ */ };
    return instance;
}

const QVector<QStringList>& getPresets() {
    static const QVector<QStringList> instance = { /* 元のデータ */ };
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

const CustomizePreset FILENAME_PRESETS[] = { { "%k_%Y_%M_%D", "Preset 0" }, { "%f_%Y_%M_%D", "Preset 1" }, /* ... */ };
const int FILENAME_PRESET_COUNT = sizeof(FILENAME_PRESETS) / sizeof(FILENAME_PRESETS[0]);

const CustomizePreset TITLE_PRESETS[] = { { "%k_%Y_%M_%D", "Preset 0" }, { "%f_%Y_%M_%D", "Preset 1" }, /* ... */ };
const int TITLE_PRESETS_COUNT = sizeof(TITLE_PRESETS) / sizeof(TITLE_PRESETS[0]);

} // namespace Constants
