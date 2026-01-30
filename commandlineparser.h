// CommandLineParser.h
#pragma once
#include "RecordingConfig.h"

class CommandLineParser {
public:
    RecordingConfig parse(int argc, char* argv[]);
};