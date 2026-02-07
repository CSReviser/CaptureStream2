#pragma once
#include <QString>

inline QString qs(const char* s)
{
    return QString::fromUtf8(s ? s : "");
}