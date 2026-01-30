// RecordingConfig.h
#pragma once
#include <QString>
#include <vector>
#include <optional>

struct RecordingConfig {
    bool nogui = false;

    std::vector<QString> programIds;

    std::optional<QString> titleTagFormat;   // -t
    std::optional<QString> fileNameFormat;   // -f
    std::optional<QString> outputFolder;     // -o
    std::optional<QString> extension;        // -e

    bool optionZ = false;  // -z
    bool optionB = false;  // -b
    bool optionS = false;  // -s

    bool hasProgramIds() const {
        return !programIds.empty();
    }
};