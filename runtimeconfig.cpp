#include "runtimeconfig.h"
#include "constants.h"

RuntimeConfig::RuntimeConfig()
{
    // 何もせず applySettings() に任せる
}

void RuntimeConfig::applySettings(const Settings &s)
{
    // ===== English（固定：id/title は Constants、enabled は Settings）=====
    for (int i = 0; i < Constants::EnglishCount; i++) {
        const auto &def = Constants::EnglishPrograms[i];
        const QString &key = def.key;

        english[i].id      = def.id;
        english[i].title   = def.title;
        english[i].enabled = s.englishEnabled.value(key, def.enabled);
    }

    // ===== Optional（editable：id/title/enabled は Settings）=====
    for (int i = 0; i < Constants::OptionalCount; i++) {
        const auto &p = Constants::OptionalPrograms[i];

        optional[i].enabled = s.optionalEnabled.value(p.keyEnabled, p.enabledDefault);
        optional[i].id      = s.optionalId.value(p.keyId, p.idDefault);
        optional[i].title   = s.optionalTitle.value(p.keyTitle, p.titleDefault);
    }

    // ===== Spec（editable）=====
    for (int i = 0; i < Constants::SpecialCount; i++) {
        const auto &p = Constants::SpecPrograms[i];

        spec[i].enabled = s.specEnabled.value(p.keyEnabled, p.enabledDefault);
        spec[i].id      = s.specId.value(p.keyId, p.idDefault);
        spec[i].title   = s.specTitle.value(p.keyTitle, p.titleDefault);
    }

    // ===== CheckBox =====
    for (int i = 0; i < Constants::CheckBoxCount; i++) {
        const auto &c = Constants::checkBoxes[i];
        checkBox[i] = s.checkBoxEnabled.value(c.keyEnabled, c.enabledDefault);
    }

    // ===== その他設定 =====
    saveFolder     = s.saveFolder;
    audioExtension = s.audioExtension;
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

        // English
        for (int i = 0; i < Constants::EnglishCount; i++) {
            if (Constants::EnglishPrograms[i].key == key) {
                english[i].enabled = false;
            }
        }

        // Optional
        for (int i = 0; i < Constants::OptionalCount; i++) {
            if (Constants::OptionalPrograms[i].keyEnabled == key) {
                optional[i].enabled = false;
            }
        }

        // Spec
        for (int i = 0; i < Constants::SpecialCount; i++) {
            if (Constants::SpecPrograms[i].keyEnabled == key) {
                spec[i].enabled = false;
            }
        }
    }
}
