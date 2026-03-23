#pragma once

#include <QStringList>
#include "recordingrequest.h"

class ThumbnailOptionsBuilder
{
public:
    static QStringList buildInput(const RecordingRequest& req);
    static QStringList buildOutput(const RecordingRequest& req);
};