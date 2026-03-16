#include "programlistservice.h"
#include "programrepository.h"
#include "constants_programs.h"

namespace {

bool match(const QString& name,
           const char* keywords[],
           int count)
{
    QString exclude = QString::fromUtf8(Constants::PROGRAM_EXCLUDE_TAG);

    if (name.contains(exclude))
        return false;

    for (int i = 0; i < count; ++i) {
        QString key = QString::fromUtf8(keywords[i]);

        if (name.contains(key))
            return true;
    }

    return false;
}

bool matchEnglish(const QString& name)
{
    return match(name,
                 Constants::PROGRAM_KEYWORDS_ENGLISH,
                 Constants::PROGRAM_KEYWORDS_ENGLISH_COUNT);
}

bool matchOtherLanguages(const QString& name)
{
    return match(name,
                 Constants::PROGRAM_KEYWORDS_OTHER,
                 Constants::PROGRAM_KEYWORDS_OTHER_COUNT);
}

}

QStringList ProgramListService::buildProgramList(int type)
{
    auto &repo = ProgramRepository::instance();

    QStringList allKeys = repo.name_map.keys();
    QStringList result;

    switch (type) {

    case English:
        for (const QString& name : allKeys) {
            if (matchEnglish(name))
                result << name;
        }
        break;

    case OtherLanguages:
        for (const QString& name : allKeys) {
            if (matchOtherLanguages(name))
                result << name;
        }
        break;

    case All:
        result = allKeys;
        break;
    }

    return result;
}

