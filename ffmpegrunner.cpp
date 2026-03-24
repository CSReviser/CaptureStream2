#include "ffmpegrunner.h"
#include <QDir>
#include <QRegularExpression>

// =========================
// ctor
// =========================
FfmpegRunner::FfmpegRunner(QObject* parent)
    : QObject(parent)
{
    connect(&process, &QProcess::started,
            this, &FfmpegRunner::onStarted);

    connect(&process, &QProcess::readyReadStandardError,
            this, &FfmpegRunner::onReadyReadStdErr);

    connect(&process,
            QOverload<int,QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &FfmpegRunner::onFinished);
}

// =========================
// tempPath生成
// =========================
QString FfmpegRunner::makeTempPath(const QString& finalPath)
{
    QFileInfo fi(finalPath);
    return fi.absolutePath() + "/" + fi.fileName() + ".tmp";
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
    tempPath  = makeTempPath(finalPath);
    
emit messageGenerated("finalPath: " + finalPath);
emit messageGenerated("tempPath: " + tempPath);

    QFile::remove(tempPath);

    FfmpegCapabilities caps =
        FfmpegCapabilities::detect(ffmpegPath);

    QStringList args =
        FfmpegCommandBuilder::build(req, caps, tempPath);

    if (args.isEmpty()) {
        emit errorOccurred("ffmpeg引数生成失敗");
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

    // 強制終了フォールバック
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
    stderrBuffer += process.readAllStandardError();

    QString text = QString::fromUtf8(stderrBuffer);

    emit messageGenerated(text);

    // progress（簡易）
    QRegularExpression re("time=(\\d+):(\\d+):(\\d+\\.\\d+)");
    auto match = re.match(text);

    if (match.hasMatch()) {
        // 本格的にはduration必要（後で対応）
        emit progressChanged(0);
    }
}

// =========================
// finished（最重要）
// =========================
void FfmpegRunner::onFinished(int exitCode,
                              QProcess::ExitStatus status)
{
    // --- キャンセル ---
    if (state == State::Cancelling) {
        QFile::remove(tempPath);
        emit errorOccurred("キャンセルされました");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- 異常終了 ---
    if (status != QProcess::NormalExit || exitCode != 0) {
        QFile::remove(tempPath);
        emit errorOccurred("ffmpeg実行失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- 出力チェック ---
    if (!QFile::exists(tempPath) ||
        QFileInfo(tempPath).size() == 0) {

        QFile::remove(tempPath);
        emit errorOccurred("出力ファイル不正");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- commit ---
    QFile::remove(finalPath);

    if (!QFile::rename(tempPath, finalPath)) {
        QFile::remove(tempPath);
        emit errorOccurred("ファイル確定失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    emit finished(true);
    state = State::Idle;
}

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
