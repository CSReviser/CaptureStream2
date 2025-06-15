#include "SettingsManager.h"

SettingsManager::SettingsManager()
    : settings("YourCompany", "CaptureStream2") // あるいは設定ファイルパス
{}

void SettingsManager::load() {
    saveFolder = settings.value(AppSettings::SETTING_SAVE_FOLDER, "").toString();
    ffmpegFolder = settings.value(AppSettings::SETTING_FFMPEG_FOLDER, "").toString();

    fileName1 = settings.value(AppSettings::SETTING_FILE_NAME1, AppSettings::FILE_NAME1).toString();
    fileName2 = settings.value(AppSettings::SETTING_FILE_NAME2, AppSettings::FILE_NAME2).toString();
    title1 = settings.value(AppSettings::SETTING_TITLE1, AppSettings::FILE_TITLE1).toString();
    title2 = settings.value(AppSettings::SETTING_TITLE2, AppSettings::FILE_TITLE2).toString();

    scrambleEnabled = settings.value(AppSettings::SETTING_SCRAMBLE, true).toBool();
    scrambleUrl1 = settings.value(AppSettings::SETTING_SCRAMBLE_URL1, AppSettings::SCRAMBLE_URL1).toString();

    kozaSeparation = settings.value(AppSettings::SETTING_KOZA_SEPARATION, AppSettings::KOZA_SEPARATION_FLAG).toBool();
    nameSpace = settings.value(AppSettings::SETTING_NAME_SPACE, AppSettings::NAME_SPACE_FLAG).toBool();
    tagSpace = settings.value(AppSettings::SETTING_TAG_SPACE, AppSettings::TAG_SPACE_FLAG).toBool();
    multiGui = settings.value(AppSettings::SETTING_MULTI_GUI, AppSettings::MULTI_GUI_FLAG).toBool();

    // オプショナル番組
    for (int i = 0; i < 10; ++i) {
        const QString key = AppSettings::SETTING_OPTIONAL_KEYS[i];
        QString id = settings.value(key, AppSettings::OPTIONAL_IDS[i]).toString();
        QString title = AppSettings::Program_TITLES[i];
        optionalIdMap[key] = id;
        optionalTitleMap[key] = title;
    }

    // 特別番組
    for (int i = 0; i < 4; ++i) {
        const QString key = AppSettings::SETTING_SPECIAL_KEYS[i];
        QString id = settings.value(key, AppSettings::SPECIAL_IDS[i]).toString();
        QString title = AppSettings::Special_TITLES[i];
        specialIdMap[key] = id;
        specialTitleMap[key] = title;
    }
}

void SettingsManager::save() {
    settings.setValue(AppSettings::SETTING_SAVE_FOLDER, saveFolder);
    settings.setValue(AppSettings::SETTING_FFMPEG_FOLDER, ffmpegFolder);

    settings.setValue(AppSettings::SETTING_FILE_NAME1, fileName1);
    settings.setValue(AppSettings::SETTING_FILE_NAME2, fileName2);
    settings.setValue(AppSettings::SETTING_TITLE1, title1);
    settings.setValue(AppSettings::SETTING_TITLE2, title2);

    settings.setValue(AppSettings::SETTING_SCRAMBLE, scrambleEnabled);
    settings.setValue(AppSettings::SETTING_SCRAMBLE_URL1, scrambleUrl1);

    settings.setValue(AppSettings::SETTING_KOZA_SEPARATION, kozaSeparation);
    settings.setValue(AppSettings::SETTING_NAME_SPACE, nameSpace);
    settings.setValue(AppSettings::SETTING_TAG_SPACE, tagSpace);
    settings.setValue(AppSettings::SETTING_MULTI_GUI, multiGui);

    for (int i = 0; i < 10; ++i) {
        const QString key = AppSettings::SETTING_OPTIONAL_KEYS[i];
        settings.setValue(key, optionalIdMap.value(key, AppSettings::OPTIONAL_IDS[i]));
    }

    for (int i = 0; i < 4; ++i) {
        const QString key = AppSettings::SETTING_SPECIAL_KEYS[i];
        settings.setValue(key, specialIdMap.value(key, AppSettings::SPECIAL_IDS[i]));
    }
}