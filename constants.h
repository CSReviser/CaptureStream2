#pragma once
#include <QString>
#include <QMap>

namespace Constants {

    // ===== 番組カテゴリの数 =====
    constexpr int OptionalCount = 8;
    constexpr int SpecialCount  = 4;

    // ===== デフォルト値 =====
    const QString DefaultAudioExtension = "m4a";
    const QString DefaultSaveFolder     = "output";

    // ===== アプリ情報 =====
    const QString AppName = "CaptureStream2";

    // ===== 固定のタイトル（必要なら）=====
    // INI に保存されるタイトルとは別に、
    // アプリ内部で使う固定の対応表がある場合に使用
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
