/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2026 CSReviser Team

	This file is part of CaptureStream2, a recorder that supports HLS for 
	NHK radio language courses.
	CaptureStream2 is a modified version of CaptureStream, originally 
	developed by jakago.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-2.0.html>.
*/



#pragma once
#include <QString>
#include <QStringList>
#include <QMap>
#include "constants.h"
#include "settings.h"

// ===== 実行時に使う番組データ =====
struct RuntimeProgram {
    QString id;      // 実際に使用する番組ID
    QString label;   // 実際に使用するボタンラベル
    bool checked;    // 実行対象かどうか
};

class RuntimeConfig
{
public:
    RuntimeConfig();

    // Settings → RuntimeConfig へコピー
    void applySettings(const Settings &s);

    // CLI オプションで上書き
    void applyCommandLine(const QMap<QString, QString> &opts);

    // ===== 実行時の最終値 =====
    RuntimeProgram english[Constants::EnglishCount];
    RuntimeProgram optional[Constants::OptionalCount];
    RuntimeProgram spec[Constants::SpecCount];
    bool checkBox[Constants::FeatureCount];

    // ===== その他設定 =====
    QString saveFolder;
    QString audioExtension;

    // 最新番組一覧（ProgramEntry に変更）
    QMap<QString, Constants::ProgramEntry> latestProgramMap;

    // name_map / id_map / thumbnail_map
    QMap<QString, QString> id_map;
    QMap<QString, QString> name_map;
    QMap<QString, QString> thumbnail_map;
};

/*
#include "runtimeconfig.h"
#include "constants.h"

RuntimeConfig::RuntimeConfig()
{
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];

        english[i].enabled = s.enabled[p.keyEnabled];
        english[i].id      = p.idDefault;       // English は固定
        english[i].title   = p.titleDefault;    // English は固定
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].enabled = s.enabled[p.keyEnabled];
        optional[i].id      = s.ids[p.keyId];
        optional[i].title   = s.titles[p.keyTitle];
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].enabled = s.enabled[p.keyEnabled];
        spec[i].id      = s.ids[p.keyId];
        spec[i].title   = s.titles[p.keyTitle];
    }

    // ===== Flag（チェックボックス）=====
    for (int i = 0; i < Constants::FlagCount; i++) {
        const auto &p = Constants::FlagSettings[i];
        checkBox[i] = s.enabled[p.keyEnabled];
    }

    // ===== その他設定 =====
    saveFolder     = s.saveFolder;
    audioExtension = s.audioExtension;
}

void RuntimeConfig::applyCommandLine(const QMap<QString, QString> &opts)
{
    // --save-folder
    if (opts.contains("save-folder"))
        saveFolder = opts["save-folder"];

    // --audio-ext
    if (opts.contains("audio-ext"))
        audioExtension = opts["audio-ext"];

    // --enable=xxx
    if (opts.contains("enable")) {
        QString key = opts["enable"];

        for (int i = 0; i < Constants::EnglishCount; i++)
            if (Constants::EnglishPrograms[i].keyEnabled == key)
                english[i].enabled = true;

        for (int i = 0; i < Constants::OptionalCount; i++)
            if (Constants::OptionalPrograms[i].keyEnabled == key)
                optional[i].enabled = true;

        for (int i = 0; i < Constants::SpecCount; i++)
            if (Constants::SpecPrograms[i].keyEnabled == key)
                spec[i].enabled = true;
    }

    // --disable=xxx
    if (opts.contains("disable")) {
        QString key = opts["disable"];

        for (int i = 0; i < Constants::EnglishCount; i++)
            if (Constants::EnglishPrograms[i].keyEnabled == key)
                english[i].enabled = false;

        for (int i = 0; i < Constants::OptionalCount; i++)
            if (Constants::OptionalPrograms[i].keyEnabled == key)
                optional[i].enabled = false;

        for (int i = 0; i < Constants::SpecCount; i++)
            if (Constants::SpecPrograms[i].keyEnabled == key)
                spec[i].enabled = false;
    }
}
*/
/*
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
    RuntimeProgram spec[Constants::SpecCount];

    bool checkBox[Constants::FlagCount];

    // ===== その他設定 =====
    QString saveFolder;
    QString audioExtension;

    // 起動時に毎回取得する最新番組一覧
    QMap<QString, Constants::ProgramEntry> latestProgramMap;
    
    QMap<QString, QString> id_map;
    QMap<QString, QString> name_map;
    QMap<QString, QString> thumbnail_map;
    
};

*/
