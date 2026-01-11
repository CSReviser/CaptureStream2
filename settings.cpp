#include "settings.h"
#include <QSettings>

Settings::Settings()
{
    // optional / special の配列サイズを初期化
    optionalIds.resize(8);
    optionalFlags.resize(8);
    optionalTitles.resize(8);

    specialIds.resize(4);
    specialFlags.resize(4);
    specialTitles.resize(4);
}

void Settings::load()
{
    QSettings ini("settings.ini", QSettings::IniFormat);

    ini.beginGroup("MainWindow");

    audioExtension     = ini.value("audio_extension", "m4a").toString();
    ffmpegFolder       = ini.value("ffmpeg_folder").toString();
    saveFolder         = ini.value("save_folder").toString();

    skip              = ini.value("skip", false).toBool();
    thumbnail         = ini.value("thumbnail", false).toBool();
    tagSpace          = ini.value("tag_space", false).toBool();
    nameSpace         = ini.value("name_space", false).toBool();
    kozaSeparation    = ini.value("koza_separation", false).toBool();
    multiGui          = ini.value("multi_gui", false).toBool();
    thisWeek          = ini.value("this_week", false).toBool();
    timetrial         = ini.value("timetrial", false).toBool();
    detailedMessage   = ini.value("detailed_message", false).toBool();

    // basic 系
    basic0 = ini.value("basic0", false).toBool();
    basic1 = ini.value("basic1", false).toBool();
    basic2 = ini.value("basic2", false).toBool();
    business1 = ini.value("business1", false).toBool();
    enjoy = ini.value("enjoy", false).toBool();
    gendai = ini.value("gendai", false).toBool();
    kaiwa = ini.value("kaiwa", false).toBool();

    // optional（8 個）
    for (int i = 0; i < 8; i++) {
        optionalIds[i]    = ini.value(QString("optional%1").arg(i+1)).toString();
        optionalFlags[i]  = ini.value(QString("optional_%1").arg(i+1), false).toBool();
        optionalTitles[i] = ini.value(QString("opt_title%1").arg(i+1)).toByteArray();
    }

    // special（4 個）
    for (int i = 0; i < 4; i++) {
        specialIds[i]     = ini.value(QString("special%1").arg(i+1)).toString();
        specialFlags[i]   = ini.value(QString("special_%1").arg(i+1), false).toBool();
        specialTitles[i]  = ini.value(QString("spec_title%1").arg(i+1)).toByteArray();
    }

    // MainWindow geometry
    mainWindowGeometry = ini.value("geometry").toByteArray();

    ini.endGroup();

    // MessageWindow
    ini.beginGroup("MessageWindow");
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::save()
{
    QSettings ini("settings.ini", QSettings::IniFormat);

    ini.beginGroup("MainWindow");

    ini.setValue("audio_extension", audioExtension);
    ini.setValue("ffmpeg_folder", ffmpegFolder);
    ini.setValue("save_folder", saveFolder);

    ini.setValue("skip", skip);
    ini.setValue("thumbnail", thumbnail);
    ini.setValue("tag_space", tagSpace);
    ini.setValue("name_space", nameSpace);
    ini.setValue("koza_separation", kozaSeparation);
    ini.setValue("multi_gui", multiGui);
    ini.setValue("this_week", thisWeek);
    ini.setValue("timetrial", timetrial);
    ini.setValue("detailed_message", detailedMessage);

    ini.setValue("basic0", basic0);
    ini.setValue("basic1", basic1);
    ini.setValue("basic2", basic2);
    ini.setValue("business1", business1);
    ini.setValue("enjoy", enjoy);
    ini.setValue("gendai", gendai);
    ini.setValue("kaiwa", kaiwa);

    // optional（8 個）
    for (int i = 0; i < 8; i++) {
        ini.setValue(QString("optional%1").arg(i+1), optionalIds[i]);
        ini.setValue(QString("optional_%1").arg(i+1), optionalFlags[i]);
        ini.setValue(QString("opt_title%1").arg(i+1), optionalTitles[i]);
    }

    // special（4 個）
    for (int i = 0; i < 4; i++) {
        ini.setValue(QString("special%1").arg(i+1), specialIds[i]);
        ini.setValue(QString("special_%1").arg(i+1), specialFlags[i]);
        ini.setValue(QString("spec_title%1").arg(i+1), specialTitles[i]);
    }

    ini.setValue("geometry", mainWindowGeometry);

    ini.endGroup();

    ini.beginGroup("MessageWindow");
    ini.setValue("geometry", messageWindowGeometry);
    ini.endGroup();
}

void Settings::loadMainWindow()
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MainWindow");
    mainWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMainWindow(const QByteArray &geometry)
{
    mainWindowGeometry = geometry;
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MainWindow");
    ini.setValue("geometry", geometry);
    ini.endGroup();
}

void Settings::loadMessageWindow()
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MessageWindow");
    messageWindowGeometry = ini.value("geometry").toByteArray();
    ini.endGroup();
}

void Settings::saveMessageWindow(const QByteArray &geometry)
{
    messageWindowGeometry = geometry;
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.beginGroup("MessageWindow");
    ini.setValue("geometry", geometry);
    ini.endGroup();
}

// ===== 結合済みを返す関数 =====

QStringList Settings::allProgramIds() const
{
    return optionalIds + specialIds;
}

QVector<bool> Settings::allProgramFlags() const
{
    return optionalFlags + specialFlags;
}

QStringList Settings::allProgramTitles() const
{
    return optionalTitles + specialTitles;
}
