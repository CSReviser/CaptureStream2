#include "constants_flags.h"

namespace Constants {

/* ============================================================
 * Feature（チェックボックス）
 * ------------------------------------------------------------
 * checked のみ保存する。
 * id は不要なので空文字。checkBoxはlabelも空文字。
 * objectName が同一のエントリは、同一の UI ウィジェットを共有する。
 * （複数の設定値が 1 つの UI 状態に紐づくケースを想定）
 * ========================================================== */
const ProgramDefinition FeatureSettings[] = {
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
const int FeatureCount =
    sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);


/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ------------------------------------------------------------
 * ini ファイルに保存されない RuntimeConfig で使用する Flag。
 * RuntimeConfig 生成時に default で初期化され、
 * Settings / GUI / CLI によって上書きされる。
 * Feature と重複する場合は後からの値が優先される。
 * ========================================================== */   
const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },	// CLI: -nogui = true
    { KEY_LAST_WEEK,    false },	// [前週]チェック = true
    { KEY_BOTH_WEEKS,   false },	// CLI: -b = true
    { KEY_PROGRAM_LIST, false },	// 番組一覧表示 = true
    { "featureX",       true  } 	// ini に保存される Feature でもよい
};

const int FlagCount =
    sizeof(FlagTable) / sizeof(FlagTable[0]);

}

