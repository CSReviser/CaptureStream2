#pragma once
#include <QString>
#include <QStringList>
#include <QVector>
#include <QByteArray>

class Settings
{
public:
    Settings();

    // 永続設定の読み書き
    void load();
    void save();

    // ウィンドウ状態
    void loadMainWindow();
    void saveMainWindow(const QByteArray &geometry);

    void loadMessageWindow();
    void saveMessageWindow(const QByteArray &geometry);

    // ===== 基本設定 =====
    QString audioExtension;
    QString ffmpegFolder;
    QString saveFolder;

    bool skip = false;
    bool thumbnail = false;
    bool tagSpace = false;
    bool nameSpace = false;
    bool kozaSeparation = false;
    bool multiGui = false;
    bool thisWeek = false;
    bool timetrial = false;
    bool detailedMessage = false;

    // ===== basic / business / enjoy / gendai / kaiwa =====
    bool basic0 = false;
    bool basic1 = false;
    bool basic2 = false;
    bool business1 = false;
    bool enjoy = false;
    bool gendai = false;
    bool kaiwa = false;

    // ===== optional（8 個）=====
    QStringList optionalIds;        // optional1〜8
    QVector<bool> optionalFlags;    // optional_1〜optional_8
    QStringList optionalTitles;     // opt_title1〜8

    // ===== special（4 個）=====
    QStringList specialIds;         // special1〜4
    QVector<bool> specialFlags;     // special_1〜special_4
    QStringList specialTitles;      // spec_title1〜4

    // ===== geometry =====
    QByteArray mainWindowGeometry;
    QByteArray messageWindowGeometry;

    // ===== 結合済みを返す便利関数 =====
    QStringList allProgramIds() const;
    QVector<bool> allProgramFlags() const;
    QStringList allProgramTitles() const;
};
