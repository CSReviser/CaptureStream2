#include "clicontroller.h"
#include "commandlineparser.h"
#include "programrepository.h"
#include "recordingcore.h"
//#include "clioptions.h"

#include <QDebug>



CLIController::CLIController(const Settings& settings, int argc, char** argv)
    : m_settings(settings)
    , m_argc(argc)
    , m_argv(argv)
{
}

int CLIController::run()
{

    // 1. Repositoryの開始（appが必要な場合があるためここ）
    ProgramRepository::instance().start();

 //   if (!ProgramRepository::instance().waitUntilReady()) {
 //           qCritical() << "Failed to initialize program repository";
 //           return 1;
//    }
        
    // 2. CLI オプション解析（抽象化済みパーサー）
    CliOptions opts = CommandLineParser::parse(m_argc, m_argv);

    // 3. オプション検証
    if (!validateOptions(opts)) {
        qWarning() << "CLI option validation failed.";
        return 1;
    }

    // 4. RuntimeConfig 構築
    // Settings → RuntimeConfig へ反映
    RuntimeConfig config;
    config.applySettings(m_settings);
qDebug() << "config.applySettings(m_settings)";  
    // 5. CLI 上書き適用
    config.applyCommandLine(opts);
qDebug() << "config.applyCommandLine(opts);";  
    // 6. 実行（RecordingCore は QThread）
    RecordingCore core(config);
qDebug() << "RecordingCore core(config)";  
    core.start();   // QThread の開始
qDebug() << "core.start()";  
    core.wait();    // 終了待ち
qDebug() << "core.wait()"; 
    return 0;       // とりあえず仮
}

bool CLIController::validateOptions(const CliOptions& opts) const
{
    // 値付きオプションの簡易チェック（空文字など）
    for (auto it = opts.valueOptions.constBegin(); it != opts.valueOptions.constEnd(); ++it) {
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
    const QMap<QString, QString>& idMap = repo.id_map;

    for (const QString& id : opts.programIds) {
        if (!idMap.contains(id)) {
            qWarning() << "Unknown program ID:" << id;
            return false;
        }
    }
    return true;
}

