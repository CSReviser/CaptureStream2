#include "thumbnailoptionsbuilder.h"

QStringList ThumbnailOptionsBuilder::buildInput(const RecordingRequest& req)
{
    QStringList args;

    if (!req.thumbnail.enabled)
        return args;

    if (req.thumbnail.imagePath.isEmpty())
        return args;

    // 画像を追加入力として渡す
    args << "-i" << req.thumbnail.imagePath;

    return args;
}

QStringList ThumbnailOptionsBuilder::buildOutput(const RecordingRequest& req)
{
    QStringList args;

    if (!req.thumbnail.enabled)
        return args;

    if (req.thumbnail.imagePath.isEmpty())
        return args;

    // =========================
    // MP3
    // =========================
    if (req.container == Container::MP3) {
        /*
         * -map 0:a  -> 音声
         * -map 1:v  -> 画像
         */
        args << "-map" << "0:a";
        args << "-map" << "1:v";

        // 音声は既存設定に従うので触らない
        args << "-map_metadata" << "0";

        args << "-c:a" << "copy";

        // 画像はjpegとして扱う
        args << "-c:v" << "mjpeg";

        // attached picture
        args << "-disposition:v" << "attached_pic";

        return args;
    }

    // =========================
    // M4A
    // =========================
    if (req.container == Container::M4A) {
        /*
         * AAC + cover art
         */
        args << "-map" << "0:a";
        args << "-map" << "1:v";

        args << "-map_metadata" << "0";

        args << "-c:a" << "copy";

        // copy前提（encodeでも問題なし）
        args << "-c:v" << "mjpeg";

        // カバー指定
        args << "-disposition:v" << "attached_pic";

        return args;
    }

    return args;
}