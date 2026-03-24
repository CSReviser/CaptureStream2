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

    if (req.container == Container::MP3 ||
        req.container == Container::M4A) {

        args << "-map" << "0:a";
        args << "-map" << "1:v";

        args << "-map_metadata" << "0";

        // 音声はBuilder側に任せる

        args << "-c:v" << "mjpeg";
        args << "-disposition:v" << "attached_pic";
    }

    return args;
}
