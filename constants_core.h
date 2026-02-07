// constants_core.h
#pragma once
namespace Constants {

        // ===== アプリ情報 =====
    inline constexpr auto  AppName = "語学講座ＣＳ２";
    inline constexpr auto  AppVersion = "2026/01/29";

    // ===== INI ファイル名 =====
    inline constexpr auto  IniFileName = "CaptureStream2.ini";
    
    // ===== QSettings グループ =====
    inline constexpr auto  SETTING_GROUP_MainWindow = "MainWindow";
    inline constexpr auto  SETTING_GROUP_CustomizeDialog = "CustomizeDialog";
    inline constexpr auto  SETTING_GROUP_MessageWindow = "MessageWindow";
    inline constexpr auto  SETTING_GROUP_ScrambleDialog = "ScrambleDialog";
    inline constexpr auto  SETTING_GROUP_Settingsdialog = "Settingsdialog";
    
    // ===== 拡張子　設定キー デフォルト値 =====
    inline constexpr auto  KEY_AudioExtension = "audio_extension";
    inline constexpr auto  DEFAULT_AudioExtension = "m4a";

    // ===== フォルダ設定キー =====
    // ===== デフォルト値 キーが無ければ null を settings で設定 =====
    inline constexpr auto  KEY_SaveFolder     = "save_folder";
    inline constexpr auto  KEY_FfmpegFolder   = "ffmpeg_folder";
    
    // ===== 英語講座　設定キー  =====
    inline constexpr auto  KEY_basic0 = "basic0";
    inline constexpr auto  KEY_basic1 = "basic1";
    inline constexpr auto  KEY_basic2 = "basic2";
    inline constexpr auto  KEY_timetrial = "timetrial";
    inline constexpr auto  KEY_enjoy = "enjoy";
    inline constexpr auto  KEY_kaiwa =  "kaiwa";
    inline constexpr auto  KEY_business = "business1";
    inline constexpr auto  KEY_gendai = "gendai";
 
    // ===== フラグ　設定キー  =====
    inline constexpr auto  KEY_KOZA_SEPARATION = "koza_separation";
    inline constexpr auto  KEY_MULTI_GUI = "multi_gui";
    inline constexpr auto  KEY_NAME_SPACE = "name_space";
    inline constexpr auto  KEY_TAG_SPACE = "tag_space"; 
    inline constexpr auto  KEY_NOGUI 	= "nogui";		// CLI: -nogui
    inline constexpr auto  KEY_LAST_WEEK 	= "last_week";		// GUI: [前週]、CLI: -z
    inline constexpr auto  KEY_BOTH_WEEKS	= "both_weeks";		// CLI: -b
    inline constexpr auto  KEY_PROGRAM_LIST = "program_list";	// GUI: 番組一覧表示
    
    // ===== FILE NAME、TITLE　設定キー  =====
    inline constexpr auto  KEY_CUSTOMIZED_TITLE1 	= "customized_title1";
    inline constexpr auto  KEY_CUSTOMIZED_TITLE2 	= "customized_title2";
    inline constexpr auto  KEY_CUSTOMIZED_FILENAME1 	= "customized_file_name1";
    inline constexpr auto  KEY_CUSTOMIZED_FILENAME2 	= "customized_file_name2";
    
}
