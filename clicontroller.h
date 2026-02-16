#pragma once

#include "settings.h"
#include "runtimeconfig.h"
#include "commandlineoptions.h"

class CLIController {
public:
    CLIController(const Settings& settings,
                  const CommandLineOptions& opts);

    int run();

private:
    bool validateOptions() const;
    void applyCliOverrides(RuntimeConfig& config) const;

    Settings m_settings;
    CommandLineOptions m_opts;
};
