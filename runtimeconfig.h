#pragma once
#include <QString>
#include <QStringList>
#include <QMap>

struct RuntimeConfig
{
    // ===== CLI の一時オプション =====
    QString inputFile;
    QString outputFolder;
    QStringList programIds;
    bool dryRun = false;

    // ===== 実行中に生成される一時データ =====
    QMap<QString, QString> programUrlMap;     // 番組ID → URL
    QMap<QString, QString> outputFolderMap;   // 番組ID → 保存先
    QMap<QString, bool>    downloadResultMap; // 番組ID → 成否

    // ===== 実行状態 =====
    bool isProcessing = false;
    int currentIndex = 0;

    // ===== 一時フォルダなど =====
    QString tempFolder;
};

#pragma once
#include <QString>
#include "constants.h"
#include "settings.h"

struct RuntimeProgram {
    QString id;
    QString title;
    bool enabled;
};

class RuntimeConfig
{
public:
    RuntimeConfig();

    // Settings → RuntimeConfig へコピー
    void applySettings(const Settings &s);

    // CLI オプションで上書き（必要に応じて拡張）
    void applyCommandLine(const QMap<QString, QString> &opts);

    // ===== 実行時の最終値 =====
    RuntimeProgram english[Constants::EnglishCount];
    RuntimeProgram optional[Constants::OptionalCount];
    RuntimeProgram spec[Constants::SpecialCount];

    bool checkBox[Constants::CheckBoxCount];

    // ===== 実行時のその他設定（必要に応じて追加）=====
    QString saveFolder;
    QString audioExtension;
};

