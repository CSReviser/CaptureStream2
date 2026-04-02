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
    extern const char* const KEY_KOZA_SEPARATION_ON;
    extern const char* const KEY_KOZA_SEPARATION_OFF;
    extern const char* const KEY_MULTI_GUI;
    extern const char* const KEY_NAME_SPACE;
    extern const char* const KEY_TAG_SPACE; 
    extern const char* const KEY_MAC_MENUBAR;
    extern const char* const KEY_NOGUI;
    extern const char* const KEY_LAST_WEEK;
    extern const char* const KEY_BOTH_WEEKS;
    extern const char* const KEY_PROGRAM_LIST;
    extern const char* const KEY_SKIP;
    extern const char* const KEY_THUMBNAIL;
    extern const char* const KEY_THUMBNAIL_ON;
    extern const char* const KEY_THUMBNAIL_OFF;	
    extern const char* const KEY_MESSAGE_ON;
    extern const char* const KEY_HELP;
    
    // ===== FILE NAME、TITLE 設定キー =====
    extern const char* const KEY_CUSTOMIZED_TITLE1;
    extern const char* const KEY_CUSTOMIZED_TITLE2;
    extern const char* const KEY_CUSTOMIZED_FILENAME1;
    extern const char* const KEY_CUSTOMIZED_FILENAME2;
    
}

