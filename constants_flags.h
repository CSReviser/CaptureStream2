// constants_flags.h
#pragma once
#include "constants_core.h"
#include "constants_programs.h"

namespace Constants {

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
      nullptr, nullptr, false, false,
      "skip_keyLabel", "既存のファイルはスキップ", false, true,
      "toolButton_skip" },

    { ProgramDefinition::Kind::Feature,
      "this_week", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_this_week" },

    { ProgramDefinition::Kind::Feature,
      "thumbnail", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_thumbnail" },

    { ProgramDefinition::Kind::Feature,
      "koza_separation", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_koza_separation" },

    { ProgramDefinition::Kind::Feature,
      "multi_gui", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_multi_gui" },

    { ProgramDefinition::Kind::Feature,
      "name_space", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "tag_space", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "detailed_message", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "toolButton_detailed_message" }
};

// ===== チェックボックスフラグの数 =====
inline constexpr int FeatureCount =
    sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);


// ---- Flag ----
struct FlagEntry {
    const char* keyFlag;	// "nogui" など
    bool flagDefault;		// 初期値
};


/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ------------------------------------------------------------
 * ini ファイルに保存されない RuntimeConfig で使用する Flag。
 * RuntimeConfig 生成時に default で初期化され、
 * Settings / GUI / CLI によって上書きされる。
 * Feature と重複する場合は後からの値が優先される。
 * ========================================================== */   
inline const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },	// CLI: -nogui = true
    { KEY_LAST_WEEK,    false },	// [前週]チェック = true
    { KEY_BOTH_WEEKS,   false },	// CLI: -b = true
    { KEY_PROGRAM_LIST, false },	// 番組一覧表示 = true
    { "featureX",       true  } 	// ini に保存される Feature でもよい
};

inline constexpr int FlagCount = 
    sizeof(FlagTable) / sizeof(FlagTable[0]);

}





