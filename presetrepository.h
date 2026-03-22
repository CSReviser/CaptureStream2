#pragma once

#include <QString>
#include "recordingrequest.h"   // AudioFormat / Container を含む

class PresetRepository
{
public:
    static bool resolve(const QString& key, RecordingRequest& req);
};
