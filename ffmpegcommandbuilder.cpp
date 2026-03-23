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
    // MP3コンテナオプション
    // =========================
    if (req.useId3v2) {
        args << "-id3v2_version" << "3";
    }

    if (!req.writeXing) {
        args << "-write_xing" << "0";
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
    // メタデータ
    // =========================
    if (!req.meta.title.isEmpty()) {
        args << "-metadata" << "title=" + req.meta.title;
    }

    if (!req.meta.title.isEmpty()) {
        args << "-metadata" << "title=" + req.meta.title;
    }

    if (!req.meta.artist.isEmpty()) {
        args << "-metadata" << "artist=" + req.meta.artist;
    }

    if (!req.meta.album.isEmpty()) {
        args << "-metadata" << "album=" + req.meta.album;
    }

    if (!req.meta.date.isEmpty()) {
        args << "-metadata" << "date=" + req.meta.date;
    }

    if (!req.meta.genre.isEmpty()) {
        args << "-metadata" << "genre=" + req.meta.genre;
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
