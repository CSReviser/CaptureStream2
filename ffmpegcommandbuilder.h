#pragma once

#include <QStringList>
#include "recordingrequest.h"
#include "ffmpegcapabilities.h"

class FfmpegCommandBuilder
{
public:
    static QStringList build(const RecordingRequest& req,
                             const FfmpegCapabilities& caps);
};
