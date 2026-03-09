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
