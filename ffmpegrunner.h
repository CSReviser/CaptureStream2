#pragma once

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QFileInfo>
#include <QFile>
#include <QTemporaryFile>
#include "recordingrequest.h"
#include "ffmpegcommandbuilder.h"
#include "ffmpegcapabilities.h"

class FfmpegRunner : public QObject
{
    Q_OBJECT



public:
    explicit FfmpegRunner(QObject* parent = nullptr);

    void start(const RecordingRequest& req,
               const QString& ffmpegPath);

    void cancel();
    bool isRunning = false;
    bool run(const QStringList &args) {
        if (isRunning) {
            emit messageGenerated("既に実行中です");
            return false;
        }
        isRunning = true;
        connect(&process, &QProcess::finished, this, [this](int code, QProcess::ExitStatus status){
            isRunning = false;
            emit finished(code == 0);
        });
        process.start("ffmpeg", args);
        return true;
    }


signals:
    void messageGenerated(const QString &msg);
    void progressChanged(int percent);
    void errorOccurred(const QString &msg);
    void finished(bool success);

private slots:
    void onStarted();
    void onReadyReadStdErr();
    void onFinished(int exitCode, QProcess::ExitStatus status);

private:
    enum class State {
        Idle,
        Starting,
        Running,
        Cancelling
    };

    QString makeTempPath(const QString& finalPath);

private:
    QProcess process;

    QString tempPath;
    QString finalPath;

    State state = State::Idle;

    QByteArray stderrBuffer;
    
    std::unique_ptr<QTemporaryFile> tempFile;
    
    static QString getExtension(const QString &filePath);

};
