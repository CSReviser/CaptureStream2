#include "ffmpegcommandbuilder.h"

QStringList FfmpegCommandBuilder::build(
    const RecordingRequest& req,
    const FfmpegCapabilities& /*caps*/)
{
    QStringList args;

    // =========================
    // 入力
    // =========================
    args << "-y";  // 上書き許可（開発中は必須）

    if (req.input.inputPath.isEmpty()) {
        return {}; // 異常
    }

    args << "-i" << req.input.inputPath;

    // =========================
    // コンテナチェック（最小）
    // =========================
    if (req.container != Container::MP3) {
        // 今はMP3のみ対応
        return {};
    }

    // =========================
    // 音声エンコード
    // =========================
    // copyCodecは未対応（最小構成）
    args << "-c:a" << "libmp3lame";

    if (!req.format.bitrate.isEmpty()) {
        args << "-b:a" << req.format.bitrate;
    }

    // チャンネル
    if (req.format.channels > 0) {
        args << "-ac" << QString::number(req.format.channels);
    }

    // サンプルレート（指定があれば）
    if (!req.format.sampleRate.isEmpty()) {
        args << "-ar" << req.format.sampleRate;
    }

    // =========================
    // メタデータ（最小）
    // =========================
    if (!req.meta.title.isEmpty()) {
        args << "-metadata" << "title=" + req.meta.title;
    }

    // =========================
    // 出力
    // =========================
    if (req.outputPath.isEmpty()) {
        return {}; // 異常
    }

    args << req.outputPath;

    return args;
}