#include "constants_flags.h"

namespace Constants {

/* Feature */
const ProgramDefinition FeatureSettings[] = {
    { ProgramDefinition::Kind::Feature, "skip", true, "", "", "", "既存のファイルはスキップ", "toolButton_skip" },
    { ProgramDefinition::Kind::Feature, "this_week", true, "", "", "", "", "checkBox_this_week" },
    { ProgramDefinition::Kind::Feature, "thumbnail", false, "", "", "", "サムネ付", "checkBox_thumbnail" },
    { ProgramDefinition::Kind::Feature, "koza_separation", true, "", "", "", "", "checkBox_koza_separation" },
    { ProgramDefinition::Kind::Feature, "multi_gui", false, "", "", "", "", "checkBox_multi_gui" },
    { ProgramDefinition::Kind::Feature, "name_space", true, "", "", "", "", "checkBox" },
    { ProgramDefinition::Kind::Feature, "tag_space", true, "", "", "", "", "checkBox" },
    { ProgramDefinition::Kind::Feature, "detailed_message", false, "", "", "", "", "toolButton_detailed_message" }
};

const int FeatureCount =
    sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);


/* Flag */
const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },
    { KEY_LAST_WEEK,    false },
    { KEY_BOTH_WEEKS,   false },
    { KEY_PROGRAM_LIST, false },
    { "featureX",       true  }
};

const int FlagCount =
    sizeof(FlagTable) / sizeof(FlagTable[0]);

}