class NhkCalendar {
public:
    static QDate getNendoStart(int fiscalYear);

    static QDate getBroadcastDate(
        int fiscalYear,
        int month,
        int day);

    static int getFiscalYear(const QDate& date);
};