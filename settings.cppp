#include "settings.h"

Settings::Settings(QObject* parent)
    : QObject(parent)
{
    m_optTitle.resize(8);
    m_specTitle.resize(4);
}

void Settings::load()
{
    QSettings s("settings.ini", QSettings::IniFormat);

    // General
    s.beginGroup("General");
    m_saveFolder = s.value("save_folder", "").toString();
    m_ffmpegFolder = s.value("ffmpeg_folder", "").toString();
    m_audioExtension = s.value("audio_extension", "m4a").toString();
    m_skip = s.value("skip", false).toBool();
    s.endGroup();

    // OptTitle
    s.beginGroup("OptTitle");
    for (int i = 0; i < m_optTitle.size(); ++i)
        m_optTitle[i] = s.value(QString("opt_title%1").arg(i + 1), "").toString();
    s.endGroup();

    // SpecTitle
    s.beginGroup("SpecTitle");
    for (int i = 0; i < m_specTitle.size(); ++i)
        m_specTitle[i] = s.value(QString("spec_title%1").arg(i + 1), "").toString();
    s.endGroup();
}

void Settings::save()
{
    QSettings s("settings.ini", QSettings::IniFormat);

    // General
    s.beginGroup("General");
    s.setValue("save_folder", m_saveFolder);
    s.setValue("ffmpeg_folder", m_ffmpegFolder);
    s.setValue("audio_extension", m_audioExtension);
    s.setValue("skip", m_skip);
    s.endGroup();

    // OptTitle
    s.beginGroup("OptTitle");
    for (int i = 0; i < m_optTitle.size(); ++i)
        s.setValue(QString("opt_title%1").arg(i + 1), m_optTitle[i]);
    s.endGroup();

    // SpecTitle
    s.beginGroup("SpecTitle");
    for (int i = 0; i < m_specTitle.size(); ++i)
        s.setValue(QString("spec_title%1").arg(i + 1), m_specTitle[i]);
    s.endGroup();
}

void Settings::loadMainWindow()
{
    QSettings s("settings.ini", QSettings::IniFormat);
    s.beginGroup("MainWindow");
    m_mainGeometry = s.value("geometry").toByteArray();
    s.endGroup();
}

void Settings::saveMainWindow()
{
    QSettings s("settings.ini", QSettings::IniFormat);
    s.beginGroup("MainWindow");
    s.setValue("geometry", m_mainGeometry);
    s.endGroup();
}

void Settings::loadMessageWindow()
{
    QSettings s("settings.ini", QSettings::IniFormat);
    s.beginGroup("MessageWindow");
    m_messageGeometry = s.value("geometry").toByteArray();
    s.endGroup();
}

void Settings::saveMessageWindow()
{
    QSettings s("settings.ini", QSettings::IniFormat);
    s.beginGroup("MessageWindow");
    s.setValue("geometry", m_messageGeometry);
    s.endGroup();
}
