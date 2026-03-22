#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>

class NetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit NetworkClient(QObject* parent = nullptr);

    QNetworkReply* get(const QUrl& url);

    QByteArray getSync(const QUrl& url,
                       int timeoutMs = 1000,
                       int maxRetry = 3);

signals:
    void requestFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_manager;

    QByteArray performRequestSync(const QNetworkRequest& request,
                                  int timeoutMs);
};