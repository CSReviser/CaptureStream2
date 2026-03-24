#include "nhkcalendar.h"
#include <QDate>

QDate NhkCalendar::getNendoStart(int fiscalYear)
{
    QDate startDate(fiscalYear, 3, 29);

    for (int i = 0; i < 7; ++i) {
        QDate d = startDate.addDays(i);
        if (d.dayOfWeek() == Qt::Monday)
            return d;
    }
    return QDate();
}

QDate NhkCalendar::getBroadcastDate(
    int fiscalYear,
    int month,
    int day)
{
    QDate fiscalStart = getNendoStart(fiscalYear);

    QDate candidate(fiscalYear, month, day);

    if (!candidate.isValid())
        return QDate();

    if (candidate < fiscalStart) {
        candidate = QDate(fiscalYear + 1, month, day);
    }

    return candidate;
}

int NhkCalendar::getFiscalYear(const QDate& date)
{
    int year = date.year();

    QDate startCurrent = getNendoStart(year);

    if (date >= startCurrent)
        return year;

    return year - 1;
}

