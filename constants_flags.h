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
        const char* objectName;   // GUI widget name
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


