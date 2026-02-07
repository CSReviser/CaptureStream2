#include "constants_cli.h"

namespace Constants {

const CliOption OPTION_TABLE[] = {
    { "-nogui", false, KEY_NOGUI,              "GUI を起動せずに実行します" },
    { "-t",     true,  KEY_CUSTOMIZED_TITLE1,  "タイトルタグ形式を指定します" },
    { "-f",     true,  KEY_CUSTOMIZED_FILENAME1,"ファイル名形式を指定します" },
    { "-o",     true,  KEY_SaveFolder,         "保存フォルダのフルパスを指定します" },
    { "-e",     true,  KEY_AudioExtension,     "拡張子を指定します" },
    { "-z",     false, KEY_LAST_WEEK,          "前週の動作を行います" },
    { "-b",     false, KEY_BOTH_WEEKS,         "前週と当週の両方を実行します" },
    { "-s",     false, KEY_KOZA_SEPARATION,    "応用編分離を有効にします" },
};

const int OPTION_TABLE_COUNT =
    sizeof(OPTION_TABLE) / sizeof(OPTION_TABLE[0]);

}