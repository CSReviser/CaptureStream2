#pragma once

#include <QString>
#include <QStringList>
#include <functional>
#include <atomic>

struct FfmpegRunRequest
{
    QString program;
    QStringList args;

    int maxRetry = 3;
    int baseDelayMs = 1000;
    int idleTimeoutMs = 30000;

    QString finalPath;
    QString saveFolder;
    QString extension;
};

class FfmpegRunner
{
public:
    struct Result {
        int exitCode = -1;
        bool success = false;
        bool canceled = false;
        int attempts = 0;
        QString lastLog;
    };

    using LogCallback = std::function<void(const QString&)>;

public:
    FfmpegRunner();

    // ★ 修正
    Result run(const FfmpegRunRequest& plan);

    void requestCancel();
    void setLogCallback(LogCallback cb);

private:
    // ★ 修正
    int runOnce(const FfmpegRunRequest& plan, QString& outLog);

    bool shouldRetry(int exitCode, const QString& log) const;
    bool isPermanentError(const QString& log) const;

    // ★ 修正
    QString makeTempPath(const FfmpegRunRequest& plan) const;

    bool safeReplace(const QString& tempPath, const QString& finalPath) const;

private:
    std::atomic<bool> m_cancelRequested { false };
    std::atomic<bool> m_running { false };

    LogCallback m_logCallback;
};