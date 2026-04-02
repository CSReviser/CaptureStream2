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
#include "constants.h"
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


static const QStringList& levelWordsBase()
{
    static QStringList list;
    if (list.isEmpty()) {
        for (int i = 0; i < Constants::LEVEL_WORDS_COUNT; ++i) {
            list << QString::fromUtf8(Constants::LEVEL_WORDS[i]);
        }
    }
    return list;
}

static const QStringList& levelWordsWithHen()
{
    static QStringList list;
    if (list.isEmpty()) {
        for (const QString &w : levelWordsBase()) {
            list << (w + "編");
        }
    }
    return list;
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

QString LegacyFormatEngine::extractLevelFromTitle(const QString &rawTitle, const QString &rawKouza)
{
    QString title = rawTitle;
    title.replace(QChar(0x3000), QChar(' '));
    title = title.simplified();

    QString kouza = rawKouza;
    kouza.replace(QChar(0x3000), QChar(' '));
    kouza = kouza.simplified();

    if (!title.startsWith(kouza))
        return QString();

    // ★ 二重登録対策：rawKouza に base word が含まれていたら抽出しない
    for (const QString &base : levelWordsBase()) {
        if (kouza.contains(base, Qt::CaseInsensitive)) {
            return QString();
        }
    }

    int pos = kouza.length();
    while (pos < title.length() && title[pos].isSpace())
        ++pos;

    // ここで levelWordsWithHen() を使う
    for (const QString &withHen : levelWordsWithHen()) {
        if (title.mid(pos).startsWith(withHen, Qt::CaseInsensitive)) {
            return withHen;
        }
    }

    return QString();
}

QString LegacyFormatEngine::buildId3TagAlbum(const QString &kouza, const QString &fileNameFormat)
{
    QString album = kouza;

    // %x が無いなら何もせず返す
    if (!fileNameFormat.contains("%x", Qt::CaseInsensitive))
        return album;

    // 「まいにち」を除去
    album.remove("まいにち", Qt::CaseInsensitive);

    //
    // レベル1 / レベル2 の処理（従来仕様）
    //
    static const QVector<LevelNumRule> numRules = {
        { "レベル1", "L1_", "【レベル1】" },
        { "レベル2", "L2_", "【レベル2】" },
        { "レベル１", "L1_", "_レベル１" },
        { "レベル２", "L2_", "_レベル２" },
        { "レベル１", "L1_", "レベル１" },
        { "レベル２", "L2_", "レベル２" }
    };

    for (const auto &r : numRules) {
        if (kouza.contains(r.key, Qt::CaseInsensitive)) {
            album = r.prefix + album.remove(r.remove, Qt::CaseInsensitive);
            break;
        }
    }

    //
    // 「入門／初級／中級／応用」などのレベル語（constants 連動）
    //
    const QStringList &bases   = levelWordsBase();      // 入門, 初級, 中級, 応用
    const QStringList &withHen = levelWordsWithHen();   // 入門編, 初級編, 中級編, 応用編

    for (int i = 0; i < bases.size(); ++i) {

        const QString &base = bases[i];     // 例: "初級"
        const QString &hen  = withHen[i];   // 例: "初級編"

        if (kouza.contains(base, Qt::CaseInsensitive)) {

            // 例: "初級_" + album.remove("【初級編】")
            album = base + "_" + album.remove("【" + hen + "】", Qt::CaseInsensitive);

            // 念のため "初級編" 単体も除去
            album.remove(hen, Qt::CaseInsensitive);

            break;
        }
    }

    return album;
}
