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
    QString ffmpegFolder;
    QString audioExtension;

    // 最新番組一覧（ProgramEntry に変更）
    QMap<QString, Constants::ProgramEntry> latestProgramMap;

    // name_map / id_map / thumbnail_map
    QMap<QString, QString> id_map;
    QMap<QString, QString> name_map;
    QMap<QString, QString> thumbnail_map;
    
    void setFlag(const QString &key, bool value);
    bool flag(const QString &key) const;
    
private:
    // ===== Flag（チェックボックス、CLIオプションなど）設定 =====
    QMap<QString, bool> flags; 
};

