#include "clicontroller.h"
#include "programrepository.h"
#include "commandlineparser.h"

#include <QEventLoop>
#include <QDebug>


CLIController::CLIController(const Settings& settings, int argc, char** argv)
    : m_settings(settings)
    , m_argc(argc)
    , m_argv(argv)
{
}

int CLIController::run()
{
    // Repository は main で準備済みという前提
    // 2. コマンドライン解析（抽象化済みパーサー）
    CliOptions opts = CommandLineParser::parse(m_argc, m_argv);

    // 3. オプション妥当性確認
    if (!validateOptions(opts)) {
        qWarning() << "CLI option validation failed.";
        return 1;
    }

    // 4. Settings → RuntimeConfig へ反映
    RuntimeConfig config;
    config.applySettings(m_settings);

    // 5. CLI オプションで RuntimeConfig を上書き
    applyCliOverrides(config, opts);

    // 6. 実行
    RecordingOrchestrator orchestrator(&config);
    return orchestrator.runHeadless();
}

bool CLIController::validateOptions(const CliOptions& opts) const
{
    // 値付きオプションの簡易チェック（空文字など）
    for (auto it = opts.optionValues.constBegin(); it != opts.optionValues.constEnd(); ++it) {
        const QString& key = it.key();
        const QString& value = it.value();

        if (value.isEmpty()) {
            qWarning() << "Empty value for option key:" << key;
            return false;
        }
        // 必要なら key ごとの詳細チェックをここに追加
    }

    // 番組IDの妥当性確認
    if (!validateProgramIds(opts)) {
        return false;
    }

    return true;
}

bool CLIController::validateProgramIds(const CliOptions& opts) const
{
    ProgramRepository& repo = ProgramRepository::instance();

    // ProgramRepository 側に id_map へのアクセサがある前提
    // 例: const QHash<QString, QString>& ProgramRepository::idMap() const;
    const QHash<QString, QString>& idMap = repo.id_map;

    for (const QString& id : opts.programIds) {
        if (!idMap.contains(id)) {
            qWarning() << "Unknown program ID:" << id;
            return false;
        }
    }
    return true;
}

void CLIController::applyCliOverrides(RuntimeConfig& config, const CliOptions& opts) const
{
    // 値付きオプション
    for (auto it = opts.optionValues.constBegin(); it != opts.optionValues.constEnd(); ++it) {
        const QString& key = it.key();
        const QString& value = it.value();
        // RuntimeConfig が QString キーを受け取る前提
        config.setValue(key, value);
    }

    // フラグ（bool）
    for (const QString& key : opts.enabledFlags) {
        config.setValue(key, true);
    }

    // 番組ID（必要に応じて RuntimeConfig に渡す）
    if (!opts.programIds.empty()) {
        // 例: 最初の ID を対象とする場合
        // config.setValue("program_id", opts.programIds.front());
        // あるいは専用 API があればそちらを呼ぶ
    }
}
