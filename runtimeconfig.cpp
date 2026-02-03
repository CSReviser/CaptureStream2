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

RuntimeConfig::RuntimeConfig()
{
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English =====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &p = Constants::EnglishPrograms[i];

        english[i].checked = s.checked[p.keyChecked];
        english[i].id      = p.idDefault;       // English は固定
        english[i].label   = p.labelDefault;    // English は固定
    }

    // ===== Optional =====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].checked = s.checked[p.keyChecked];
        optional[i].id      = s.ids[p.keyId];
        optional[i].label   = s.labels[p.keyLabel];
    }

    // ===== Spec =====
    for (int i = 0; i < Constants::SpecCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].checked = s.checked[p.keyChecked];
        spec[i].id      = s.ids[p.keyId];
        spec[i].label   = s.labels[p.keyLabel];
    }

    // ===== Feature（チェックボックス）=====
    for (int i = 0; i < Constants::FeatureCount; i++) {
        const auto &p = Constants::FeatureSettings[i];
        checkBox[i] = s.checked[p.keyChecked];
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
            if (Constants::EnglishPrograms[i].keyChecked == key)
                english[i].checked = true;

        for (int i = 0; i < Constants::OptionalCount; i++)
            if (Constants::OptionalPrograms[i].keyChecked == key)
                optional[i].checked = true;

        for (int i = 0; i < Constants::SpecCount; i++)
            if (Constants::SpecPrograms[i].keyChecked == key)
                spec[i].checked = true;
    }

    // --disable=xxx
    if (opts.contains("disable")) {
        QString key = opts["disable"];

        for (int i = 0; i < Constants::EnglishCount; i++)
            if (Constants::EnglishPrograms[i].keyChecked == key)
                english[i].checked = false;

        for (int i = 0; i < Constants::OptionalCount; i++)
            if (Constants::OptionalPrograms[i].keyChecked == key)
                optional[i].checked = false;

        for (int i = 0; i < Constants::SpecCount; i++)
            if (Constants::SpecPrograms[i].keyChecked == key)
                spec[i].checked = false;
    }
}

/*
#include "runtimeconfig.h"
#include "constants.h"

RuntimeConfig::RuntimeConfig()
{
    // 何もせず applySettings() に任せる
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English（固定：id/title は Constants、enabled は Settings）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        const QString &key = def.key;

        english[i].id      = def.id;
        english[i].title   = def.title;
        english[i].enabled = s.englishEnabled.value(key, def.enabled);
    }

    // ===== Optional（editable：id/title/enabled は Settings）=====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].enabled = s.optionalEnabled.value(p.keyEnabled, p.enabledDefault);
        optional[i].id      = s.optionalId.value(p.keyId, p.idDefault);
        optional[i].title   = s.optionalTitle.value(p.keyTitle, p.titleDefault);
    }

    // ===== Spec（editable）=====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].enabled = s.specEnabled.value(p.keyEnabled, p.enabledDefault);
        spec[i].id      = s.specId.value(p.keyId, p.idDefault);
        spec[i].title   = s.specTitle.value(p.keyTitle, p.titleDefault);
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &c = Constants::CheckBoxSettings[i];
        checkBox[i] = s.checkBoxEnabled.value(c.keyEnabled, c.enabledDefault);
    }

    // ===== その他設定 =====
    saveFolder     = s.saveFolder;
    audioExtension = s.audioExtension;
}

void RuntimeConfig::applyCommandLine(const QMap<QString, QString> &opts)
{
    // 例: --save-folder=/path/to/dir
    if (opts.contains("save-folder")) {
        saveFolder = opts["save-folder"];
    }

    // 例: --audio-ext=m4a
    if (opts.contains("audio-ext")) {
        audioExtension = opts["audio-ext"];
    }

    // 例: --enable=optional3
    if (opts.contains("enable")) {
        QString key = opts["enable"];

        // English
        for (int i = 0; i < Constants::EnglishCount; i++) {
            if (Constants::EnglishPrograms[i].key == key) {
                english[i].enabled = true;
            }
        }

        // Optional
        for (int i = 0; i < Constants::OptionalCount; i++) {
            if (Constants::OptionalPrograms[i].keyEnabled == key) {
                optional[i].enabled = true;
            }
        }

        // Spec
        for (int i = 0; i < Constants::SpecialCount; i++) {
            if (Constants::SpecPrograms[i].keyEnabled == key) {
                spec[i].enabled = true;
            }
        }
    }

    // 例: --disable=optional3
    if (opts.contains("disable")) {
        QString key = opts["disable"];

        // English
        for (int i = 0; i < Constants::EnglishCount; i++) {
            if (Constants::EnglishPrograms[i].key == key) {
                english[i].enabled = false;
            }
        }

        // Optional
        for (int i = 0; i < Constants::OptionalCount; i++) {
            if (Constants::OptionalPrograms[i].keyEnabled == key) {
                optional[i].enabled = false;
            }
        }

        // Spec
        for (int i = 0; i < Constants::SpecialCount; i++) {
            if (Constants::SpecPrograms[i].keyEnabled == key) {
                spec[i].enabled = false;
            }
        }
    }
}

*/
