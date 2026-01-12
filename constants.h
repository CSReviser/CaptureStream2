/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2026 CSReviser Team

	This file is part of CaptureStream2, a recorder that supports HLS for 
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

#pragma once
#include <QString>
#include <QMap>

struct ProgramInfo {
    QString key;      // INI のキー名
    QString id;       // 番組ID（初期値）
    QString title;    // 表示タイトル（初期値）
    bool    enabled;  // enabled の初期値
};

namespace Constants {

    // ===== アプリ情報 =====
    const QString AppName = "CaptureStream2";
    const QString AppVersion = "2024/06/08";

    // ===== INI ファイル名 =====
    const QString IniFileName = "CaptureStream2.ini";

    // ===== 番組カテゴリの数 =====
    constexpr int EnglishCount = 8;
    constexpr int OptionalCount = 8;
    constexpr int SpecialCount  = 4;

    // ===== デフォルト値 =====
    const QString DefaultAudioExtension = "m4a";
    const QString DefaultSaveFolder     = "";  
    // 空文字 = 「未設定」扱い（GUI 初回起動で設定させる）

    // ===== 固定のタイトル（必要なら）=====
    // INI に保存されるタイトルとは別に、
    // アプリ内部で使う固定の対応表がある場合に使用
    inline const ProgramInfo EnglishPrograms[EnglishCount] = {
        {"basic0",    "eng_basic_1", "中学生の基礎英語1", false},
        {"basic1",    "eng_basic_2", "中学生の基礎英語2", false},
        {"basic2",    "eng_basic_3", "中高生の基礎英語 in English", false},
        {"business1", "eng_business","ラジオ英会話", false},
        {"enjoy",     "eng_enjoy",   "エンジョイ・シンプル・イングリッシュ", false}
    };

    inline const ProgramInfo DefaultOptional[OptionalCount] = {
        {"opt1", "まいにちフランス語"},
        {"opt2", "まいにちドイツ語"},
        {"opt3", "まいにちイタリア語"},
        {"opt4", "まいにちスペイン語"},
        {"opt5", "まいにちロシア語"},
        {"opt6", "ポルトガル語"},
        {"opt7", "まいにち中国語"},
        {"opt8", "まいにちハングル講座"}
    };

    inline const ProgramInfo DefaultSpec[SpecialCount] = {
        {"sp1", "やさしい日本語"},
        {"sp2", "アラビア語講座"},
        {"sp3", "Asian View"},
        {"sp4", "Living in Japan"}
    };


    const QMap<QString, QString> DefaultTitles = {
        {"optional1", "まいにちフランス語"},
        {"optional2", "まいにちドイツ語"},
        {"optional3", "まいにちイタリア語"},
        {"optional4", "まいにちスペイン語"},
        {"optional5", "まいにちロシア語"},
        {"optional6", "ポルトガル語"},
        {"optional7", "まいにち中国語"},
        {"optional8", "まいにちハングル講座"},
        {"special1", "やさしい日本語"},
        {"special2", "アラビア語講座"},
        {"special3", "Asian View"},
        {"special4", "Living in Japan"}
    };

    // ===== 固定の URL などがある場合はここに追加 =====
    // const QString BaseApiUrl = "https://example.com/api/";
}
