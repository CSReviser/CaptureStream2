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

#pragma once

#include <QDate>
#include <QString>

// ========================================
// 正規化済み放送日データ（DTO）
// ========================================
struct NHKBroadcastDate
{
    // ===== 基準 =====
    QDate date;  // 内部用（唯一の真実）

    // ===== 年 =====
    QString year4;   // "2026"
    QString year2;   // "26"

    // ===== 月 =====
    QString month;   // "3"
    QString month2;  // "03"

    // ===== 日 =====
    QString day;     // "26"
    QString day2;    // "26"

    // ===== 表示 =====
    QString display; // "03月26日放送分"

    // ===== 年度 =====
    QString fiscalYear; // "2025"
};

// ========================================
// NHKカレンダー変換ユーティリティ
// ========================================
class NHKCalendar
{
public:
    // ===== エントリポイント =====

    // XML: 年度 + "3月26日放送分"
    static NHKBroadcastDate fromXml(int fiscalYear, const QString& hdate);

    // JSON: aa_contents_id から生成
    static NHKBroadcastDate fromJsonContentId(const QString& contentId);

    // ===== コアロジック =====

    static QDate getBroadcastDate(int fiscalYear, int month, int day);
    static int getFiscalYear(const QDate& date);
    static QDate getFiscalStart(int fiscalYear);

private:
    // ===== 内部 =====

    static bool parseMonthDay(const QString& str, int& month, int& day);
    static QDate extractDateFromContentId(const QString& contentId);

    static NHKBroadcastDate build(const QDate& date);
};

