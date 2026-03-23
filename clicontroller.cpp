/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
	NHK radio language courses.
	CaptureStream2 is a modified version of CaptureStream, originally 
	developed by jakago.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-2.0.html>.
*/

#include "clicontroller.h"
#include "commandlineparser.h"
#include "programrepository.h"
#include "recordingcore.h"
//#include "clioptions.h"

#include <QDebug>
#include <iostream>
#include <QProcess>

CLIController::CLIController(const Settings& settings, int argc, char** argv)
    : m_settings(settings)
    , m_argc(argc)
    , m_argv(argv)
{
    // 1. Repositoryの開始（appが必要な場合があるためここ）
    ProgramRepository::instance().start();
}

int CLIController::run()
{
    if (!ProgramRepository::instance().waitUntilReady()) {
           qCritical() << "Failed to initialize program repository";
           return 1;
    } 
    testFfmpeg();  
    // 2. CLI オプション解析（抽象化済みパーサー）
    CliOptions opts = CommandLineParser::parse(m_argc, m_argv);

    // --- DEBUG: CommandLineParser の解析結果を表示 ---
    qDebug() << "--- [DEBUG] CommandLineParser Results ---";
    qDebug() << "Program IDs:" << opts.programIds;
    for (auto it = opts.valueOptions.constBegin(); it != opts.valueOptions.constEnd(); ++it) {
        qDebug() << "Value Option:" << it.key() << "=" << it.value();
    }
    for (const QString& flag : opts.enabledFlags) {
        qDebug() << "Flag detected:" << flag;
    }
    // -----------------------------------------------

    // 3. オプション検証
    if (!validateOptions(opts)) {
        qWarning() << "CLI option validation failed.";
        return 1;
    }

    // 4. RuntimeConfig 構築
    // Settings → RuntimeConfig へ反映
    RuntimeConfig config;
    config.applySettings(m_settings);

    // 5. CLI 上書き適用
    config.applyCommandLine(opts);

    // --- DEBUG: OPTION_TABLE に基づく RuntimeConfig の最終状態表示 ---
    qDebug() << "--- [DEBUG] RuntimeConfig State Check (via OPTION_TABLE) ---";
    
    int tableCount = Constants::getOptionTableCount();
    for (int i = 0; i < tableCount; ++i) {
        const auto& optEntry = Constants::OPTION_TABLE[i];
        QString internalKey = QString::fromUtf8(optEntry.keyOption);
        
        // 値を持つオプションかフラグかによって判定を分ける

        if (optEntry.requiresValue) {

            // 値オプションの確認（空でない場合のみ表示、または設定値を表示）
            QString currentVal = opts.valueOptions.value(internalKey); // RuntimeConfigにvalue()メソッドがある想定
            qDebug() << QString("Option [%1] (%2): %3")
                        .arg(optEntry.name)
                        .arg(internalKey)
                        .arg(currentVal.isEmpty() ? "(Not Set)" : currentVal);
            
        } else {

            // フラグ（bool）の確認
            bool isSet = config.flag(internalKey);
            qDebug() << QString("Flag   [%1] (%2): %3")
                        .arg(optEntry.name)
                        .arg(internalKey)
                        .arg(isSet ? "ON" : "OFF");
        }
    }



    // 6. 実行（RecordingCore は QThread）
    RecordingCore core(config);

    if (config.flag( QString::fromUtf8(Constants::KEY_HELP))) {
        showHelp();
        return 0;
    }


 
    //
    // ★★★ ここがポイント：-m のときだけメッセージ出力を接続 ★★★
    //
    if (config.flag( QString::fromUtf8(Constants::KEY_MESSAGE_ON))) {
        QObject::connect(&core, &RecordingCore::messageGenerated,
                         [](const QString &msg){
                             std::cout << msg.toStdString() << std::endl;
                         });

        QObject::connect(&core, &RecordingCore::errorOccurred,
                         [](const QString &msg){
                             std::cerr << msg.toStdString() << std::endl;
                         });

        QObject::connect(&core, &RecordingCore::progressChanged,
                         [](int percent){
                             std::cout << "Progress: " << percent << "%" << std::endl;
                         });
    }

    // 終了通知は常に受け取ってもよい（任意）
    QObject::connect(&core, &RecordingCore::finished,
                     [](){
                         // 必要なら終了メッセージ
                     });

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

void CLIController::showHelp()
{
    QTextStream out(stdout);

    out << QString::fromUtf8(Constants::HELP_USAGE) << "\n\n";
    out << QString::fromUtf8(Constants::HELP_HEADER) << "\n\n";

    QMap<QString, QStringList> groupOptions;
    QMap<QString, QString> groupDesc;
    QMap<QString, bool> groupValue;

    const int count = Constants::getOptionTableCount();

    for (int i = 0; i < count; ++i) {

        const auto &opt = Constants::OPTION_TABLE[i];
        
        QString group;

        if (opt.group)
            group = QString::fromUtf8(opt.group);
        else
            group = QString::fromUtf8(opt.name);

        groupOptions[group].append(QString::fromUtf8(opt.name));
        groupDesc[group] = QString::fromUtf8(opt.description);
        groupValue[group] = opt.requiresValue;
    }

    for (auto it = groupOptions.begin(); it != groupOptions.end(); ++it)
    {
        QString names = it.value().join(" / ");

        if (groupValue[it.key()])
            names += " <value>";

        out << "  " << names << "\n";
        out << "      " << groupDesc[it.key()] << "\n\n";
    }

    out << QString::fromUtf8(Constants::HELP_PROGRAMID) << "\n";
}

// =========================
// 仮の構造体（未実装対策）
// =========================

enum class Container {
    MP3,
    M4A,
    AAC
};

struct AudioFormat {
    QString codec;
    QString bitrate;
    int channels = 2;
    QString sampleRate;
    bool copyCodec = false;
};

struct Metadata {
    QString title;
};

struct InputOptions {
    QString inputPath;
};

struct RecordingRequest {
    InputOptions input;
    AudioFormat format;
    Metadata meta;
    Container container;
    QString outputPath;
};

struct FfmpegCapabilities {
    bool httpSeekableSupported = false;
};

// =========================
// 仮Builder（未実装ならこれで代用）
// =========================
QStringList buildTestCommand(const RecordingRequest& req)
{
    QStringList args;

    args << "-y";
    args << "-i" << req.input.inputPath;

    args << "-c:a" << "libmp3lame";
    args << "-b:a" << req.format.bitrate;
    args << "-ac" << QString::number(req.format.channels);

    if (!req.meta.title.isEmpty()) {
        args << "-metadata" << "title=" + req.meta.title;
    }

    args << req.outputPath;

    return args;
}

// =========================
// テスト実行
// =========================
void CLIController::testFfmpeg()
{
    RecordingRequest req;

    req.input.inputPath = "input.aac";
    req.outputPath = "output.m4a";
    req.format.bitrate = "128k";
    req.format.channels = 2;
    req.meta.title = "test";
//  req.container = Container::MP3;
    req.container = Container::M4A;
    FfmpegCapabilities caps;

    // ★ Builder未実装ならこれ
    QStringList args = buildTestCommand(req);

    // ★ Builder実装済ならこれに切り替え
    // QStringList args = FfmpegCommandBuilder::build(req, caps);

    if (args.isEmpty()) {
        qDebug() << "Command build failed";
        return;
    }

    // コマンド確認
    qDebug() << "ffmpeg" << args.join(" ");

    // =========================
    // 実行
    // =========================
    QProcess process;

    process.setProgram("ffmpeg"); // フルパスでもOK
    process.setArguments(args);

    process.start();

    if (!process.waitForStarted()) {
        qDebug() << "Failed to start ffmpeg";
        return;
    }

    process.waitForFinished(-1);

    qDebug() << "Exit code:" << process.exitCode();
    qDebug() << "STDOUT:\n" << process.readAllStandardOutput();
    qDebug() << "STDERR:\n" << process.readAllStandardError();
}
