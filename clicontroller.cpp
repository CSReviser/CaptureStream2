#include "clicontroller.h"
#include "recordingorchestrator.h"

CLIController::CLIController(const Settings& settings,
                             const CommandLineOptions& opts)
    : m_settings(settings), m_opts(opts)
{
}

int CLIController::run()
{
    // 1. CLI オプション妥当性チェック
    if (!validateOptions()) {
        qWarning() << "Invalid CLI options";
        return 1;
    }

    // 2. Settings → RuntimeConfig
    RuntimeConfig config;
    config.applySettings(m_settings);

    // 3. CLI オプションで上書き
    applyCliOverrides(config);

    // 4. 実行プログラムへ制御移譲
    RecordingOrchestrator orchestrator(config);
    return orchestrator.runHeadless();
}

bool CLIController::validateOptions() const
{
    // TODO: 実装
    return true;
}

void CLIController::applyCliOverrides(RuntimeConfig& config) const
{
    // TODO: CLI オプションを反映
}
