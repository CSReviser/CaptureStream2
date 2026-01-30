// CommandLineParser.cpp
#include "CommandLineParser.h"
#include "constants.h"
#include <QString>

RecordingConfig CommandLineParser::parse(int argc, char* argv[])
{
    RecordingConfig cfg;

    auto findOption = [&](const QString& arg) -> const CliOption* {
        for (int i = 0; i < OPTION_TABLE_COUNT; ++i) {
            if (arg == OPTION_TABLE[i].name)
                return &OPTION_TABLE[i];
        }
        return nullptr;
    };

    for (int i = 1; i < argc; ++i) {
        QString arg = argv[i];
        const CliOption* opt = findOption(arg);

        if (!opt) {
            // オプションでなければ番組IDとして扱う（無効でもエラーにしない）
            cfg.programIds.push_back(arg);
            continue;
        }

        // 値が必要なオプション
        if (opt->requiresValue) {
            if (i + 1 >= argc)
                break; // 値がない → 無視（仕様上エラーにしない）

            QString value = argv[++i];

            if (arg == "-t")      cfg.titleTagFormat = value;
            else if (arg == "-f") cfg.fileNameFormat = value;
            else if (arg == "-o") cfg.outputFolder = value;
            else if (arg == "-e") cfg.extension = value;
        }
        else {
            // フラグ型オプション
            if (arg == "-nogui") cfg.nogui = true;
            else if (arg == "-z") cfg.optionZ = true;
            else if (arg == "-b") cfg.optionB = true;
            else if (arg == "-s") cfg.optionS = true;
        }
    }

    // 番組IDがない場合は -z と -b 以外は無効（仕様）
    if (!cfg.hasProgramIds()) {
        cfg.titleTagFormat.reset();
        cfg.fileNameFormat.reset();
        cfg.outputFolder.reset();
        cfg.extension.reset();
        cfg.optionS = false;
    }

    return cfg;
}