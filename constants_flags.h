// constants_flags.h
#pragma once
#include "constants_core.h"
#include "constants_programs.h"

namespace Constants {

// ---- Feature ----
extern const ProgramDefinition FeatureSettings[];
extern const int FeatureCount;


// ---- Flag ----
struct FlagEntry {
    const char* keyFlag;	// "nogui" など
    bool flagDefault;		// 初期値
};

extern const FlagEntry FlagTable[];
extern const int FlagCount;

}

