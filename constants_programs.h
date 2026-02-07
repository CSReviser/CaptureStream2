// constants_programs.h
#pragma once
namespace Constants {

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
    const char* keyChecked;
    bool    checkedDefault;

    // id の保存キーとデフォルト値（English/Feature は空）
    const char* keyId;
    const char* idDefault;

    // label の保存キーとデフォルト値（English は固定値、Feature は空）
    const char* keyLabel;
    const char* labelDefault;

    // UI の objectName（Feature で空の場合もある）
    const char* objectName;
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

  



}
