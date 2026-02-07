// constants_core.h
#pragma once
namespace Constants {

        // ===== アプリ情報 =====
    inline constexpr const char*  AppName = "語学講座ＣＳ２";
    inline constexpr const char*  AppVersion = "2026/01/29";

    // ===== INI ファイル名 =====
    inline constexpr const char*  IniFileName = "CaptureStream2.ini";
    
    // ===== QSettings グループ =====
    inline constexpr const char*  SETTING_GROUP_MainWindow = "MainWindow";
    inline constexpr const char*  SETTING_GROUP_CustomizeDialog = "CustomizeDialog";
    inline constexpr const char*  SETTING_GROUP_MessageWindow = "MessageWindow";
    inline constexpr const char*  SETTING_GROUP_ScrambleDialog = "ScrambleDialog";
    inline constexpr const char*  SETTING_GROUP_Settingsdialog = "Settingsdialog";
    
    // ===== 拡張子　設定キー デフォルト値 =====
    inline constexpr const char*  KEY_AudioExtension = "audio_extension";
    inline constexpr const char*  DEFAULT_AudioExtension = "m4a";

    // ===== フォルダ設定キー =====
    // ===== デフォルト値 キーが無ければ null を settings で設定 =====
    inline constexpr const char*  KEY_SaveFolder     = "save_folder";
    inline constexpr const char*  KEY_FfmpegFolder   = "ffmpeg_folder";
    
    // ===== 英語講座　設定キー  =====
    inline constexpr const char*  KEY_basic0 = "basic0";
    inline constexpr const char*  KEY_basic1 = "basic1";
    inline constexpr const char*  KEY_basic2 = "basic2";
    inline constexpr const char*  KEY_timetrial = "timetrial";
    inline constexpr const char*  KEY_enjoy = "enjoy";
    inline constexpr const char*  KEY_kaiwa =  "kaiwa";
    inline constexpr const char*  KEY_business = "business1";
    inline constexpr const char*  KEY_gendai = "gendai";
 
    // ===== フラグ　設定キー  =====
    inline constexpr const char*  KEY_KOZA_SEPARATION = "koza_separation";
    inline constexpr const char*  KEY_MULTI_GUI = "multi_gui";
    inline constexpr const char*  KEY_NAME_SPACE = "name_space";
    inline constexpr const char*  KEY_TAG_SPACE = "tag_space"; 
    inline constexpr const char*  KEY_NOGUI 	= "nogui";		// CLI: -nogui
    inline constexpr const char*  KEY_LAST_WEEK 	= "last_week";		// GUI: [前週]、CLI: -z
    inline constexpr const char*  KEY_BOTH_WEEKS	= "both_weeks";		// CLI: -b
    inline constexpr const char*  KEY_PROGRAM_LIST = "program_list";	// GUI: 番組一覧表示
    
    // ===== FILE NAME、TITLE　設定キー  =====
    inline constexpr const char*  KEY_CUSTOMIZED_TITLE1 	= "customized_title1";
    inline constexpr const char*  KEY_CUSTOMIZED_TITLE2 	= "customized_title2";
    inline constexpr const char*  KEY_CUSTOMIZED_FILENAME1 	= "customized_file_name1";
    inline constexpr const char*  KEY_CUSTOMIZED_FILENAME2 	= "customized_file_name2";
    
}
