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

#include "constants_cli.h"

namespace Constants {

/* ============================================================
 * CLI オプションテーブル
 * ========================================================== */
const CliOption OPTION_TABLE[] = {
    { "-nogui", false, KEY_NOGUI,              "GUI を起動せずに実行します", nullptr },
    { "-t",     true,  KEY_CUSTOMIZED_TITLE1,  "タイトルタグ形式を指定します", nullptr },
    { "-f",     true,  KEY_CUSTOMIZED_FILENAME1,"ファイル名形式を指定します", nullptr },
    { "-o",     true,  KEY_SaveFolder,         "保存フォルダのフルパスを指定します", nullptr },
    { "-e",     true,  KEY_AudioExtension,     "拡張子を指定します", nullptr },
    { "-z",     false, KEY_LAST_WEEK,          "前週の動作を行います", nullptr },
    { "-b",     false, KEY_BOTH_WEEKS,         "前週と当週の両方を実行します", nullptr },
    { "-s",     false, KEY_KOZA_SEPARATION,    "応用編分離を有効にします", nullptr },
    { "-m",     false, KEY_MESSAGE_ON,		"メッセージ表示を有効にします", nullptr },
    { "-a0",    false,  KEY_THUMBNAIL_OFF,	"サムネイル追加を無効にします", "thumbnail"  },
    { "-a1",    false, "thumbnail-on",	  	"サムネイル追加を有効にします", "thumbnail"  },
    { "-x",    false, KEY_THUMBNAIL,	  	"サムネイル追加を有効にします", "thumbnail"  },
    { "-h",    false, KEY_HELP,	  	"ヘルプ表示す", "help"  },
    { "-help",    false, KEY_HELP,	  	"ヘルプ表示す", "help"  },
};

// --- 個数取得の実装 ---
int getOptionTableCount() {
    return sizeof(OPTION_TABLE) / sizeof(OPTION_TABLE[0]);
}

const FlagControl CLI_FLAG_CONTROLS[] = {
    {"thumbnail-on", KEY_THUMBNAIL_OFF, KEY_THUMBNAIL},
    {"debug", "debug-off", "debug"}
    // 他のフラグペアもここに追加
};

// --- 個数取得の実装 ---
int getCLI_FLAG_CONTROLSCount() {
    return sizeof(CLI_FLAG_CONTROLS) / sizeof(CLI_FLAG_CONTROLS[0]);
}

const char* HELP_USAGE =
"Usage: capturestream2 [options] [program_id...]";

const char* HELP_HEADER =
"Options:";

const char* HELP_PROGRAMID =
"program_id を指定すると対象番組のみ処理します";

} // namespace Constants
