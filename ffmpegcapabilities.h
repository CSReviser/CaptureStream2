#pragma once

#include <QString>

struct FfmpegCapabilities {
    bool httpSeekableSupported = false;

    static FfmpegCapabilities detect(const QString& ffmpegPath);
};