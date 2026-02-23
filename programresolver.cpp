#include "programresolver.h"
#include "programrepository.h"

QString ProgramResolver::normalize(const QString& s)
{
    QString t = s.trimmed();

    // 全角→半角対策など将来ここに追加可能
    return t;
}

ResolveResult ProgramResolver::resolve(const QString& input)
{
    ResolveResult r;
    if (input.isEmpty())
        return r;

    auto& repo = ProgramRepository::instance();
    QString key = normalize(input);

    // ---- 1 ID完全一致 ----
    if (repo.id_map.contains(key)) {
        r.status = ResolveResult::Unique;
        r.id = key;
        return r;
    }

    // ---- 2 タイトル完全一致 ----
    for (auto it = repo.name_map.cbegin(); it != repo.name_map.cend(); ++it) {
        if (QString::compare(it.key(), key, Qt::CaseInsensitive) == 0) {
            r.status = ResolveResult::Unique;
            r.id = it.value();
            return r;
        }
    }

    // ---- 3 前方一致 ----
    QStringList prefixMatches;
    for (auto it = repo.name_map.cbegin(); it != repo.name_map.cend(); ++it) {
        if (it.key().startsWith(key, Qt::CaseInsensitive))
            prefixMatches << it.value();
    }

    if (prefixMatches.size() == 1) {
        r.status = ResolveResult::Unique;
        r.id = prefixMatches.first();
        return r;
    }
    if (prefixMatches.size() > 1) {
        r.status = ResolveResult::Ambiguous;
        r.candidates = prefixMatches;
        return r;
    }

    // ---- 4 部分一致 ----
    QStringList partialMatches;
    for (auto it = repo.name_map.cbegin(); it != repo.name_map.cend(); ++it) {
        if (it.key().contains(key, Qt::CaseInsensitive))
            partialMatches << it.value();
    }

    if (partialMatches.size() == 1) {
        r.status = ResolveResult::Unique;
        r.id = partialMatches.first();
        return r;
    }
    if (partialMatches.size() > 1) {
        r.status = ResolveResult::Ambiguous;
        r.candidates = partialMatches;
        return r;
    }

    return r;
}

QString ProgramResolver::resolveUnique(const QString& input)
{
    auto r = resolve(input);
    if (r.status == ResolveResult::Unique)
        return r.id;
    return {};
}
