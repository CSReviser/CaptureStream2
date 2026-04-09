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

#include "utility.h"
#include "urldownloader.h"
#include "mainwindow.h"
#include "constants.h"
#include "settings.h"
#include "recordingcore.h"
#include "programrepository.h"

#include <QRegularExpression>
#include <QUrl>
#include <QCoreApplication>
#include <QDir>
#include <QTemporaryFile>
#include <QProcess>
#include <QFileInfo>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMap>
#include <QLockFile>
#include <QTimer>
#include <QElapsedTimer>
#include <QSettings>

#define SETTING_MULTI_GUI "multi_gui"
#define MULTI_GUI_FLAG false
namespace {
	const QString UPUPUP( "/../../.." );
	const QString FLARE( "flare" );
	const QString GNASH( "gnash" );
	const QString GNASH_arguments { "-r0 -v http://www.nhk.or.jp/gogaku/common/swf/streaming.swf" };
	const QUrl STREAMINGSWF( "http://www.nhk.or.jp/gogaku/common/swf/streaming.swf" );
	const QString TEMPLATE( "streamingXXXXXX.swf" );

	const QRegularExpression REGEXP( "function startInit\\(\\) \\{[^}]*\\}\\s*function (\\w*).*startInit\\(\\);" );
	const QRegularExpression PREFIX( "load\\('([A-Z0-9]*)' \\+ CONNECT_DIRECTORY" );
	const QRegularExpression SUFFIX( "CONNECT_DIRECTORY \\+ '(.*)/' \\+ INIT_URI" );

	const QString LISTDATAFLV( "http://www.nhk.or.jp/gogaku/common/swf/(\\w+)/listdataflv.xml" );
        const QString WIKIXML1( "doc('" );
        const QString WIKIXML2( "')/flv/scramble[@date=\"" );
	const QString WIKIXML3( "\"]/@code/string()" );
	const QString APPNAME( "CaptureStream2" );
	const QString lockFilePath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/CaptureStream2.lock";
        static QLockFile lockFile(lockFilePath);
	QTimer* removeTimer = nullptr;
	QElapsedTimer elapsed;
	const int maxWaitMs = 3000;
	const int retryIntervalMs = 100;

QDate nendo_start_date = RecordingCore::nendo_start_date1;
QDate zenki_end_date = RecordingCore::zenki_end_date;
QDate kouki_start_date = RecordingCore::kouki_start_date;
QDate nendo_end_date = RecordingCore::nendo_end_date;

QMap<QString, QString> koza_unkown = { 
	{ "XQ487ZM61K_x1", "まいにちフランス語【入門/初級編】" },	// まいにちフランス語 入門編
	{ "XQ487ZM61K_y1", "まいにちフランス語【応用編】" },		// まいにちフランス語 応用編
	{ "N8PZRZ9WQY_x1", "まいにちドイツ語【入門/初級編】" },		// まいにちドイツ語 入門編
	{ "N8PZRZ9WQY_y1", "まいにちドイツ語【応用編】" },		// まいにちドイツ語 応用編
	{ "NRZWXVGQ19_x1", "まいにちスペイン語【入門/初級編】" },	// まいにちスペイン語 入門編
	{ "NRZWXVGQ19_y1", "まいにちスペイン語【中級/応用編】" },	// まいにちスペイン語 応用編
	{ "LJWZP7XVMX_x1", "まいにちイタリア語【入門/初級編】" },	// まいにちイタリア語 入門編
	{ "LJWZP7XVMX_y1", "まいにちイタリア語【応用編】" },		// まいにちイタリア語 応用編
	{ "YRLK72JZ7Q_x1", "まいにちロシア語【入門/初級編】" },		// まいにちロシア語 入門編
	{ "YRLK72JZ7Q_y1", "まいにちロシア語【応用編】" },		// まいにちロシア語 応用編
};	
}

// Macの場合はアプリケーションバンドル、それ以外はアプリケーションが含まれるディレクトリを返す
QString Utility::applicationBundlePath() {

#ifdef Q_OS_LINUX
    QString basePath;
    // AppImage 環境変数が存在すれば AppImage 実行中
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty()) {
        // AppImage 実行：本体のある場所を保存先とする
        QFileInfo fi(appImagePath);
        basePath = fi.absolutePath();
	basePath += QDir::separator();
        return basePath;
    } 
 #endif
    
	QString result = QCoreApplication::applicationDirPath();
//#ifdef Q_OS_MACOS				//Macのffmpegパス不正対策　2022/04/13
//	result = QDir::cleanPath( result + UPUPUP );
//#endif
	result += QDir::separator();
	return result;
}

QString Utility::getSettingsPath() {
    QString basePath;

    // AppImage 環境変数が存在すれば AppImage 実行中
    QString appImagePath = qgetenv("APPIMAGE");
    if (!appImagePath.isEmpty()) {
        // AppImage 実行：本体のある場所を保存先とする
        QFileInfo fi(appImagePath);
        basePath = fi.absolutePath();
        qDebug() << "Running from AppImage, using path:" << basePath;
    } else {
        // 通常実行：バイナリの場所を保存先とする
        QFileInfo fi(QCoreApplication::applicationFilePath());
        basePath = fi.absolutePath();
        qDebug() << "Running from normal binary, using path:" << basePath;
    }

    // 保存先ファイル名
    return basePath + "/capturestream2.ini";
}

QString Utility::appLocaldataLocationPath() {
	QString result = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/";
	result += QDir::separator();
	return result;
}

QString Utility::appConfigLocationPath() {
	QString result = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/";
	result += QDir::separator();
	return result;
}

QString Utility::ConfigLocationPath() {
	QString result = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/";
	result += QDir::separator();
	return result;
}

QString Utility::DownloadLocationPath() {
	QString result = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "/";
	result += QDir::separator();
	return result;
}

QString Utility::HomeLocationPath() {
	QString result = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/" + APPNAME + "/";
	result += QDir::separator();
	return result;
}

std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList, QStringList>
Utility::getJsonData1(const QString& strReply, int json_ohyo) {
    QStringList fileList, kouzaList, file_titleList, hdateList, yearList, contentsIdList;

    if (strReply == "error") return { fileList, kouzaList, file_titleList, hdateList, yearList, contentsIdList };

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !jsonDoc.isObject())
        return { fileList, kouzaList, file_titleList, hdateList, yearList, contentsIdList };

    QJsonObject jsonObj = jsonDoc.object();
    QString programName = jsonObj.value("title").toString().replace("　", " ");
    QString cornerName = jsonObj.value("corner_name").toString().replace("　", " ");

    if (!cornerName.isEmpty()) {
        cornerName.remove("を聴く");
        if (cornerName.contains("曜日放送") || cornerName.contains("曜放送") || cornerName.contains("特集")) {
            programName += " - " + cornerName;
        } else {
            programName = cornerName;
        }
    }

    // 半角化：記号
    for (ushort i = 0xFF1A; i < 0xFF5F; ++i)
        programName.replace(QChar(i), QChar(i - 0xFEE0));
    // 半角化：数字
    for (ushort i = 0xFF10; i < 0xFF1A; ++i)
        programName.replace(QChar(i - 0xFEE0), QChar(i));

    QJsonArray episodes = jsonObj.value("episodes").toArray();
    if (episodes.isEmpty()) {
        QStringList emptyList = { "\0" };
        kouzaList.append(programName);
        return { emptyList, kouzaList, emptyList, emptyList, emptyList, emptyList };
    }

    static const QRegularExpression dateRx(R"(\d{4}-\d{2}-\d{2})");

    for (const auto& val : episodes) {
        QJsonObject obj = val.toObject();

        QString fileTitle = obj.value("program_title").toString();
        QString fileName = obj.value("stream_url").toString();
        QString contentsId = obj.value("aa_contents_id").toString();
        QString onairDate = obj.value("onair_date").toString();
        QString year = dateRx.match(contentsId).captured(0).left(4);

        if ((json_ohyo == 1 && (fileTitle.contains("中級編") || fileTitle.contains("応用編"))) ||
            (json_ohyo == 2 && (fileTitle.contains("入門編") || fileTitle.contains("初級編")))) {
            continue;
        }

        QString nameTmp = programName;
        auto &s = Settings::instance();
        if (Settings::nameSpaceFlag()) {
            if (json_ohyo == 1 && fileTitle.contains("入門編")) nameTmp += "【入門編】";
            if (json_ohyo == 1 && fileTitle.contains("初級編")) nameTmp += "【初級編】";
            if (json_ohyo == 2 && fileTitle.contains("中級編")) nameTmp += "【中級編】";
            if (json_ohyo == 2 && fileTitle.contains("応用編")) nameTmp += "【応用編】";
        } else {
            if (json_ohyo == 1 && fileTitle.contains("入門編")) nameTmp += " 入門編";
            if (json_ohyo == 1 && fileTitle.contains("初級編")) nameTmp += " 初級編";
            if (json_ohyo == 2 && fileTitle.contains("中級編")) nameTmp += " 中級編";
            if (json_ohyo == 2 && fileTitle.contains("応用編")) nameTmp += " 応用編";
        }

        kouzaList.append(nameTmp);
        file_titleList.append(fileTitle);
        fileList.append(fileName);
        hdateList.append(onairDate);
        yearList.append(year);
        contentsIdList.append(contentsId);
    }

    return { fileList, kouzaList, file_titleList, hdateList, yearList, contentsIdList };
}

QString Utility::parseLatestVersion(const QByteArray& json)
{
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    return obj["tag_name"].toString();
}

QString Utility::getLatest_version(NetworkClient& client)
{
    const QString url =
        "https://api.github.com/repos/CSReviser/CaptureStream2/releases/latest";

    int timer = 100;

    for (int i = 0; i < 20; ++i) {

        QByteArray res = client.getSync(QUrl(url), timer, 1);

        if (!res.isEmpty()) {
            QJsonDocument json = QJsonDocument::fromJson(res);
            QJsonObject obj = json.object();
            return obj["tag_name"].toString();
        }

        if (timer < 500) timer += 50;
        else if (timer < 5000) timer += 100;
    }

    return QString();
}

bool Utility::nogui() {
	bool nogui_flag = QCoreApplication::arguments().contains( "-nogui" );
	return nogui_flag;
}

bool Utility::gui() {
	bool nogui_flag = QCoreApplication::arguments().contains( "-nogui" );
	bool gui_flag = QCoreApplication::arguments().contains( "-gui" ) && !nogui_flag;
	return gui_flag;
}

bool Utility::option_check( QString option ) {
	bool option_flag = ( QCoreApplication::arguments().contains( option ) && QCoreApplication::arguments().contains( "-nogui" ) );
	return option_flag;
}

QStringList Utility::optionList() {
	QStringList attribute;
	QStringList ProgList = QCoreApplication::arguments();
	int ccc = 3;
	if ( Utility::option_check( "-z" ) || Utility::option_check( "-b" ) ) ccc = 4;
	if ( ProgList.count() < ccc ) { attribute += "erorr" ; return attribute; }
	ProgList.removeAt(0);
	// ★ 番組一覧の初期化（非同期）
	auto &repo = ProgramRepository::instance();
	QStringList idList = repo.id_map.keys();;
//	QStringList titleList;
//	std::tie( idList, titleList ) = Utility::getProgram_List();

	if( Utility::nogui() ) {
		for( int i = 0; i < ProgList.count() ; i++ ){
			if ( koza_unkown.contains( ProgList[i] ) ) { attribute += ProgList[i]; continue; }
			if ( idList.contains( ProgList[i] ) ) attribute += ProgList[i];
		}
		if ( attribute.count() < 1 ) attribute += "return" ;
	}
	return attribute;
}

std::tuple<QString, QString, QString, QString> Utility::nogui_option( QString titleFormat, QString fileNameFormat, QString outputDir, QString extension ) {
	QString titleFormat_out = titleFormat;
	QString fileNameFormat_out = fileNameFormat;
	QString outputDir_out = outputDir;
	QString extension_out = extension;
	QStringList optionList = QCoreApplication::arguments();
	optionList.removeAt(0);

	if ( optionList.contains( "-t" ) ) { titleFormat_out = optionList[ optionList.indexOf( "-t" ) + 1 ].remove( "'" ).remove( "\"" );}
	if ( optionList.contains( "-f" ) ) { fileNameFormat_out = optionList[ optionList.indexOf( "-f" ) + 1 ].remove( "'" ).remove( "\"" );}
	if ( optionList.contains( "-o" ) ) { outputDir_out = optionList[ optionList.indexOf( "-o" ) + 1 ].remove( "'" ).remove( "\"" ) + QDir::separator();}
	if ( optionList.contains( "-e" ) ) { extension_out = optionList[ optionList.indexOf( "-e" ) + 1 ].remove( "'" ).remove( "\"" ); if (extension_out == "mp3") extension_out += "-64k-S"; }

	return { titleFormat_out, fileNameFormat_out, outputDir_out, extension_out };
}

bool Utility::tryLockFile() {
	lockFile.setStaleLockTime(30000);
//	if(multi_gui_flag_check()) return true;
	return lockFile.tryLock();
}

void Utility::unLockFile() {
	lockFile.unlock();
	return;
}

void Utility::remove_LockFile() {
	QString lockFilePath2 = QFileInfo(lockFilePath).absoluteFilePath();
	lockFile.removeStaleLockFile();
	lockFile.unlock();
	QFile::remove(lockFilePath2);
	return;
}

bool Utility::multi_gui_flag_check() {
	if( Utility::nogui() || Utility::gui() ) return 1;
	auto &s = Settings::instance();
	QVariant saved = s.checked[QString::fromUtf8(Constants::KEY_MULTI_GUI)];
	bool multi_gui_flag = !saved.isValid() ? MULTI_GUI_FLAG : saved.toBool();
	if(multi_gui_flag) 
		return true;
	else 
		return false;		
}

QString Utility::loadFirstExistingTextFile(const QStringList& paths)
{
    for (const QString& path : paths) {
        QFile f(path);
        if (f.open(QFile::ReadOnly))
            return QString::fromUtf8(f.readAll());
    }
    return {};
}

QString Utility::findFirstExistingFile(const QStringList& paths)
{
    for (const QString& path : paths) {
        if (QFile::exists(path))
            return path;
    }
    return {};
}

QString Utility::loadTextFile(const QString& path)
{
    QFile f(path);
    if (!f.open(QFile::ReadOnly))
        return {};
    return QString::fromUtf8(f.readAll());
}

