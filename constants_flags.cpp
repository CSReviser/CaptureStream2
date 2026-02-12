#include "constants_flags.h"

namespace Constants {

/* ============================================================
 * Feature（チェックボックス）
 * ========================================================== */
const ProgramDefinition FeatureSettings[] = {
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

// 個数取得の実装
int getFeatureCount() {
    return sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);
}

/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ========================================================== */   
const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },
    { KEY_LAST_WEEK,    false },
    { KEY_BOTH_WEEKS,   false },
    { KEY_PROGRAM_LIST, false },
    { "featureX",       true  }
};

// 個数取得の実装
int getFlagCount() {
    return sizeof(FlagTable) / sizeof(FlagTable[0]);
}

}
