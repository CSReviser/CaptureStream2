#include "networkclient.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QUrl>


NetworkClient::NetworkClient(QObject* parent)
    : QObject(parent)
{
}

QNetworkReply* NetworkClient::get(const QUrl& url)
{
    QNetworkRequest request(url);
    return m_manager.get(request);
}



QByteArray NetworkClient::getSync(
    const QUrl& url,
    int timeoutMs,
    int maxRetry)
{
    QNetworkRequest request(url);

    // NHK API 対策（User-Agent 必須）
    request.setHeader(QNetworkRequest::UserAgentHeader,
                      "NetworkClient/1.0");

    int wait = timeoutMs;

    for (int i = 0; i < maxRetry; ++i) {

        QEventLoop loop;
        QNetworkReply* reply = m_manager.get(request);

        QTimer timer;
        timer.setSingleShot(true);

        connect(reply, &QNetworkReply::finished,
                &loop, &QEventLoop::quit);

        connect(&timer, &QTimer::timeout,
                &loop, &QEventLoop::quit);

        timer.start(wait);
        loop.exec();

        QByteArray data;

        bool ok = reply->isFinished()
               && reply->error() == QNetworkReply::NoError;

        // HTTP ステータスコードも確認
        if (ok) {
            int status = reply->attribute(
                QNetworkRequest::HttpStatusCodeAttribute).toInt();

            if (status == 200) {
                data = reply->readAll();
            }
        } else {
            reply->abort();
        }

        reply->deleteLater();

        if (!data.isEmpty())
            return data;

        // バックオフ（指数的）
        wait = qMin(wait * 2, 5000);
    }

    return QByteArray();
}
