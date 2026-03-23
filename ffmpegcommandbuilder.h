#pragma once

#include <QStringList>
#include "RecordingRequest.h"
#include "FfmpegCapabilities.h"

class FfmpegCommandBuilder
{
public:
    static QStringList build(const RecordingRequest& req,
                             const FfmpegCapabilities& caps);
};