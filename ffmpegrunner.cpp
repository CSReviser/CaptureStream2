void FfmpegRunner::start(const RecordingRequest& req,
                         const QString& ffmpegPath)
{
    if (state != State::Idle) {
        emit errorOccurred("既に実行中です");
        return;
    }

    finalPath = req.outputPath;

    QFileInfo fi(finalPath);
    tempPath = fi.absolutePath() + "/" + fi.fileName() + ".tmp";

    QFile::remove(tempPath);

    QStringList args =
        FfmpegCommandBuilder::build(req, tempPath);

    if (args.isEmpty()) {
        emit errorOccurred("ffmpeg引数生成失敗");
        return;
    }

    process.setProgram(ffmpegPath);
    process.setArguments(args);

    process.start();

    state = State::Starting;
}

void FfmpegRunner::cancel()
{
    if (state != State::Running &&
        state != State::Starting)
        return;

    state = State::Cancelling;

    process.terminate();

    // 念のため強制終了も予約
    QTimer::singleShot(3000, this, [this]() {
        if (process.state() != QProcess::NotRunning) {
            process.kill();
        }
    });
}

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

    // --- プロセス異常終了 ---
    if (status != QProcess::NormalExit || exitCode != 0) {
        QFile::remove(tempPath);
        emit errorOccurred("ffmpeg実行失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    // --- ファイル検証 ---
    if (!QFile::exists(tempPath) ||
        QFileInfo(tempPath).size() == 0) {

        QFile::remove(tempPath);
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
        QFile::remove(tempPath);
        emit errorOccurred("ファイル確定失敗");
        emit finished(false);
        state = State::Idle;
        return;
    }

    emit finished(true);
    state = State::Idle;
}

void FfmpegRunner::onReadyReadStdErr()
{
    stderrBuffer += process.readAllStandardError();

    QString text = QString::fromUtf8(stderrBuffer);

    // 例: time=00:01:23.45
    QRegularExpression re("time=(\\d+):(\\d+):(\\d+\\.\\d+)");
    auto match = re.match(text);

    if (match.hasMatch()) {
        // progress算出（duration必要）
        emit progressChanged(...);
    }

    emit messageGenerated(text);
}
