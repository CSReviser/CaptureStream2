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

// core/nhkcalendar.cpp
#include "nhkcalendar.h"

QDate NhkCalendar::getNendoStart(int fiscalYear)
{
    QDate startDate(fiscalYear, 3, 29);

    for (int i = 0; i < 7; ++i) {
        QDate d = startDate.addDays(i);
        if (d.dayOfWeek() == Qt::Monday)
            return d;
    }
    return QDate(fiscalYear, 4, 1);
}

QDate NhkCalendar::getBroadcastDate(
    int fiscalYear,
    int month,
    int day)
{
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return QDate();

    QDate fiscalStart = getNendoStart(fiscalYear);
    QDate nextStart   = getNendoStart(fiscalYear + 1);

    int year = (month <= 3) ? fiscalYear + 1 : fiscalYear;

    QDate candidate(year, month, day);
    if (!candidate.isValid())
        return QDate();

    if (candidate < fiscalStart || candidate >= nextStart)
        return QDate();

    return candidate;
}

int NhkCalendar::getFiscalYear(const QDate& date)
{
    int year = date.year();
    QDate start = getNendoStart(year);

    return (date >= start) ? year : year - 1;
}

QString NhkCalendar::getFiscalYearString(const QDate& date)
{
    return QString::number(getFiscalYear(date));
}
