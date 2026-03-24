class FfmpegRunner : public QObject
{
    Q_OBJECT

public:
    explicit FfmpegRunner(QObject* parent = nullptr);

    void start(const RecordingRequest& req,
               const QString& ffmpegPath);

    void cancel();

signals:
    void messageGenerated(const QString &msg);
    void progressChanged(int percent);
    void errorOccurred(const QString &msg);
    void finished(bool success);

private slots:
    void onStarted();
    void onReadyReadStdErr();
    void onFinished(int exitCode,
                    QProcess::ExitStatus status);

private:
    QString makeTempPath(const QString& finalPath);
    bool commitFile();

private:
    QProcess process;

    QString tempPath;
    QString finalPath;

    State state = State::Idle;

    QByteArray stderrBuffer; // progress解析用
};