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