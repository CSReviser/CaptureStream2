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
#include "guistate.h"
#include "clioptions.h"

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

    // GUI オプションで上書き
    void applyGui(const GuiState& g);
    
    // CLI オプションで上書き
    void applyCommandLine(const CliOptions &cli);

    // ===== 実行時の最終値 =====
    QVector<RuntimeProgram> english;
    QVector<RuntimeProgram> optional;
    QVector<RuntimeProgram> spec;
    bool checkBox[Constants::getFeatureCount];

    // ===== その他設定 =====
    QString saveFolder;
    QString ffmpegFolder;
    QString audioExtension;
    
    // ===== GUI: CustomizeDialog =====
    QVector<QString> titleFormat;
    QVector<QString> fileNameFormat;

    // ===== CLI: 録画設定 =====
    std::optional<QString> cliTitleTagFormat;   // -t
    std::optional<QString> cliFileNameFormat;   // -f
    std::optional<QString> cliOutputFolder;     // -o
    std::optional<QString> cliExtension;        // -e

    std::vector<QString> cliProgramIds;
    
    // 最新番組一覧（ProgramDefinition に変更）
    QMap<QString, Constants::ProgramDefinition> latestProgramMap;

    // ===== flags（GUI + CLI 統合）=====
    QMap<QString, bool> flags;    
    void setFlag(const QString &key, bool value);
    bool flag(const QString &key) const;
    
    struct ProgramEntry
{
    bool checked;        // 有効かどうか
    QString id;          // 実行に使う ID
    QString label;       // 表示用ラベル
    QString category;    // "english" / "optional" / "spec"
};

    QVector<ProgramEntry> allPrograms() const;

    QVector<ProgramEntry> checkedPrograms() const;
    
private:
    // ===== Flag（チェックボックス、CLIオプションなど）設定 =====
//    QMap<QString, bool> flags; 
};

