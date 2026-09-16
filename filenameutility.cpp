/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
	NHK radio language courses.
	CaptureStream2 is a modified version of CaptureStream, originally 
	developed by jakago.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-2.0.html>.
*/
#include "filenameutility.h"

#include <QDir>

namespace
{
    QChar fullWidthReplacement(const QChar c)
    {
        switch (c.unicode()) {
        case '"':  return QChar(0xFF02); // ＂
        case '*':  return QChar(0xFF0A); // ＊
        case '/':  return QChar(0xFF0F); // ／
        case ':':  return QChar(0xFF1A); // ：
        case '<':  return QChar(0xFF1C); // ＜
        case '>':  return QChar(0xFF1E); // ＞
        case '?':  return QChar(0xFF1F); // ？
        case '\\': return QChar(0xFF3C); // ＼
        case '|':  return QChar(0xFF5C); // ｜
        default:   return QChar();
        }
    }

    bool isReservedDeviceName(const QString &name)
    {
        const QString upperName = name.toUpper();

        if (upperName == QStringLiteral("CON") ||
            upperName == QStringLiteral("PRN") ||
            upperName == QStringLiteral("AUX") ||
            upperName == QStringLiteral("NUL")) {
            return true;
        }

        if (upperName.size() == 4) {
            const QString prefix = upperName.left(3);
            const QChar number = upperName.at(3);

            if ((prefix == QStringLiteral("COM") ||
                 prefix == QStringLiteral("LPT")) &&
                number >= QLatin1Char('1') &&
                number <= QLatin1Char('9')) {
                return true;
            }
        }

        return false;
    }
}

namespace FileNameUtility
{

QString sanitizeFileName(const QString &fileName)
{
    // アプリケーションのファイル名はNFCを正準形とする。
    QString result =
        fileName.normalized(QString::NormalizationForm_C);

    QString sanitized;
    sanitized.reserve(result.size());

    for (const QChar c : result) {
        // U+0000 ～ U+001F
        if (c.unicode() <= 0x1F) {
            continue;
        }

        const QChar replacement = fullWidthReplacement(c);

        if (!replacement.isNull()) {
            sanitized.append(replacement);
        } else {
            sanitized.append(c);
        }
    }

    result = sanitized;

    // Windowsでは末尾のASCIIスペースと '.' は使用できない。
    while (!result.isEmpty() &&
           (result.endsWith(QLatin1Char(' ')) ||
            result.endsWith(QLatin1Char('.')))) {
        result.chop(1);
    }

    if (result.isEmpty()) {
        return QStringLiteral("_");
    }

    if (isReservedDeviceName(result)) {
        result.prepend(QLatin1Char('_'));
    }

    return result;
}

bool fileExists(const QString &folderPath,
                const QString &fileName)
{
    const QDir dir(folderPath);

    if (!dir.exists()) {
        return false;
    }

    // 比較対象はアプリケーションの正準形であるNFCに統一する。
    const QString normalizedFileName =
        fileName.normalized(QString::NormalizationForm_C);

    const QStringList entries =
        dir.entryList(QDir::Files | QDir::NoDotAndDotDot);

    for (const QString &entry : entries) {
        if (entry.normalized(QString::NormalizationForm_C) ==
            normalizedFileName) {
            return true;
        }
    }

    return false;
}

} // namespace FileNameUtility
