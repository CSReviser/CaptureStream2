#pragma once
#include <QString>
#include "settings.h"
#include "runtimeconfig.h"

class CLIController {
public:
    CLIController(const Settings& settings, int argc, char** argv);
    int run();
    bool validateOptions(const CliOptions& opts) const;
    bool validateProgramIds(const CliOptions& opts) const;
    void applyCliOverrides(RuntimeConfig& config, const CliOptions& opts) const;
    
private:
    const Settings& m_settings;   // ← 参照にする
    int m_argc;
    char** m_argv;


};
