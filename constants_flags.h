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

// constants_flags.h
#pragma once
#include "constants_core.h"
#include "constants_programs.h"

namespace Constants {

    // ---- Flag 定義 ----
    struct FlagEntry {
        const char* keyFlag;    // "nogui" など
        bool flagDefault;       // 初期値
    };

    // --- 外部参照の宣言 ---
    extern const ProgramDefinition FeatureSettings[];
    extern const FlagEntry FlagTable[];

    // --- 個数取得関数の宣言 ---
    int getFeatureCount();
    int getFlagCount();

    // 以前の変数名に合わせたインライン関数（互換性維持のため）
    inline int getFeatureSettingsSize() { return getFeatureCount(); }
    inline int getFlagTableSize() { return getFlagCount(); }

}



/*
#pragma once
#include "constants_core.h"
#include "constants_programs.h"

namespace Constants {

/* ============================================================
 * Feature（チェックボックス）
 * ------------------------------------------------------------
 * checked のみ保存する。
 * id は不要なので空文字。checkBoxはlabelも空文字。
 * objectName が同一のエントリは、同一の UI ウィジェットを共有する。
 * （複数の設定値が 1 つの UI 状態に紐づくケースを想定）
 * ========================================================== */
 /*
inline const ProgramDefinition FeatureSettings[] = {
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

// ===== チェックボックスフラグの数 =====
inline constexpr int FeatureCount =
    sizeof(FeatureSettings) / sizeof(FeatureSettings[0]);


// ---- Flag ----
struct FlagEntry {
    const char* keyFlag;	// "nogui" など
    bool flagDefault;		// 初期値
};


/* ============================================================
 * Flag（チェックボックス、CLIオプションなど）
 * ------------------------------------------------------------
 * ini ファイルに保存されない RuntimeConfig で使用する Flag。
 * RuntimeConfig 生成時に default で初期化され、
 * Settings / GUI / CLI によって上書きされる。
 * Feature と重複する場合は後からの値が優先される。
 * ========================================================== */ 
   /*
inline const FlagEntry FlagTable[] = {
    { KEY_NOGUI,        false },	// CLI: -nogui = true
    { KEY_LAST_WEEK,    false },	// [前週]チェック = true
    { KEY_BOTH_WEEKS,   false },	// CLI: -b = true
    { KEY_PROGRAM_LIST, false },	// 番組一覧表示 = true
    { "featureX",       true  } 	// ini に保存される Feature でもよい
};

inline constexpr int FlagCount = 
    sizeof(FlagTable) / sizeof(FlagTable[0]);

}

*/ 



