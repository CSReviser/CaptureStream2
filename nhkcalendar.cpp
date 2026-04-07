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

#include "nhkcalendar.h"
#include <QRegularExpression>

// ========================================
// XML → NHKBroadcastDate
// ========================================
NHKBroadcastDate NHKCalendar::fromXml(int fiscalYear, const QString& hdate)
{
    int m = 0, d = 0;

    if (!parseMonthDay(hdate, m, d)) {
        return {};
    }

    QDate date = getBroadcastDate(fiscalYear, m, d);
    if (!date.isValid()) {
        return {};
    }

    return build(date);
}

// ========================================
// JSON → NHKBroadcastDate
// aa_contents_id 使用
// ========================================
NHKBroadcastDate NHKCalendar::fromJsonContentId(const QString& contentId)
{
    QDate date = extractDateFromContentId(contentId);

    if (!date.isValid()) {
        return {};
    }

    return build(date);
}

// ========================================
// 年度 + 月日 → 暦日
// ========================================
QDate NHKCalendar::getBroadcastDate(int fiscalYear, int month, int day)
{
    QDate fiscalStart = getFiscalStart(fiscalYear);

    QDate candidate(fiscalYear, month, day);

    if (candidate < fiscalStart) {
        candidate = QDate(fiscalYear + 1, month, day);
    }

    return candidate;
}

// ========================================
// 年度開始日（3/29〜4/4の月曜）
// ========================================
QDate NHKCalendar::getFiscalStart(int fiscalYear)
{
    QDate base(fiscalYear, 3, 29);

    for (int i = 0; i < 7; ++i) {
        QDate d = base.addDays(i);
        if (d.dayOfWeek() == Qt::Monday) {
            return d;
        }
    }

    return {};
}

// ========================================
// QDate → 年度
// ========================================
int NHKCalendar::getFiscalYear(const QDate& date)
{
    int y = date.year();
    QDate start = getFiscalStart(y);

    if (date >= start) {
        return y;
    } else {
        return y - 1;
    }
}

// ========================================
// "3月26日放送分" → month/day
// ========================================
bool NHKCalendar::parseMonthDay(const QString& str, int& month, int& day)
{
    QRegularExpression re("(\\d{1,2})月(\\d{1,2})日");
    auto match = re.match(str);

    if (!match.hasMatch()) {
        return false;
    }

    month = match.captured(1).toInt();
    day   = match.captured(2).toInt();

    return true;
}

// ========================================
// contentId から YYYY-MM-DD 抽出
// ========================================
QDate NHKCalendar::extractDateFromContentId(const QString& contentId)
{
    QRegularExpression re(R"((\d{4}-\d{2}-\d{2}))");
    auto match = re.match(contentId);

    if (!match.hasMatch()) {
        return {};
    }

    QString dateStr = match.captured(1);
    return QDate::fromString(dateStr, "yyyy-MM-dd");
}

// ========================================
// QDate → 完全構造体生成（最重要）
// ========================================
NHKBroadcastDate NHKCalendar::build(const QDate& date)
{
    NHKBroadcastDate r;

    r.date = date;

    int y = date.year();
    int m = date.month();
    int d = date.day();

    // ===== 年 =====
    r.year4 = QString::number(y);
    r.year2 = QString("%1").arg(y % 100, 2, 10, QChar('0'));

    // ===== 月 =====
    r.month  = QString::number(m);
    r.month2 = QString("%1").arg(m, 2, 10, QChar('0'));

    // ===== 日 =====
    r.day  = QString::number(d);
    r.day2 = QString("%1").arg(d, 2, 10, QChar('0'));

    // ===== 表示 =====
    r.display = QString("%1月%2日放送分")
        .arg(r.month2)
        .arg(r.day2);

    // ===== 年度 =====
    r.fiscalYear = QString::number(getFiscalYear(date));

    return r;
}

