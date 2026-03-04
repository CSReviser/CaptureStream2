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
#include "settings.h"
#include "guistate.h"
#include "clioptions.h"

RuntimeConfig::RuntimeConfig()
{
    m_titleFormat.resize(Constants::ITEM_COUNT);
    m_fileNameFormat.resize(Constants::ITEM_COUNT);
    english.resize(Constants::EnglishCount);
    optional.resize(Constants::OptionalCount);
    spec.resize(Constants::SpecCount);
}

//
// Settings → 初期値
//
void RuntimeConfig::applySettings(const Settings& s)
{
    m_programs.clear();

    // ===== English =====
    for (int i = 0; i < Constants::EnglishCount; ++i) {
        const auto& p = Constants::EnglishPrograms[i];

        ProgramEntry e;
        e.checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
            e.id = s.ids[QString::fromUtf8(p.keyId)];
        if (p.hasLabel)
            e.label = s.labels[QString::fromUtf8(p.keyLabel)];
        e.category = Category::English;

        m_programs.append(e);
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; ++i) {
        const auto& p = Constants::OptionalPrograms[i];

        ProgramEntry e;
        e.checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
            e.id = s.ids[QString::fromUtf8(p.keyId)];
        if (p.hasLabel)
            e.label = s.labels[QString::fromUtf8(p.keyLabel)];
        e.category = Category::Optional;

        m_programs.append(e);
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecCount; ++i) {
        const auto& p = Constants::SpecPrograms[i];

        ProgramEntry e;
        e.checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
            e.id = s.ids[QString::fromUtf8(p.keyId)];
        if (p.hasLabel)
            e.label = s.labels[QString::fromUtf8(p.keyLabel)];
        e.category = Category::Spec;

        m_programs.append(e);
    }

    // ===== Feature flags =====
    for (int i = 0; i < Constants::getFeatureCount(); ++i) {
        const auto& f = Constants::FeatureSettings[i];
        m_flags[QString::fromUtf8(f.keyChecked)] = s.checked[QString::fromUtf8(f.keyChecked)];
    }

    // ===== その他 =====
    m_saveFolder     = s.saveFolder;
    m_ffmpegFolder   = s.ffmpegFolder;
    m_audioExtension = s.audioExtension;

    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        m_titleFormat[i]    = s.titleFormat[i];
        m_fileNameFormat[i] = s.fileNameFormat[i];
    }
    // ===== English =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];

        english[i].checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
        	english[i].id      = QString(s.ids[QString::fromUtf8(p.keyId)]);       // English は固定
        if (p.hasLabel)	
        	english[i].label   = QString(s.labels[QString::fromUtf8(p.keyLabel)]);    // English は固定
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
        	optional[i].id      = QString(s.ids[QString::fromUtf8(p.keyId)]);
        if (p.hasLabel)	
        	optional[i].label   = QString(s.labels[QString::fromUtf8(p.keyLabel)]);
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].checked = s.checked[QString::fromUtf8(p.keyChecked)];
        if (p.hasId)
        	spec[i].id      = QString(s.ids[QString::fromUtf8(p.keyId)]);
        if (p.hasLabel)	
        	spec[i].label   = QString(s.labels[QString::fromUtf8(p.keyLabel)]);
    }
}

//
// GUI → flags 上書きのみ
//
void RuntimeConfig::applyGui(const GuiState& g)
{
    for (auto it = g.flags.begin(); it != g.flags.end(); ++it) {
        m_flags[it.key()] = it.value();
    }
}

//
// CLI → 最終上書き
//
void RuntimeConfig::applyCommandLine(const CliOptions& cli)
{
    // ===== 値オプション =====
    if (cli.valueOptions.contains("saveFolder"))
        m_saveFolder = cli.valueOptions.value("saveFolder");

    if (cli.valueOptions.contains("ffmpegFolder"))
        m_ffmpegFolder = cli.valueOptions.value("ffmpegFolder");

    if (cli.valueOptions.contains("audioExtension"))
        m_audioExtension = cli.valueOptions.value("audioExtension");

    // ===== titleFormat / fileNameFormat =====
    for (int i = 0; i < Constants::ITEM_COUNT; ++i) {
        QString key1 = QString("titleFormat%1").arg(i);
        QString key2 = QString("fileNameFormat%1").arg(i);

        if (cli.valueOptions.contains(key1))
            m_titleFormat[i] = cli.valueOptions.value(key1);

        if (cli.valueOptions.contains(key2))
            m_fileNameFormat[i] = cli.valueOptions.value(key2);
    }

    // ===== フラグ =====
    for (const QString& key : cli.enabledKeys) {
        m_flags[key] = true;
    }

    // ===== CLI専用 programIds =====
    if (!cli.programIds.isEmpty())
        m_cliProgramIds = cli.programIds;
}

//
// ===== Getter =====
//
bool RuntimeConfig::flag(const QString& key) const
{
    return m_flags.value(key, false);
}

QString RuntimeConfig::saveFolder() const
{
    return m_saveFolder;
}

QString RuntimeConfig::ffmpegFolder() const
{
    return m_ffmpegFolder;
}

QString RuntimeConfig::audioExtension() const
{
    return m_audioExtension;
}

QString RuntimeConfig::titleFormatAt(int index) const
{
    return m_titleFormat.value(index);
}

QString RuntimeConfig::fileNameFormatAt(int index) const
{
    return m_fileNameFormat.value(index);
}

QVector<QString> RuntimeConfig::cliProgramIds() const
{
    return m_cliProgramIds;
}

QVector<RuntimeConfig::ProgramEntry> RuntimeConfig::allPrograms() const
{
    return m_programs;
}

QVector<RuntimeConfig::ProgramEntry> RuntimeConfig::checkedPrograms() const
{
    QVector<ProgramEntry> result;

    for (const auto& p : m_programs) {
        if (p.checked)
            result.append(p);
    }

    return result;
}

QVector<QString> RuntimeConfig::checkedProgramIds() const
{
    QVector<QString> ids;

    for (const auto& p : m_programs) {
        if (p.checked && !p.id.isEmpty())
            ids.append(p.id);
    }

    return ids;
}

/*
#include "runtimeconfig.h"
#include "constants.h"
#include <QDebug>

RuntimeConfig::RuntimeConfig()
{
    checkBox.resize(Constants::getFeatureCount());
    english.resize(Constants::EnglishCount);
    optional.resize(Constants::OptionalCount);
    spec.resize(Constants::SpecCount);

    titleFormat.resize(Constants::ITEM_COUNT);
    fileNameFormat.resize(Constants::ITEM_COUNT);
    // すべてのフラグを定義済みの初期値で埋める 
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
*/
