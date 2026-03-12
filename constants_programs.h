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

// constants_programs.h
#pragma once
#include <QString>
#include <QMap>
#include <QMultiMap>
#include <QStringList>

namespace Constants {

struct ProgramDefinition {
    enum class Kind { English, Optional, Spec, Feature };
    Kind kind;
    const char* keyChecked;
    bool checkedDefault;
    const char* keyId;
    const char* idDefault;
    bool saveId;
    bool hasId; 
    const char* keyLabel;
    const char* labelDefault;
    bool saveLabel;
    bool hasLabel; 
    const char* objectName;
};

// --- 配列の宣言（実体は.cpp） ---
extern const ProgramDefinition EnglishPrograms[];
extern const int EnglishCount;

extern const ProgramDefinition OptionalPrograms[];
extern const int OptionalCount;

extern const ProgramDefinition SpecPrograms[];
extern const int SpecCount;

extern const  char* AUDIO_EXT_LIST[];
extern const int AUDIO_EXT_COUNT;

// --- コンテナ系の取得関数 ---
const QMap<QString, QString>& getMap();
const QMultiMap<QString, QString>& getMultiMap();
const QMultiMap<QString, QString>& getMultiMap1();
const std::vector<QStringList>& getOptPresets();
const std::vector<QStringList>& getPresets();


// --- その他の構造体 ---
struct Item { const QString key; const char* defaultValue; };
extern const Item TITLE_ITEMS[];
extern const Item FILENAME_ITEMS[];
extern const int ITEM_COUNT;

struct CustomizePreset { const char* value; const char* label; };
extern const CustomizePreset FILENAME_PRESETS[];
extern const int FILENAME_PRESET_COUNT;
extern const CustomizePreset TITLE_PRESETS[];
extern const int TITLE_PRESETS_COUNT;

// 固定文字列は利便性のため inline のまま維持（変更頻度が低いため）
inline constexpr auto prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
inline constexpr auto suffix = "listdataflv.xml";
inline constexpr auto json_prefix = "https://www.nhk.or.jp/radioondemand/json/";



    // --- 実体配列の参照宣言 ---
    extern const ProgramDefinition EnglishPrograms[];
    extern const ProgramDefinition OptionalPrograms[];
    extern const ProgramDefinition SpecPrograms[];

    // --- 【重要】個数を自動で返す関数 ---
    int getEnglishCount();
    int getOptionalCount();
    int getSpecCount();
    int getItemCount();
    int getAudioExtCount();
    
    // std::array の代わりに使う側のための別名（セマンティクス維持）
    int getOptPresetSize();
    int getPresetSize();
//    inline int getOptPresetSize() { return getOptionalCount(); }
//    inline int getPresetSize() { return getSpecCount(); }

} // namespace Constants



