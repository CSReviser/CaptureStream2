#include "programrepository.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ProgramRepository& ProgramRepository::instance()
{
    static ProgramRepository repo;
    return repo;
}

ProgramRepository::ProgramRepository()
{
}

void ProgramRepository::updatePrograms()
{
    QStringList kozaList = { "まいにちイタリア語", "まいにちスペイン語",
                             "まいにちドイツ語", "まいにちフランス語",
                             "まいにちロシア語" };

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    const QUrl url("https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/corners/new_arrivals");

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response_data = reply->readAll();
        reply->deleteLater();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["corners"].toArray();

        for (const QJsonValue& value : jsonArray) {
            QJsonObject objxx = value.toObject();
            QString title = objxx["title"].toString();
            QString corner_name = objxx["corner_name"].toString();
            QString series_site_id = objxx["series_site_id"].toString();
            QString corner_site = objxx["corner_site_id"].toString();
            QString thumbnail_url = objxx["thumbnail_url"].toString();

            QString program_name = Utility::getProgram_name3(title, corner_name);
            QString url_id = series_site_id + "_" + corner_site;

            id_map.insert(url_id, program_name);
            name_map.insert(program_name, url_id);
            thumbnail_map.insert(url_id, thumbnail_url);
        }

        fetchKozaSeries(kozaList);
    });
}

void ProgramRepository::fetchKozaSeries(const QStringList& kozaList)
{
    for (const QString& koza : kozaList) {

        if (!name_map.contains(koza)) continue;

        QString url = name_map[koza];
        int l = url.length() != 13 ? url.length() - 3 : 10;
        QString fullUrl = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
                          url.left(l) + "&corner_site_id=" + url.right(2);

        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkRequest request(fullUrl);
        QNetworkReply* reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {
            QByteArray response_data = reply->readAll();
            reply->deleteLater();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray jsonArray = jsonObject["episodes"].toArray();

            for (const QJsonValue& value : jsonArray) {
                QJsonObject objxx = value.toObject();
                QString file_title = objxx["program_title"].toString();

                QString temp1, temp2;
                if (file_title.contains("入門編")) {
                    temp1 = koza + "【入門編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("初級編")) {
                    temp1 = koza + "【初級編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("応用編")) {
                    temp1 = koza + "【応用編】";
                    temp2 = url.left(l) + "_y1";
                }
                if (file_title.contains("中級編")) {
                    temp1 = koza + "【中級編】";
                    temp2 = url.left(l) + "_y1";
                }

                if (!temp1.isEmpty() && !temp2.isEmpty()) {
                    name_map.insert(temp1, temp2);
                    id_map.insert(temp2, temp1);
                }
            }

            emit programListUpdated();
        });
    }
}
