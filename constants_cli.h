// constants_cli.h
#pragma once
#include "constants_core.h"

namespace Constants {

struct CliOption {
    const char* name;
    bool requiresValue;
    const char* keyOption;	// GUI、Flagの キーと一致
    const char* description;
};

extern const CliOption OPTION_TABLE[];
extern const int OPTION_TABLE_COUNT;

}
