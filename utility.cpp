/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2025 CSReviser Team

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
#include "downloadthread.h"
#include "qt4qt5.h"

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
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMap>
#include <QLockFile>
#include <QTimer>
#include <QElapsedTimer>

#define SETTING_GROUP "MainWindow"
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

QDate nendo_start_date = DownloadThread::nendo_start_date1;
QDate zenki_end_date = DownloadThread::zenki_end_date;
QDate kouki_start_date = DownloadThread::kouki_start_date;
QDate nendo_end_date = DownloadThread::nendo_end_date;

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
	QString result = QCoreApplication::applicationDirPath();
//#ifdef Q_OS_MACOS				//Macのffmpegパス不正対策　2022/04/13
//	result = QDir::cleanPath( result + UPUPUP );
//#endif
	result += QDir::separator();
	return result;
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

std::tuple<QStringList, QStringList> Utility::getProgram_List( ) {
	QStringList idList; 		idList.clear() ;
	QStringList titleList; 		titleList.clear() ;
		
	const QString jsonUrl1 = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/corners/new_arrivals";

	QString strReply;
	int flag = 0;
	int TimerMin = 100;
	int TimerMax = 5000;
	int Timer = TimerMin;
	int retry = 20;
	for ( int i = 0 ; i < retry ; i++ ) {
		strReply = Utility::getJsonFile( jsonUrl1, Timer );
		if ( strReply != "error" )  {
			flag = 1; break;
		}
		if ( Timer < 500 ) Timer += 50;
		if ( Timer > 500 && Timer < TimerMax ) Timer += 100;
	}
	
	switch ( flag ) {
	case 0: idList += "error"; titleList += "error"; break;
	case 1: std::tie( idList, titleList ) = Utility::getProgram_List1( strReply ); break;
//	case 2: std::tie( idList, titleList ) = Utility::getProgram_List2( strReply ); break;
	default: idList += "error"; titleList += "error"; break;
	}
	return { idList, titleList };
}


std::tuple<QStringList, QStringList> Utility::getProgram_List1( QString strReply ) {
	QStringList attribute1; 	attribute1.clear() ;
	QStringList attribute2; 	attribute2.clear() ;
	
	QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();
    
	QJsonArray jsonArray = jsonObject[ "corners" ].toArray();
	for (const auto&& value : jsonArray) {
		QJsonObject objxx = value.toObject();
		QString title = objxx[ "title" ].toString();
		QString corner_name = objxx[ "corner_name" ].toString();
		QString series_site_id = objxx[ "series_site_id" ].toString();
		QString corner_site = objxx[ "corner_site_id" ].toString();
		
		QString program_name = Utility::getProgram_name3( title, corner_name );
			
		QString url_id = series_site_id + "_" + corner_site;
			
		attribute1 += url_id;
		attribute2 += program_name;
	}
	return { attribute1, attribute2 };
}

QString Utility::getJsonFile(QString jsonUrl, int Timer) {
    QEventLoop eventLoop;
    QString attribute;
    QTimer timer;
    timer.setSingleShot(true);
    QNetworkAccessManager mgr;

    // Qt5 / Qt6 両対応のシグナル接続
    QObject::connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    QObject::connect(&mgr, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

    QUrl url_json(jsonUrl);
    QNetworkRequest req(url_json);
    QNetworkReply *reply = mgr.get(req);
    
    timer.start(Timer);  // ミリ秒指定
    eventLoop.exec(); // シグナルを待つ

    if (timer.isActive()) {
        timer.stop();

        if (reply->error() == QNetworkReply::NoError) {
            attribute = reply->readAll();
        } else {
            attribute = "error";
        }
    } else {
        // タイムアウト処理
        reply->abort();
        attribute = "error";
    }

    reply->deleteLater(); // メモリ管理を適切に
    return attribute;
}

QString Utility::getProgram_name( QString url ) {
	QString attribute;	QString title;	QString corner_name;
	attribute.clear() ;

	QString url_tmp = url;
	QString pattern( "[A-Z0-9][0-9]{3}|[A-Z0-9]{10}" );
    	pattern = QRegularExpression::anchoredPattern(pattern);
 	QString pattern2( "[A-Z0-9][0-9]{3}_[sxy0-9][0-9]|[A-Z0-9]{10}_[sxy0-9][0-9]" );
    	if ( QRegularExpression(pattern).match( url ).hasMatch() ) url += "_01";
    	
//	QString pattern( "[A-Z0-9]{4}_[0-9]{2}" );
//    	pattern = QRegularExpression::anchoredPattern(pattern);
// 	QString pattern2( "[A-Z0-9]{10}_[0-9]{2}" );
//     	if ( url.right(3) != "_01" ) url += "_01";

	if ( MainWindow::id_map.contains( url ) ) return MainWindow::id_map.value( url );

	int l = 10 ;				int l_length = url.length();
	if ( l_length != 13 ) l = l_length -3 ;
    	
//    	if ( !(QRegularExpression(pattern).match( url ).hasMatch()) && !(QRegularExpression(pattern2).match( url ).hasMatch()) ) return attribute;
	
 	const QString jsonUrl1 = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" + url.left( l ) + "&corner_site_id=" + url.right(2);

	QString strReply;
	int flag = 0;
	int TimerMin = 100;
	int TimerMax = 5000;
	int Timer = TimerMin;
	int retry = 20;
	for ( int i = 0 ; i < retry ; i++ ) {
		strReply = Utility::getJsonFile( jsonUrl1, Timer );
		if ( strReply != "error" )  {
			flag = 1; break;
		}
//		strReply = Utility::getJsonFile( jsonUrl2, Timer );
//		if ( strReply != "error" )  {
//			flag = 2; break;
//		}
		if ( Timer < 500 ) Timer += 50;
		if ( Timer > 500 && Timer < TimerMax ) Timer += 100;
	}
	
	switch ( flag ) {
	case 0: return attribute;
	case 1: std::tie( title, corner_name ) = Utility::getProgram_name1( strReply ); break;
	default: return attribute;
	}
	attribute = Utility::getProgram_name3( title, corner_name );
	return attribute;
}

std::tuple<QString, QString> Utility::getProgram_name1( QString strReply ) {
	QString attribute;
	attribute.clear() ;
	
	QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();
	attribute = jsonObject[ "title" ].toString().replace( "　", " " );
	QString corner_name = jsonObject[ "corner_name" ].toString().remove( "を聴く" ).replace( "　", " " );
	return { attribute, corner_name };
}

QString Utility::getProgram_name3( QString title, QString corner_name ) {
	QString attribute = title.replace( "　", " " );
		
	if ( !(corner_name.isNull()  || corner_name.isEmpty()) ) {
		if( corner_name.contains( "曜日放送", Qt::CaseInsensitive ) || corner_name.contains( "曜放送", Qt::CaseInsensitive ) || corner_name.contains( "特集", Qt::CaseInsensitive )){
			attribute = title + "-" + corner_name;
		} else {
			attribute = corner_name;
		}
	}
	for (ushort i = 0xFF1A; i < 0xFF5F; ++i) {
		attribute = attribute.replace(QChar(i), QChar(i - 0xFEE0));
	}
	for (ushort i = 0xFF10; i < 0xFF1A; ++i) {
		attribute = attribute.replace( QChar(i - 0xFEE0), QChar(i) );
	}

	attribute = attribute.remove( "【らじる文庫】" ).remove( "より" ).remove( "カルチャーラジオ " ).remove( "【恋する朗読】" ).remove( "【ラジオことはじめ】" ).remove( "【生朗読！】" );
        attribute.replace( QString::fromUtf8( "初級編" ), QString::fromUtf8( "【初級編】" ) ); attribute.replace( QString::fromUtf8( "入門編" ), QString::fromUtf8( "【入門編】" ) );
        attribute.replace( QString::fromUtf8( "中級編" ), QString::fromUtf8( "【中級編】" ) ); attribute.replace( QString::fromUtf8( "応用編" ), QString::fromUtf8( "【応用編】" ) );
	return attribute;
}


std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList>
Utility::getJsonData1(const QString& strReply, int json_ohyo) {
    QStringList fileList, kouzaList, file_titleList, hdateList, yearList;

    if (strReply == "error") return { fileList, kouzaList, file_titleList, hdateList, yearList };

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(strReply.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !jsonDoc.isObject())
        return { fileList, kouzaList, file_titleList, hdateList, yearList };

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
        return { emptyList, kouzaList, emptyList, emptyList, emptyList };
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
        if (MainWindow::name_space_flag) {
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
    }

    return { fileList, kouzaList, file_titleList, hdateList, yearList };
}

QString Utility::getLatest_version() {
	QString attribute;
	attribute.clear();
	
 	const QString jsonUrl = "https://api.github.com/repos/CSReviser/CaptureStream2/releases/latest";

	QString strReply;
	int TimerMin = 100;
	int TimerMax = 5000;
	int Timer = TimerMin;
	int retry = 20;
	for ( int i = 0 ; i < retry ; i++ ) {
		strReply = Utility::getJsonFile( jsonUrl, Timer );
		if ( strReply != "error" ) break;
		if ( Timer < 500 ) Timer += 50;
		if ( Timer > 500 && Timer < TimerMax ) Timer += 100;
	}
	
	QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();
	attribute = jsonObject[ "tag_name" ].toString();
	return attribute;
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
	QStringList idList = MainWindow::id_map.keys();;
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
	lockFile.setStaleLockTime(100);
	if(multi_gui_flag_check()) return true;
	return lockFile.tryLock();
}

void Utility::unLockFile() {
	lockFile.unlock();
	return;
}

void Utility::remove_LockFile() {
	lockFile.unlock();
	QString lockFilePath2 = QFileInfo(lockFilePath).absoluteFilePath();
	lockFile.removeStaleLockFile();
//	lockFile.setPermissions(QFile::WriteOwner | QFile::ReadOwner);
	QFile::remove(lockFilePath2);
	QFile::remove(lockFile.fileName());
	return;
}

bool Utility::multi_gui_flag_check() {
	if( Utility::nogui() || Utility::gui() ) return 1;
#ifdef Q_OS_MACOS
	QString ini_file_path = Utility::ConfigLocationPath();
#endif
#if !defined( Q_OS_MACOS )
	QString ini_file_path = Utility::applicationBundlePath();
#endif	
	QSettings settings( ini_file_path + INI_FILE, QSettings::IniFormat );
	settings.beginGroup( SETTING_GROUP );
	QVariant saved = settings.value( SETTING_MULTI_GUI );
	bool multi_gui_flag = !saved.isValid() ? MULTI_GUI_FLAG : saved.toBool();
	if(multi_gui_flag) 
		return true;
	else 
		return false;		
}

