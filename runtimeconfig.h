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
