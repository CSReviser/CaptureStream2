#include "constants_cli.h"

namespace Constants {

/* ============================================================
 * CLI オプションテーブル
 * ========================================================== */
const CliOption OPTION_TABLE[] = {
    { "-nogui", false, KEY_NOGUI,              "GUI を起動せずに実行します" },
    { "-t",     true,  KEY_CUSTOMIZED_TITLE1,  "タイトルタグ形式を指定します" },
    { "-f",     true,  KEY_CUSTOMIZED_FILENAME1,"ファイル名形式を指定します" },
    { "-o",     true,  KEY_SaveFolder,         "保存フォルダのフルパスを指定します" },
    { "-e",     true,  KEY_AudioExtension,     "拡張子を指定します" },
    { "-z",     false, KEY_LAST_WEEK,          "前週の動作を行います" },
    { "-b",     false, KEY_BOTH_WEEKS,         "前週と当週の両方を実行します" },
    { "-s",     false, KEY_KOZA_SEPARATION,    "応用編分離を有効にします" },
    { "-m",     false, KEY_MESSAGE_ON,		"メッセージ表示を有効にします" },
    { "-a0",    false,  KEY_THUMBNAIL_OFF,	"サムネイル追加を無効にします" },
    { "-a1",    false, KEY_THUMBNAIL,	  	"サムネイル追加を有効にします" },
};

// --- 個数取得の実装 ---
int getOptionTableCount() {
    return sizeof(OPTION_TABLE) / sizeof(OPTION_TABLE[0]);
}

const FlagControl CLI_FLAG_CONTROLS[] = {
    {"thumbnail", "thumbnail-off", "thumbnail"},
    {"debug", "debug-off", "debug"}
    // 他のフラグペアもここに追加
};

// --- 個数取得の実装 ---
int getCLI_FLAG_CONTROLSCount() {
    return sizeof(CLI_FLAG_CONTROLS) / sizeof(CLI_FLAG_CONTROLS[0]);
}

} // namespace Constants
