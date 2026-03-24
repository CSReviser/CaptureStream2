#include "ffmpegrunner.h"
#include <QDir>
#include <QTemporaryFile>
#include <QRegularExpression>
#include <QFileInfo>
#include <QFile>
#include <QTimer>

// =========================
// ctor
// =========================
FfmpegRunner::FfmpegRunner(QObject* parent)
    : QObject(parent)
{
    connect(&process, &QProcess::started, this, &FfmpegRunner::onStarted);
    connect(&process, &QProcess::readyReadStandardError, this, &FfmpegRunner::onReadyReadStdErr);
    connect(&process,
            QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &FfmpegRunner::onFinished);
}

// =========================
// start
// =========================
void FfmpegRunner::start(const RecordingRequest& req,
                         const QString& ffmpegPath)
{
    if (state != State::Idle) {
        emit errorOccurred("既に実行中です");
        return;
    }

    if (req.outputPath.isEmpty()) {
        emit errorOccurred("出力パスが空です");
        return;
    }

    finalPath = req.outputPath;

    // --- 拡張子取得 ---
    QString ext = QFileInfo(finalPath).suffix();
    if (ext.isEmpty()) ext = "m4a"; // デフォルト

    // --- 一時ファイル作成 ---
    QString tmpTemplate = QDir::tempPath() + "/CaptureStream2_XXXXXX." + ext;
    tempFile = std::make_unique<QTemporaryFile>(tmpTemplate);

    if (!tempFile->open()) {
        emit errorOccurred("一時ファイル作成失敗");
        tempFile.reset();
        return;
    }

    tempPath = tempFile->fileName();
    tempFile->close(); // ffmpeg に書き込ませるために閉じる

    emit messageGenerated("finalPath: " + finalPath);
    emit messageGenerated("tempPath: " + tempPath);

    // --- ffmpeg コマンド生成 ---
    FfmpegCapabilities caps = FfmpegCapabilities::detect(ffmpegPath);
    QStringList args = FfmpegCommandBuilder::build(req, caps, tempPath);

    if (args.isEmpty()) {
        emit errorOccurred("ffmpeg引数生成失敗");
        tempFile.reset();
        return;
    }

    process.setProgram(ffmpegPath);
    process.setArguments(args);

    emit messageGenerated("[ffmpeg] " + args.join(" "));

    process.start();
    state = State::Starting;
}

// =========================
// cancel
// =========================
void FfmpegRunner::cancel()
{
    if (state != State::Running &&
        state != State::Starting)
        return;

    state = State::Cancelling;
    process.terminate();

    // 3秒後に強制終了
    QTimer::singleShot(3000, this, [this]() {
        if (process.state() != QProcess::NotRunning) {
            process.kill();
        }
    });
}

// =========================
// started
// =========================
void FfmpegRunner::onStarted()
{
    state = State::Running;
}

// =========================
// stderr（ログ＋progress）
// =========================
void FfmpegRunner::onReadyReadStdErr()
{
    QByteArray data = process.readAllStandardError();
    if (data.isEmpty()) return;

    QString text = QString::fromUtf8(data);
    emit messageGenerated(text);

    // 簡易 progress
    QRegularExpression re("time=(\\d+):(\\d+):(\\d+\\.\\d+)");
    auto match = re.match(text);
    if (match.hasMatch()) {
        emit progressChanged(0); // TODO: duration 対応
    }
}

// =========================
// finished
// =========================
void FfmpegRunner::onFinished(int exitCode, QProcess::ExitStatus status)
{
    // --- キャンセル ---
    if (state == State::Cancelling) {
        tempFile.reset(); // 自動削除
        emit errorOccurred("キャンセルされました");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- 異常終了 ---
    if (status != QProcess::NormalExit || exitCode != 0) {
        tempFile.reset();
        emit errorOccurred("ffmpeg実行失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- 出力チェック ---
    if (!QFile::exists(tempPath) || QFileInfo(tempPath).size() == 0) {
        tempFile.reset();
        emit errorOccurred("出力ファイル不正");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- commit ---
    if (QFile::exists(finalPath)) {
        QFile::remove(finalPath);
    }

    if (!QFile::rename(tempPath, finalPath)) {
        tempFile.reset();
        emit errorOccurred("ファイル確定失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    tempFile.reset(); // 自動削除解除
    emit finished(true);
    state = State::Idle;
}