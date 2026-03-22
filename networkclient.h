class NetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit NetworkClient(QObject* parent = nullptr);

    // 非同期
    QNetworkReply* get(const QUrl& url);

    // 同期（CLI用）
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