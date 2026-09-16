#ifndef FILENAMEUTILITY_H
#define FILENAMEUTILITY_H

#include <QString>

namespace FileNameUtility
{
    QString sanitizeFileName(const QString &fileName);

    bool fileExists(const QString &folderPath,
                    const QString &fileName);
}

#endif // FILENAMEUTILITY_H