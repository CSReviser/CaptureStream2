// core/outputpathbuilder.cpp
#include "outputpathbuilder.h"
#include "legacyformatengine.h"
#include <QDir>

// =========================
// サニタイズ
// =========================

QString OutputPathBuilder::sanitize(const QString& s)
{
    QString out = s;

    static const QStringList illegalChars = {
        "/", "\\", ":", "*", "?", "\"",
        "<", ">", "|", "#", "{", "}",
        "%", "&", "~"
    };

    for (const auto& c : illegalChars) {
        out.replace(c, "_");
    }

    return out.trimmed();
}

// =========================
// サブフォルダ構築
// =========================

QString OutputPathBuilder::buildSubDir(
    const QString& format,
    const EpisodeInfo& ep)
{
    if (format.isEmpty())
        return "";

    LegacyFormatInput in;
    in.format = format;
    in.kouza  = ep.kouza;
    in.hdate  = ep.date.toString("MMdd");
    in.file   = ep.fileId;
    in.nendo  = ep.nendo;
    in.dupnmb = ep.dupnmb;
    in.checkIllegal = true;

    QString dir = LegacyFormatEngine::formatName(in);

    return sanitize(dir);
}

// =========================
// メイン
// =========================

QString OutputPathBuilder::buildSubDir(
    const QString& format,
    const EpisodeInfo& ep)
{
    // 🔥 XML特別処理
    if (ep.isXml) {
        QString dir =
            QString::fromUtf8("[前週]/") + ep.kouza;

        return sanitize(dir);
    }

    // 🔷 通常（JSON）
    if (format.isEmpty())
        return "";

    LegacyFormatInput in;
    in.format = format;
    in.kouza  = ep.kouza;
    in.hdate  = ep.date.toString("MMdd");
    in.file   = ep.fileId;
    in.nendo  = ep.nendo;
    in.dupnmb = ep.dupnmb;
    in.checkIllegal = true;

    QString dir = LegacyFormatEngine::formatName(in);

    return sanitize(dir);
}

/*
QString OutputPathBuilder::build(
    const OutputPathConfig& cfg,
    const QString& fileNameBase,
    const EpisodeInfo& ep)
{
    QString baseDir = cfg.rootDir;

    // 🔷 サブフォルダ
    QString subDir = buildSubDir(cfg.subDirFormat, ep);

    QString fullDir = baseDir;
    if (!subDir.isEmpty()) {
        fullDir = QDir(baseDir).filePath(subDir);
    }

    // 🔷 ファイル名
    QString fileName = sanitize(fileNameBase);

    // 🔷 拡張子
    QString ext = cfg.extension;
    if (!ext.startsWith(".")) {
        ext = "." + ext;
    }

    QString fullPath =
        QDir(fullDir).filePath(fileName + ext);

    return fullPath;
}
*/