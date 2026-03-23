#include "ffmpegexecutor.h"

FfmpegResult FfmpegExecutor::run(const QString& program,
                                 const QStringList& args,
                                 int timeoutMs)
{
    FfmpegResult result;

    QProcess process;

    // =========================
    // プロセス設定
    // =========================
    process.setProgram(program);
    process.setArguments(args);

    // stdout / stderr を分離
    process.setProcessChannelMode(QProcess::SeparateChannels);

    // =========================
    // 起動
    // =========================
    process.start();

    if (!process.waitForStarted(5000)) {
        result.started = false;
        result.processError = process.error();
        return result;
    }

    result.started = true;

    // =========================
    // 実行待ち
    // =========================
    bool finished = false;

    if (timeoutMs < 0) {
        // 無制限（基本これ）
        finished = process.waitForFinished(-1);
    } else {
        finished = process.waitForFinished(timeoutMs);
    }

    // =========================
    // タイムアウト対応
    // =========================
    if (!finished) {
        process.kill();
        process.waitForFinished(3000);

        result.exitCode = -1;
        result.processError = QProcess::Timedout;
        result.stdOut = process.readAllStandardOutput();
        result.stdErr = process.readAllStandardError();
        return result;
    }

    // =========================
    // 結果取得
    // =========================
    result.exitCode = process.exitCode();
    result.processError = process.error();

    result.stdOut = process.readAllStandardOutput();
    result.stdErr = process.readAllStandardError();

    return result;
}