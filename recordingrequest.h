#pragma once

#include <QString>

// =========================
// Container種別
// =========================
enum class Container {
    AAC,
    M4A,
    MP3
};

// =========================
// 音声フォーマット
// =========================
struct AudioFormat {
    QString codec;        // "libmp3lame" など
    QString bitrate;      // "128k"
    int channels = 2;     // 1 or 2
    QString sampleRate;   // "44100" など
    bool copyCodec = false;
};

// =========================
// メタデータ
// =========================
struct Metadata {
    QString title;
    QString artist;
    QString album;
    QString date;
    QString genre;
};

// =========================
// 入力オプション
// =========================
struct InputOptions {
    QString inputPath;        // URL or file

    QString userAgent;
    QString cookie;

    bool httpSeekable = false;
};

struct ThumbnailOptions {
    QString imagePath;     // カバー画像
    bool enabled = false;  // 有効/無効
};

// =========================
// RecordingRequest（本体）
// =========================
struct RecordingRequest {
    InputOptions input;
    AudioFormat format;
    ThumbnailOptions thumbnail;
    Metadata meta;

    Container container = Container::MP3;

    // コンテナ依存オプション
    bool writeXing = false;   // mp3用
    bool useId3v2 = false;    // mp3用

    QString outputPath;
    QStringList extraOutputOptions;
};
