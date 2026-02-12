// constants_core.h
#pragma once

namespace Constants {

    // ===== アプリ情報 =====
    extern const char* const AppName;
    extern const char* const AppVersion;

    // ===== INI ファイル名 =====
    extern const char* const IniFileName;
    
    // ===== QSettings グループ =====
    extern const char* const SETTING_GROUP_MainWindow;
    extern const char* const SETTING_GROUP_CustomizeDialog;
    extern const char* const SETTING_GROUP_MessageWindow;
    extern const char* const SETTING_GROUP_ScrambleDialog;
    extern const char* const SETTING_GROUP_Settingsdialog;
    
    // ===== 拡張子 設定キー デフォルト値 =====
    extern const char* const KEY_AudioExtension;
    extern const char* const DEFAULT_AudioExtension;

    // ===== フォルダ設定キー =====
    extern const char* const KEY_SaveFolder;
    extern const char* const KEY_FfmpegFolder;
    
    // ===== 英語講座 設定キー =====
    extern const char* const KEY_basic0;
    extern const char* const KEY_basic1;
    extern const char* const KEY_basic2;
    extern const char* const KEY_timetrial;
    extern const char* const KEY_enjoy;
    extern const char* const KEY_kaiwa;
    extern const char* const KEY_business;
    extern const char* const KEY_gendai;
 
    // ===== フラグ 設定キー =====
    extern const char* const KEY_KOZA_SEPARATION;
    extern const char* const KEY_MULTI_GUI;
    extern const char* const KEY_NAME_SPACE;
    extern const char* const KEY_TAG_SPACE; 
    extern const char* const KEY_NOGUI;
    extern const char* const KEY_LAST_WEEK;
    extern const char* const KEY_BOTH_WEEKS;
    extern const char* const KEY_PROGRAM_LIST;
    
    // ===== FILE NAME、TITLE 設定キー =====
    extern const char* const KEY_CUSTOMIZED_TITLE1;
    extern const char* const KEY_CUSTOMIZED_TITLE2;
    extern const char* const KEY_CUSTOMIZED_FILENAME1;
    extern const char* const KEY_CUSTOMIZED_FILENAME2;
    
}

