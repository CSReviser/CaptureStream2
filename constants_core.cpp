#include "constants_core.h"

namespace Constants {

    // ===== アプリ情報 =====
    const char* const AppName    = "語学講座ＣＳ２";
    const char* const AppVersion = "2026/03/07";

    // ===== INI ファイル名 =====
    const char* const IniFileName = "CaptureStream2.ini";
    
    // ===== QSettings グループ =====
    const char* const SETTING_GROUP_MainWindow      = "MainWindow";
    const char* const SETTING_GROUP_CustomizeDialog = "CustomizeDialog";
    const char* const SETTING_GROUP_MessageWindow   = "MessageWindow";
    const char* const SETTING_GROUP_ScrambleDialog  = "ScrambleDialog";
    const char* const SETTING_GROUP_Settingsdialog  = "Settingsdialog";
    
    // ===== 拡張子　設定キー デフォルト値 =====
    const char* const KEY_AudioExtension     = "audio_extension";
    const char* const DEFAULT_AudioExtension = "m4a";

    // ===== フォルダ設定キー =====
    // ===== デフォルト値 キーが無ければ null を settings で設定 =====
    const char* const KEY_SaveFolder     = "save_folder";
    const char* const KEY_FfmpegFolder   = "ffmpeg_folder";
    
    // ===== 英語講座　設定キー  =====
    const char* const KEY_basic0     = "basic0";
    const char* const KEY_basic1     = "basic1";
    const char* const KEY_basic2     = "basic2";
    const char* const KEY_timetrial  = "timetrial";
    const char* const KEY_enjoy      = "enjoy";
    const char* const KEY_kaiwa      = "kaiwa";
    const char* const KEY_business   = "business1";
    const char* const KEY_gendai     = "gendai";
 
     // ===== フラグ　設定キー  =====
    const char* const KEY_KOZA_SEPARATION = "koza_separation";
    const char* const KEY_MULTI_GUI       = "multi_gui";
    const char* const KEY_NAME_SPACE      = "name_space";
    const char* const KEY_TAG_SPACE       = "tag_space"; 
    const char* const KEY_NOGUI           = "nogui";			// CLI: -nogui
    const char* const KEY_LAST_WEEK       = "last_week";		// GUI: [前週]、CLI: -z
    const char* const KEY_BOTH_WEEKS      = "both_weeks";		// CLI: -b
    const char* const KEY_PROGRAM_LIST    = "program_list";		// GUI: 番組一覧表示
    const char* const KEY_SKIP		  = "skip";			// GUI: スキップ
    const char* const KEY_THUMBNAIL	  = "thumbnail";		// GUI: サムネイル
    const char* const KEY_THUMBNAIL_OFF	  = "thumbnail_off";		// CLI: サムネイルOFF
    const char* const KEY_MESSAGE_ON	  = "MESSAGE_ON";		// CLI: メッセージ表示
    // ===== FILE NAME、TITLE　設定キー  =====
    const char* const KEY_CUSTOMIZED_TITLE1    = "customized_title1";
    const char* const KEY_CUSTOMIZED_TITLE2    = "customized_title2";
    const char* const KEY_CUSTOMIZED_FILENAME1 = "customized_file_name1";
    const char* const KEY_CUSTOMIZED_FILENAME2 = "customized_file_name2";
    
}
