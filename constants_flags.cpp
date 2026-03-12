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

#include "constants_flags.h"

namespace Constants {

/* ============================================================
 * Feature（チェックボックス）
 * ------------------------------------------------------------
 * ini に保存される、UIと連動する設定。
 * ========================================================== */
const ProgramDefinition FeatureSettings[] = {
    { ProgramDefinition::Kind::Feature,
      "skip", true,
      nullptr, nullptr, false, false,
      "skip_keyLabel", "既存のファイルはスキップ", false, true,
      "toolButton_skip" },

    { ProgramDefinition::Kind::Feature,
      "this_week", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_this_week" },

    { ProgramDefinition::Kind::Feature,
      "thumbnail", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_thumbnail" },

    { ProgramDefinition::Kind::Feature,
      "koza_separation", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_koza_separation" },

    { ProgramDefinition::Kind::Feature,
      "multi_gui", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox_multi_gui" },

    { ProgramDefinition::Kind::Feature,
      "name_space", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "tag_space", true,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "checkBox" },

    { ProgramDefinition::Kind::Feature,
      "detailed_message", false,
      nullptr, nullptr, false, false,
      nullptr, nullptr, false, false,
      "toolButton_detailed_message" }
};

// 個数取得の実装
int getFeatureCount() {
    return sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);
}


/* ============================================================
 * Flag（実行時フラグ）
 * ------------------------------------------------------------
 * RuntimeConfig で使用される、保存されないフラグ。
 * ========================================================== */   
const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },
    { KEY_LAST_WEEK,    false },
    { KEY_BOTH_WEEKS,   false },
    { KEY_PROGRAM_LIST, false },
    { KEY_THUMBNAIL,	false },
    { "featureX",       true  }
};

// 個数取得の実装
int getFlagCount() {
    return sizeof(FlagTable) / sizeof(FlagTable[0]);
}

}
