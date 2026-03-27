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

// core/legacyformatengine.cpp

#include "legacyformatengine.h"
#include <QRegularExpression>
#include <QDate>

// =========================
// 内部ユーティリティ
// =========================

static bool illegal(char c)
{
    switch (c) {
    case '/':
    case '\\':
    case ':':
    case '*':
    case '?':
    case '"':
    case '<':
    case '>':
    case '|':
    case '#':
    case '{':
    case '}':
    case '%':
    case '&':
    case '~':
        return true;
    default:
        return false;
    }
}

// =========================
// one2two（必要なら外部公開可）
// =========================

QStringList one2two(const QStringList &hdateList)
{
    QStringList result;
    QRegularExpression rx("(\\d+)(?:\\D+)(\\d+)");

    for (const QString &hdate : hdateList) {
        QRegularExpressionMatch match = rx.match(hdate);
        if (match.hasMatch()) {
            int month = match.captured(1).toInt();
            int day = match.captured(2).toInt();

            QString formatted =
                QString::number(month + 100).right(2)
                + QString::fromUtf8("月")
                + QString::number(day + 100).right(2)
                + QString::fromUtf8("日放送分");

            result << formatted;
        } else {
            result << hdate;
        }
    }

    return result;
}

// =========================
// thisweekfile（必要なら外部公開可）
// =========================

QStringList thisweekfile(QStringList fileList2, QStringList codeList)
{
    QStringList result;

    for (int i = 0; i < fileList2.count(); i++) {

        QString filex = fileList2[i];
        int filexxx = codeList[i].toInt() + fileList2.count();

        filex.replace(
            codeList[i].right(3),
            QString::number(filexxx).right(3));

        filex.remove("-re01");

        result << filex;
    }

    return result;
}

// =========================
// メイン
// =========================

QString LegacyFormatEngine::formatName(const LegacyFormatInput& in)
{
    QString format = in.format;
    QString kouza  = in.kouza;
    QString hdate  = in.hdate;
    QString file   = in.file;
    QString nendo  = in.nendo;
    QString dupnmb = in.dupnmb;

    int month = hdate.left(2).toInt();
    int day   = hdate.mid(2, 2).toInt();
    int year  = nendo.right(4).toInt();

    // flv除去
    if (file.endsWith(".flv"))
        file.chop(4);

    QString dupnmb1 = dupnmb;

    if (format.contains("%i", Qt::CaseInsensitive))
        dupnmb1 = "";

    if (format.contains("%_%i", Qt::CaseInsensitive)) {
        dupnmb.replace("-", "_");
        format.remove("%_");
    }

    QString result;
    bool percent = false;

    for (int i = 0; i < format.length(); i++) {

        QChar qchar = format[i];

        if (percent) {
            percent = false;

            char ascii = qchar.toLatin1();

            if (in.checkIllegal && illegal(ascii))
                continue;

            switch (ascii) {

            case 'k': result += kouza; break;

            case 'h':
                result += hdate.left(4)
                       + QString::fromUtf8("放送分")
                       + dupnmb1;
                break;

            case 'f': result += file; break;

            case 'Y': result += QString::number(year); break;
            case 'y': result += QString::number(year).right(2); break;

            case 'N': result += nendo + QString::fromUtf8("年度"); break;
            case 'n': result += nendo.right(2) + QString::fromUtf8("年度"); break;

            case 'M': result += QString::number(month + 100).right(2); break;
            case 'm': result += QString::number(month); break;

            case 'D':
                result += QString::number(day + 100).right(2) + dupnmb1;
                break;

            case 'd':
                result += QString::number(day) + dupnmb1;
                break;

            case 'i':
                result += dupnmb;
                break;

            case 'x':
            case 's':
                break;

            default:
                result += qchar;
                break;
            }

        } else {

            if (qchar == QChar('%')) {
                percent = true;
            }
            else if (in.checkIllegal && illegal(qchar.toLatin1())) {
                continue;
            }
            else {
                result += qchar;
            }
        }
    }

    return result;
}
