#pragma once

#include <QString>
#include <QStringList>
#include <functional>
#include <atomic>
#include <QProcess>

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
    int runOnce(const FfmpegRunRequest& plan, QString& outLog);

    bool shouldRetry(int exitCode, const QString& log) const;
    bool isPermanentError(const QString& log) const;

    QProcess proc;
    QString makeTempPath(const FfmpegRunRequest& plan) const;

    bool safeReplace(const QString& tempPath, const QString& finalPath) const;

    std::atomic<bool> m_cancelRequested { false };
    std::atomic<bool> m_running { false };

    LogCallback m_logCallback;
    
    bool removeFileForce(const QString& path);
    
    static QString buildCommandString(const QString& program, const QStringList& args);
};
