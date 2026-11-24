/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
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
#include "constants_gui.h"

namespace Constants {

// ===== GUI テーマ一覧 =====
const ThemeDefinition Themes[] = {
    { "original", "オリジナル（Original）" },
    { "blue",    "ブルー（Blue）" },
    { "darkblue", "ダークブルー（DarkBlue）" },
    { "brown",   "ブラウン（Brown）" },
    { "chocolate", "チョコレート（Chocolate）" },
    { "green",   "グリーン（Green）" },
    { "darkgreen", "ダークグリーン（DarkGreen）" },
    { "indigo",  "インディゴ（Indigo）" },
    { "purple",  "パープル（Purple）" },
    { "red",      "レッド（Red）" },
    { "darkred", "ダークレッド（DarkRed）" },
    { "yellow",   "イエロー（Yellow）" }
};

const int ThemeCount =
    sizeof(Themes) / sizeof(Themes[0]);

// ===== GUI Appearance デフォルト設定 =====
const AppearanceDefaults DEFAULT_Appearance = {
    "original",
    true,
    true
};

// ===== GUI Appearance 設定キー =====
const char* const SETTING_GROUP_Appearance = "Appearance";

const char* const KEY_Theme                 = "theme";
const char* const KEY_UseExternalStyleSheet = "useExternalStyleSheet";
const char* const KEY_UseExternalIcons      = "useExternalIcons";

} // namespace Constants

