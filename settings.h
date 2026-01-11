#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QVector>
#include <QString>
#include <QByteArray>

class Settings : public QObject {
    Q_OBJECT
public:
    explicit Settings(QObject* parent = nullptr);

    // 全体ロード・セーブ
    void load();
    void save();

    // ウィンドウ別
    void loadMainWindow();
    void saveMainWindow();

    void loadMessageWindow();
    void saveMessageWindow();

    // --- Getter / Setter ---

    QString saveFolder() const { return m_saveFolder; }
    void setSaveFolder(const QString& v) { m_saveFolder = v; }

    QString ffmpegFolder() const { return m_ffmpegFolder; }
    void setFfmpegFolder(const QString& v) { m_ffmpegFolder = v; }

    QString audioExtension() const { return m_audioExtension; }
    void setAudioExtension(const QString& v) { m_audioExtension = v; }

    bool skip() const { return m_skip; }
    void setSkip(bool v) { m_skip = v; }

    QString optTitle(int i) const { return m_optTitle[i]; }
    void setOptTitle(int i, const QString& v) { m_optTitle[i] = v; }

    QString specTitle(int i) const { return m_specTitle[i]; }
    void setSpecTitle(int i, const QString& v) { m_specTitle[i] = v; }

    QByteArray mainGeometry() const { return m_mainGeometry; }
    void setMainGeometry(const QByteArray& g) { m_mainGeometry = g; }

    QByteArray messageGeometry() const { return m_messageGeometry; }
    void setMessageGeometry(const QByteArray& g) { m_messageGeometry = g; }

private:
    // --- 設定値 ---
    QString m_saveFolder;
    QString m_ffmpegFolder;
    QString m_audioExtension;

    bool m_skip = false;

    QVector<QString> m_optTitle;   // 例: 8個
    QVector<QString> m_specTitle;  // 例: 4個

    // --- ウィンドウ状態 ---
    QByteArray m_mainGeometry;
    QByteArray m_messageGeometry;
};

#endif // SETTINGS_H
