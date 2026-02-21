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

#include "runtimeconfig.h"
#include "constants.h"
#include <QDebug>

RuntimeConfig::RuntimeConfig()
{
    // すべてのフラグを定義済みの初期値で埋める
    checkBox.resize(Constants::getFeatureCount());
    for (int i = 0; i < Constants::getFlagCount(); ++i) {
        const auto &f = Constants::FlagTable[i];
        flags[f.keyFlag] = f.flagDefault;
    }
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];

        english[i].checked = s.checked[p.keyChecked];
        if (p.hasId)
        	english[i].id      = QString(s.ids[p.keyId]);       // English は固定
        if (p.hasLabel)	
        	english[i].label   = QString(s.labels[p.keyLabel]);    // English は固定
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].checked = s.checked[p.keyChecked];
        if (p.hasId)
        	optional[i].id      = QString(s.ids[p.keyId]);
        if (p.hasLabel)	
        	optional[i].label   = QString(s.labels[p.keyLabel]);
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].checked = s.checked[p.keyChecked];
        if (p.hasId)
        	spec[i].id      = QString(s.ids[p.keyId]);
        if (p.hasLabel)	
        	spec[i].label   = QString(s.labels[p.keyLabel]);
    }

    // ===== Feature（チェックボックス）=====
    for (int i = 0; i < Constants::getFeatureCount(); i++) {
        const auto &p = Constants::FeatureSettings[i];
        checkBox[i] = s.checked[p.keyChecked];
        setFlag(p.keyChecked, s.checked[p.keyChecked]);   // flags にも反映
    }

    // ===== その他設定 =====
    saveFolder     = s.saveFolder;
    ffmpegFolder   = s.ffmpegFolder;
    audioExtension = s.audioExtension;
    
    // ===== CustomizeDialog =====
    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        titleFormat[i]    = s.titleFormat[i];
        fileNameFormat[i] = s.fileNameFormat[i];
    }

}

void RuntimeConfig::applyGui(const GuiState& g)
{
    for (auto it = g.flags.begin(); it != g.flags.end(); ++it) {
        setFlag(it.key(), it.value());
    }
}

void RuntimeConfig::applyCommandLine(const CliOptions& cli)
{
    // 1. 値を取るオプション（CLI が指定したものだけ上書き）
    for (auto it = cli.valueOptions.constBegin(); it != cli.valueOptions.constEnd(); ++it) {
        set(it.key(), it.value());
    }

    // 2. フラグオプション（CLI が指定したものだけ true にする）
    for (const QString& key : cli.enabledKeys) {
        set(key, true);
    }

    // 3. プログラムID（CLI が指定したものだけ反映）
    cliProgramIds.clear();
    for (const QString& id : cli.programIds) {
        cliProgramIds.push_back(id);
    }
}

void RuntimeConfig::setFlag(const QString &key, bool value)
{
    flags[key] = value;
}

bool RuntimeConfig::flag(const QString &key) const
{
    return flags.value(key, false);
}

QVector<RuntimeConfig::ProgramEntry> RuntimeConfig::allPrograms() const
{
    QVector<ProgramEntry> list;

    // English
    for (int i = 0; i < Constants::EnglishCount; i++) {
        ProgramEntry e;
        e.checked  = english[i].checked;
        e.id       = english[i].id;
        e.label    = english[i].label;
        e.category = "english";
        list.append(e);
    }

    // Optional
    for (int i = 0; i < Constants::OptionalCount; i++) {
        ProgramEntry e;
        e.checked  = optional[i].checked;
        e.id       = optional[i].id;
        e.label    = optional[i].label;
        e.category = "optional";
        list.append(e);
    }

    // Spec
    for (int i = 0; i < Constants::SpecCount; i++) {
        ProgramEntry e;
        e.checked  = spec[i].checked;
        e.id       = spec[i].id;
        e.label    = spec[i].label;
        e.category = "spec";
        list.append(e);
    }

    return list;
}

QVector<RuntimeConfig::ProgramEntry> RuntimeConfig::checkedPrograms() const
{
    QVector<ProgramEntry> list;

    // English
    for (int i = 0; i < Constants::EnglishCount; i++) {
        if (english[i].checked) {
            ProgramEntry e;
            e.checked  = true;
            e.id       = english[i].id;
            e.label    = english[i].label;
            e.category = "english";
            list.append(e);
        }
    }

    // Optional
    for (int i = 0; i < Constants::OptionalCount; i++) {
        if (optional[i].checked) {
            ProgramEntry e;
            e.checked  = true;
            e.id       = optional[i].id;
            e.label    = optional[i].label;
            e.category = "optional";
            list.append(e);
        }
    }

    // Spec
    for (int i = 0; i < Constants::SpecCount; i++) {
        if (spec[i].checked) {
            ProgramEntry e;
            e.checked  = true;
            e.id       = spec[i].id;
            e.label    = spec[i].label;
            e.category = "spec";
            list.append(e);
        }
    }

    return list;
}

void RuntimeConfig::set(const QString& key, const QString& value)
{
    m_overrides.insert(key, value);
}

void RuntimeConfig::set(const QString& key, bool value)
{
    m_overrides.insert(key, value);
}
