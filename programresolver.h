#pragma once
#include <QString>
#include <QStringList>

struct ResolveResult
{
    enum Status {
        NotFound,
        Unique,
        Ambiguous
    };

    Status status = NotFound;
    QString id;              // Unique のときのみ有効
    QStringList candidates;  // Ambiguous のときのみ
};

class ProgramResolver
{
public:
    static ResolveResult resolve(const QString& input);
    static QString resolveUnique(const QString& input);

private:
    static QString normalize(const QString& s);
};

