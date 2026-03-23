#pragma once

#include <QString>
#include <QStringList>
#include <QProcess>

// =========================
// 実行結果
// =========================
struct FfmpegResult {
    bool started = false;

    int exitCode = -1;
    QProcess::ProcessError processError = QProcess::UnknownError;

    QString stdOut;
    QString stdErr;
};

// =========================
// Executor
// =========================
class FfmpegExecutor
{
public:
    static FfmpegResult run(const QString& program,
                            const QStringList& args,
                            int timeoutMs = -1); // -1 = 無制限
};