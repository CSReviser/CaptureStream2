#pragma once
#include <QString>
#include <QStringList>
#include <QMap>
#include "constants.h"
#include "settings.h"

// ===== 実行中に使う一時データ =====
struct RuntimeConfig1
{
    // CLI の一時オプション
    QString inputFile;
    QString outputFolder;
    QStringList programIds;
    bool dryRun = false;

    // 実行中に生成される一時データ
    QMap<QString, QString> programUrlMap;     // 番組ID → URL
    QMap<QString, QString> outputFolderMap;   // 番組ID → 保存先
    QMap<QString, bool>    downloadResultMap; // 番組ID → 成否

    // 実行状態
    bool isProcessing = false;
    int currentIndex = 0;

    // 一時フォルダ
    QString tempFolder;
};

// ===== 実行時に使う番組データ =====
struct RuntimeProgram {
    QString id;      // 実際に使用する番組ID
    QString title;   // 実際に使用するタイトル
    bool enabled;    // 実行対象かどうか
};

class RuntimeConfig
{
public:
    RuntimeConfig();

    // Settings → RuntimeConfig へコピー
    // Settings は key 対応（QMap）なので applySettings 内で key を使って参照する
    void applySettings(const Settings &s);

    // CLI オプションで上書き
    void applyCommandLine(const QMap<QString, QString> &opts);

    // ===== 実行時の最終値 =====
    // Constants の配列数に合わせて固定長配列
    RuntimeProgram english[Constants::EnglishCount];
    RuntimeProgram optional[Constants::OptionalCount];
    RuntimeProgram spec[Constants::SpecialCount];

    bool checkBox[Constants::CheckBoxCount];

    // ===== その他設定 =====
    QString saveFolder;
    QString audioExtension;

    // 起動時に毎回取得する最新番組一覧
    QMap<QString, ProgramInfo> latestProgramMap;
    
    QMap<QString, QString> id_map;
    QMap<QString, QString> name_map;
    QMap<QString, QString> thumbnail_map;
    
};
