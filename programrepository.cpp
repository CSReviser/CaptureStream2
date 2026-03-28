/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2026 CSReviser Team

	This file is part of CaptureStream2, a recorder that supports HLS for 
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
#include "programrepository.h"
#include "utility.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
//#include <QNetworkAccessManager>
#include <QNetworkReply>

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
    m_pendingRequests = 0; // new_arrivals の 1 リクエスト
    m_pendingRequests++;
    QStringList kozaList = { "まいにちイタリア語", "まいにちスペイン語",
                             "まいにちドイツ語", "まいにちフランス語",
                             "まいにちロシア語" };

 //   QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    const QUrl url("https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/corners/new_arrivals");

    QNetworkReply* reply = m_client.get(url);

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

            QString program_name = formatProgramName(title, corner_name);
            QString url_id = series_site_id + "_" + corner_site;

            id_map.insert(url_id, program_name);
            name_map.insert(program_name, url_id);
            thumbnail_map.insert(url_id, thumbnail_url);
        }

        fetchKozaSeries(kozaList);
        checkIfAllRequestsFinished();
    });

/*
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

            QString program_name = formatProgramName(title, corner_name);
            QString url_id = series_site_id + "_" + corner_site;

            id_map.insert(url_id, program_name);
            name_map.insert(program_name, url_id);
            thumbnail_map.insert(url_id, thumbnail_url);
        }

        fetchKozaSeries(kozaList);
        checkIfAllRequestsFinished();
*/
}

void ProgramRepository::fetchKozaSeries(const QStringList& kozaList)
{
    for (const QString& koza : kozaList) {

        if (!name_map.contains(koza)) continue;

        m_pendingRequests++; // 追加の HTTP リクエスト
        QString url = name_map[koza];
        int l = url.length() != 13 ? url.length() - 3 : 10;
        QString fullUrl = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
                          url.left(l) + "&corner_site_id=" + url.right(2);

//        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
 //       QNetworkRequest request(fullUrl);
//        QNetworkReply* reply = manager->get(request);
        QNetworkReply* reply = m_client.get(QUrl(fullUrl));

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

 //           emit programListUpdated();
            checkIfAllRequestsFinished();
        });
    }
}

void ProgramRepository::start()
{
    if (m_started)
        return;

    m_started = true;
    updatePrograms(); // ← 今まで呼んでいたやつ
}

bool ProgramRepository::waitUntilReady()
{
    if (m_ready)
        return true;

    QEventLoop loop;
    QObject::connect(this, &ProgramRepository::programListUpdated,
                     &loop, &QEventLoop::quit);
    loop.exec();
    return m_ready;
}

bool ProgramRepository::isReady() const
{
    return m_ready;
}

void ProgramRepository::checkIfAllRequestsFinished()
{
    m_pendingRequests--;

    if (m_pendingRequests == 0) {
        m_ready = true;
        emit programListUpdated();
    }
}

QString ProgramRepository::getProgramNameById(const QString& url)
{
    // キャッシュ優先
    if (id_map.contains(url))
        return id_map.value(url);

    // 未取得なら取得
    QString json = fetchProgramJson(url);
    if (json.isEmpty())
        return QString();

    auto [title, corner] = parseProgramJson(json);
    QString name = formatProgramName(title, corner);

    id_map.insert(url, name);
    name_map.insert(name, url);

    return name;
}

QString ProgramRepository::fetchProgramJson(const QString& url)
{
    int l = (url.length() != 13) ? url.length() - 3 : 10;

    QString api =
        "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
        url.left(l) + "&corner_site_id=" + url.right(2);

    int timer = 100;

    for (int i = 0; i < 20; ++i) {

        QByteArray res = m_client.getSync(QUrl(api), timer, 1);

        if (!res.isEmpty())
            return QString::fromUtf8(res);

        if (timer < 500) timer += 50;
        else if (timer < 5000) timer += 100;
    }

    return QString();
}
/*
QString ProgramRepository::fetchProgramJson(const QString& url)
{
    int l = (url.length() != 13) ? url.length() - 3 : 10;

    QString api =
        "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
        url.left(l) + "&corner_site_id=" + url.right(2);

    int timer = 100;
    for (int i = 0; i < 20; ++i) {
        QString res = Utility::getJsonFile(api, timer);
        if (res != "error")
            return res;

        if (timer < 500) timer += 50;
        else if (timer < 5000) timer += 100;
    }
    return QString();
}
*/
std::tuple<QString, QString>
ProgramRepository::parseProgramJson(const QString& str)
{
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject obj = doc.object();

    QString title = obj["title"].toString().replace("　", " ");
    QString corner = obj["corner_name"]
                        .toString()
                        .remove("を聴く")
                        .replace("　", " ");

    return { title, corner };
}

QString ProgramRepository::formatProgramName(
    const QString& title,
    const QString& corner_name)
{
    QString attribute = buildBaseProgramName(title, corner_name);
    normalizeWidth(attribute);
//   attribute = normalizeProgramName(attribute);
    return attribute;
}

void ProgramRepository::normalizeWidth(QString& s)
{
    for (ushort i = 0xFF1A; i < 0xFF5F; ++i)
        s.replace(QChar(i), QChar(i - 0xFEE0));

    for (ushort i = 0xFF10; i < 0xFF1A; ++i)
        s.replace(QChar(i - 0xFEE0), QChar(i));
}

QString ProgramRepository::buildBaseProgramName(
    const QString& title,
    const QString& corner_name)
{
    QString attribute = title;
    attribute.replace("　", " ");

    if (!corner_name.isEmpty()) {
        if (corner_name.contains("曜日放送", Qt::CaseInsensitive) ||
            corner_name.contains("曜放送", Qt::CaseInsensitive) ||
            corner_name.contains("特集", Qt::CaseInsensitive)) {
            attribute = title + "-" + corner_name;
        } else {
            attribute = corner_name;
        }
    }

    return attribute;
}

QString ProgramRepository::normalizeProgramName(QString attribute)
{
    normalizeWidth(attribute);

    attribute.remove("【らじる文庫】");
    attribute.remove("より");
    attribute.remove("カルチャーラジオ ");
    attribute.remove("【恋する朗読】");
    attribute.remove("【ラジオことはじめ】");
    attribute.remove("【生朗読！】");
    attribute.remove("NHK高校講座");
    attribute.remove("まいにち朗読");

    attribute.replace(" 初級編", "【初級編】");
    attribute.replace(" 入門編", "【入門編】");
    attribute.replace(" 中級編", "【中級編】");
    attribute.replace(" 応用編", "【応用編】");

    return attribute;
}


