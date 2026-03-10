#pragma once
#include <QStringList>

class ProgramListService
{
public:
    enum ListType {
        English = 1,
        OtherLanguages = 2,
        All = 3
    };

    static QStringList buildProgramList(int type);
};