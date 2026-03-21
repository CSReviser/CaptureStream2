NetworkClient::NetworkClient(QObject* parent)
    : QObject(parent)
{
}

QNetworkReply* NetworkClient::get(const QUrl& url)
{
    QNetworkRequest request(url);
    return m_manager.get(request);
}

QByteArray NetworkClient::getSync(const QUrl& url,
                                  int timeoutMs,
                                  int maxRetry)
{
    QNetworkRequest request(url);

    int wait = timeoutMs;

    for (int i = 0; i < maxRetry; ++i) {

        QByteArray result = performRequestSync(request, wait);

        if (!result.isEmpty())
            return result;

        // バックオフ
        if (wait < 500) wait += 50;
        else if (wait < 5000) wait += 100;
    }

    return QByteArray();
}

QByteArray NetworkClient::performRequestSync(
    const QNetworkRequest& request,
    int timeoutMs)
{
    QEventLoop loop;
    QNetworkReply* reply = m_manager.get(request);

    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    timer.start(timeoutMs);
    loop.exec();

    QByteArray data;

    if (reply->isFinished() && reply->error() == QNetworkReply::NoError) {
        data = reply->readAll();
    }

    reply->deleteLater();
    return data;
}

QByteArray NetworkClient::getSync(
    const QUrl& url,
    int timeoutMs,
    int maxRetry)
{
    QNetworkRequest request(url);

    int wait = timeoutMs;

    for (int i = 0; i < maxRetry; ++i) {

        QEventLoop loop;
        QNetworkReply* reply = m_manager.get(request);

        QTimer timer;
        timer.setSingleShot(true);

        // reply単位で待つ ← 重要
        connect(reply, &QNetworkReply::finished,
                &loop, &QEventLoop::quit);

        connect(&timer, &QTimer::timeout,
                &loop, &QEventLoop::quit);

        timer.start(wait);
        loop.exec();

        QByteArray data;

        if (reply->isFinished() &&
            reply->error() == QNetworkReply::NoError) {

            data = reply->readAll();
        } else {
            reply->abort();
        }

        reply->deleteLater();

        if (!data.isEmpty())
            return data;

        // バックオフ
        if (wait < 500) wait += 50;
        else if (wait < 5000) wait += 100;
    }

    return QByteArray(); // ← error文字列廃止
}