#include "programlistservice.h"
#include "programrepository.h"
#include "constants_programs.h"

QStringList ProgramListService::buildProgramList(int type)
{
    auto &repo = ProgramRepository::instance();

    QStringList allKeys = repo.name_map.keys();
    QStringList result;

    switch (type) {

    case English:
        for (const QString& name : allKeys) {
            if (Constants::matchEnglish(name))
                result << name;
        }
        break;

    case OtherLanguages:
        for (const QString& name : allKeys) {
            if (Constants::matchOtherLanguages(name))
                result << name;
        }
        break;

    case All:
        result = allKeys;
        break;
    }

    return result;
}
