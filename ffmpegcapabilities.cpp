#include "ffmpegcapabilities.h"
#include <QProcess>

FfmpegCapabilities FfmpegCapabilities::detect(const QString& ffmpegPath)
{
    FfmpegCapabilities caps;

    QProcess process;
    process.setProgram(ffmpegPath);

    process.setArguments({
    	"-http_seekable", "0", "-version", "0"
/*
        "-http_seekable", "0",
        "-f", "lavfi",
        "-i", "anullsrc",
        "-t", "0.1",
        "-f", "null",
        "-"
*/  
    });

    process.start();
    process.waitForFinished();

    QString err = process.readAllStandardError();

//    if (!err.contains("Option not found", Qt::CaseInsensitive) &&
//        !err.contains("Unrecognized option", Qt::CaseInsensitive))
    if (!err.contains("Option not found", Qt::CaseInsensitive) )
    {
        caps.httpSeekableSupported = true;
    }

    return caps;
}
