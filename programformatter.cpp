#include "programformatter.h"
#include "programrepository.h"

QStringList ProgramFormatter::toLines(const QStringList& ids)
{
    auto &repo = ProgramRepository::instance();

    QStringList lines;

    int maxWidth = 0;
    for (const QString& id : ids) {
        maxWidth = std::max(maxWidth, repo.name_map[id].length());
    }

    lines << QString("%1 : %2")
                .arg("番組名", -maxWidth)
                .arg("番組ID");

    for (const QString& id : ids) {
        QString name = repo.name_map[id];

        lines << QString("%1 : %2")
                     .arg(name, -maxWidth)
                     .arg(id);
    }

    return lines;
}