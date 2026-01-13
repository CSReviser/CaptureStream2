#include "runtimeconfig.h"

RuntimeConfig::RuntimeConfig()
{
    // 何もせず applySettings() に任せる
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English（固定：id/title は Constants、enabled は Settings）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];

        english[i].id      = def.id;
        english[i].title   = def.title;
        english[i].enabled = s.englishEnabled[i];
    }

    // ===== Optional（editable：id/title/enabled は Settings）=====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        optional[i].id      = s.optionalId[i];
        optional[i].title   = s.optionalTitle[i];
        optional[i].enabled = s.optionalEnabled[i];
    }

    // ===== Spec（editable）=====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        spec[i].id      = s.specId[i];
        spec[i].title   = s.specTitle[i];
        spec[i].enabled = s.specEnabled[i];
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        checkBox[i] = s.checkBoxEnabled[i];
    }

    // ===== その他設定 =====
    saveFolder     = Constants::DefaultSaveFolder;
    audioExtension = Constants::DefaultAudioExtension;
}

void RuntimeConfig::applyCommandLine(const QMap<QString, QString> &opts)
{
    // 例: --save-folder=/path/to/dir
    if (opts.contains("save-folder")) {
        saveFolder = opts["save-folder"];
    }

    // 例: --audio-ext=m4a
    if (opts.contains("audio-ext")) {
        audioExtension = opts["audio-ext"];
    }

    // 例: --enable=optional3
    if (opts.contains("enable")) {
        QString key = opts["enable"];

        // English
        for (int i = 0; i < Constants::EnglishCount; i++) {
            if (Constants::EnglishPrograms[i].key == key) {
                english[i].enabled = true;
            }
        }

        // Optional
        for (int i = 0; i < Constants::OptionalCount; i++) {
            if (Constants::OptionalPrograms[i].keyEnabled == key) {
                optional[i].enabled = true;
            }
        }

        // Spec
        for (int i = 0; i < Constants::SpecialCount; i++) {
            if (Constants::SpecPrograms[i].keyEnabled == key) {
                spec[i].enabled = true;
            }
        }
    }

    // 例: --disable=optional3
    if (opts.contains("disable")) {
        QString key = opts["disable"];

        for (int i = 0; i < Constants::EnglishCount; i++) {
            if (Constants::EnglishPrograms[i].key == key) {
                english[i].enabled = false;
            }
        }

        for (int i = 0; i < Constants::OptionalCount; i++) {
            if (Constants::OptionalPrograms[i].keyEnabled == key) {
                optional[i].enabled = false;
            }
        }

        for (int i = 0; i < Constants::SpecialCount; i++) {
            if (Constants::SpecPrograms[i].keyEnabled == key) {
                spec[i].enabled = false;
            }
        }
    }
}
