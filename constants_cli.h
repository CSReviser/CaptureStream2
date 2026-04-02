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

// constants_cli.h
#pragma once
#include "constants_core.h"

namespace Constants {

struct CliOption {
    const char* name;
    bool requiresValue;
    const char* keyOption; // GUI、Flagの キーと一致
    const char* description;
    const char* group;   // 追加
};

// --- 外部参照の宣言 ---
extern const CliOption OPTION_TABLE[];

// --- 個数取得関数の宣言 ---
int getOptionTableCount();

struct FlagControl {
    const char* onKey;   // 例: "thumbnail"
    const char* offKey;  // 例: "thumbnail-off"
    const char* target;  // 最終的に m_flags で使うキー: "thumbnail"
};

// --- 外部参照の宣言 ---
extern const FlagControl CLI_FLAG_CONTROLS[];

// --- 個数取得関数の宣言 ---
int getCLI_FLAG_CONTROLSCount();

extern const char* HELP_USAGE;
extern const char* HELP_HEADER;
extern const char* HELP_PROGRAMID;

} // namespace Constants




/*
#pragma once
#include "constants_core.h"

namespace Constants {

struct CliOption {
    const char* name;
    bool requiresValue;
    const char* keyOption;	// GUI、Flagの キーと一致
    const char* description;
};

inline const CliOption OPTION_TABLE[] = {
    { "-nogui", false, KEY_NOGUI,              "GUI を起動せずに実行します" },
    { "-t",     true,  KEY_CUSTOMIZED_TITLE1,  "タイトルタグ形式を指定します" },
    { "-f",     true,  KEY_CUSTOMIZED_FILENAME1,"ファイル名形式を指定します" },
    { "-o",     true,  KEY_SaveFolder,         "保存フォルダのフルパスを指定します" },
    { "-e",     true,  KEY_AudioExtension,     "拡張子を指定します" },
    { "-z",     false, KEY_LAST_WEEK,          "前週の動作を行います" },
    { "-b",     false, KEY_BOTH_WEEKS,         "前週と当週の両方を実行します" },
    { "-s",     false, KEY_KOZA_SEPARATION,    "応用編分離を有効にします" },
};

inline constexpr int OPTION_TABLE_COUNT = std::size(OPTION_TABLE);
 //   sizeof(OPTION_TABLE) / sizeof(OPTION_TABLE[0]);

}
*/
