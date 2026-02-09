#ifndef PROGRAMREPOSITORY_H
#define PROGRAMREPOSITORY_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ProgramRepository : public QObject
{
    Q_OBJECT

public:
    static ProgramRepository& instance();

    // 取得した番組一覧
    QMap<QString, QString> id_map;        // url_id → program_name
    QMap<QString, QString> name_map;      // program_name → url_id
    QMap<QString, QString> thumbnail_map; // url_id → thumbnail_url

    // 起動後にネットから番組一覧を取得
    void updatePrograms();

signals:
    void programListUpdated();  // GUI に通知したい場合

private:
    ProgramRepository();
    Q_DISABLE_COPY(ProgramRepository)

    void fetchKozaSeries(const QStringList& kozaList);
};

#endif // PROGRAMREPOSITORY_H
