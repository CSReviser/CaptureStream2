#include "programformatter.h"
#include "programrepository.h"

QStringList ProgramFormatter::toLines(const QStringList& names)
{
    auto &repo = ProgramRepository::instance();

    QStringList lines;

 qsizetype maxWidth = 0;

for (const QString& name : names) {
    QString id = repo.name_map[name];
    maxWidth = std::max(maxWidth, id.length());
}

lines << QString("%1 : %2")
            .arg("番組ID", -int(maxWidth))
            .arg("番組名");

for (const QString& name : names) {
    QString id = repo.name_map[name];

    lines << QString("%1 : %2")
                 .arg(id, -int(maxWidth))
                 .arg(name);
}
    return lines;
}


