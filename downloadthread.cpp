/*
	Copyright (C) 2009-2013 jakago

	This file is part of CaptureStream, the flv downloader for NHK radio
	language courses.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>

#include "downloadthread.h"
#include "ui_mainwindow.h"
#include "downloadmanager.h"
#include "customizedialog.h"
#include "mainwindow.h"
#include "urldownloader.h"
#include "utility.h"
#include "qt4qt5.h"
#include "scrambledialog.h"
#ifdef QT5
#include "mp3.h"
//#include <QXmlQuery>
#include <QScriptEngine>
#include <QDesktopWidget>
#include <QRegExp>
#include <QTextCodec>
#endif
#ifdef QT6
#include <QRegularExpression>
#endif
#include <QCheckBox>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QTemporaryFile>
#include <QDateTime>
#include <QEventLoop>
#include <QTextStream>
#include <QDate>
#include <QLocale>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QApplication>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork>
#include <QTemporaryFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonValue>
#include <QMap>
#include <QMultiMap>
#include <tuple>


#ifdef QT4_QT5_WIN
#define TimeOut " -m 10000 "
#else
#define TimeOut " -m 10 "
#endif

#define ScrambleLength 14
#define FlvMinSize 100	// ストリーミングが存在しなかった場合は13バイトだが少し大きめに設定
#define OriginalFormat "ts"
#define FilterOption "-bsf:a aac_adtstoasc"
#define CancelCheckTimeOut 500	// msec
#define DebugLog(s) if ( ui->toolButton_detailed_message->isChecked() ) {emit information((s));}

//--------------------------------------------------------------------------------
QString DownloadThread::prefix = "https://www.nhk.or.jp/gogaku/st/xml/";
QString DownloadThread::suffix = "listdataflv.xml";
QString DownloadThread::json_prefix = "https://www.nhk.or.jp/radioondemand/json/";

QString DownloadThread::prefix1 = "https://vod-stream.nhk.jp/gogaku-stream/mp4/";
QString DownloadThread::prefix2 = "https://vod-stream.nhk.jp/gogaku-stream/mp4/";
QString DownloadThread::prefix3 = "https://vod-stream.nhk.jp/gogaku-stream/mp4/";
//QString DownloadThread::prefix1 = "https://vod-stream.nhk.jp/radioondemand/r/";
QString DownloadThread::suffix1 = "/index.m3u8";
QString DownloadThread::suffix2 = ".mp4/index.m3u8";
QString DownloadThread::suffix3 = "/index.m3u8";

QString DownloadThread::flv_host = "flv.nhk.or.jp";
QString DownloadThread::flv_app = "ondemand/";
QString DownloadThread::flv_service_prefix = "mp4:flv/gogaku/streaming/mp4/";

QString DownloadThread::flvstreamer;
QString DownloadThread::ffmpeg;
QString DownloadThread::Xml_koza;
QString DownloadThread::test;
QString DownloadThread::Error_mes;
QString DownloadThread::scramble;
QString DownloadThread::optional1;
QString DownloadThread::optional2;
QString DownloadThread::optional3;
QString DownloadThread::optional4;
QString DownloadThread::optional5;
QString DownloadThread::optional6;
QString DownloadThread::optional7;
QString DownloadThread::optional8;
QString DownloadThread::opt_title1;
QString DownloadThread::opt_title2;
QString DownloadThread::opt_title3;
QString DownloadThread::opt_title4;
QString DownloadThread::opt_title5;
QString DownloadThread::opt_title6;
QString DownloadThread::opt_title7;
QString DownloadThread::opt_title8;

QStringList DownloadThread::malformed = (QStringList() << "3g2" << "3gp" << "m4a" << "mov");
QString DownloadThread::nendo1 = "2024";	// 今年度
QString DownloadThread::nendo2 = "2025";	// 次年度
QDate DownloadThread::nendo_start_date(2024, 4, 1);	// 今年度開始
QDate DownloadThread::zenki_end_date(2024, 9, 29);	// 今年度前期末、年度末は次年度前期末
QDate DownloadThread::kouki_start_date(2024, 9, 30);	// 今年度後期開始
QDate DownloadThread::nendo_end_date(2025, 3, 30);	// 今年度末
QDate DownloadThread::nendo_start_date1(2025, 3, 31);	// 年度初めは今年度開始、年度末は次年開始
QDate DownloadThread::nendo_end_date1(2026, 3, 29);	// 年度初めは今年度末、年度末は次年度末
QDate DownloadThread::nendo_start_date2(2025, 3, 31);	// 次年度開始
QDate DownloadThread::nendo_end_date2(2026, 3, 29);	// 次年度末

QHash<QString, QString> DownloadThread::ffmpegHash;
QHash<QProcess::ProcessError, QString> DownloadThread::processError;

//--------------------------------------------------------------------------------

DownloadThread::DownloadThread( Ui::MainWindowClass* ui ) : isCanceled(false), failed1935(false) {
	this->ui = ui;
	if ( ffmpegHash.empty() ) {
		ffmpegHash["aac"] = "%1,-vn,-acodec,copy,%2";
		ffmpegHash["m4a"] = "%1,-id3v2_version,3,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-bsf,aac_adtstoasc,-acodec,copy,%2";
		ffmpegHash["mp3-64k-S"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,64k,-ac,2,%2";
		ffmpegHash["mp3-128k-S"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,128k,-ac,2,%2";
		ffmpegHash["mp3-48k-S"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,48k,-ac,2,%2";
		ffmpegHash["mp3-40k-M"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,40k,-ar,32k,-ac,1,%2";
		ffmpegHash["mp3-32k-M"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,32k,-ar,32k,-ac,1,%2";
		ffmpegHash["mp3-24k-M"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,24k,-ar,22.05k,-ac,1,%2";
		ffmpegHash["mp3-16k-M"] = "%1,-id3v2_version,3,-write_xing,0,-metadata,title=%3,-metadata,artist=NHK,-metadata,album=%4,-metadata,date=%5,-metadata,genre=Speech,-vn,-acodec:a,libmp3lame,-ab,16k,-ar,22.05k,-ac,1,%2";
	}

	if ( processError.empty() ) {
		processError[QProcess::FailedToStart] = "FailedToStart";
		processError[QProcess::Crashed] = "Crashed";
		processError[QProcess::Timedout] = "Timedout";
		processError[QProcess::ReadError] = "ReadError";
		processError[QProcess::WriteError] = "WriteError";
		processError[QProcess::UnknownError] = "UnknownError";
	}
}


#include <QStringList>
#include <QFile>
#include <QXmlStreamReader>

QStringList Utility::getAttributeFromXml(const QString &xmlFilePath, const QString &attribute) {
    QStringList attributeList;
    QFile file(xmlFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return attributeList; // ファイルが開けなかった場合は空のリストを返す
    }

    QXmlStreamReader reader(&file);
    while (!reader.atEnd() && !reader.hasError()) {
        reader.readNext();
        if (reader.isStartElement() && reader.name() == attribute) {
            attributeList.append(reader.readElementText());
        }
    }

    if (reader.hasError()) {
        attributeList.clear(); // XML の解析エラー時は空のリストを返す
    }

    return attributeList;
}

#include <QStringList>
#include <QFile>
#include <QXmlStreamReader>

QStringList DownloadThread::getAttribute(const QString &url, const QString &attribute) {
    QStringList attributeList;
    QFile file(url);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return attributeList;  // ファイルが開けなかった場合は空リストを返す
    }

    QXmlStreamReader reader(&file);
    bool insideMusic = false;  // <music> 要素内かどうかのフラグ

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            // <music> 要素に入ったらフラグを立てる
            if (reader.name() == "music") {
                insideMusic = true;
            }
            // <music> 要素内で、目的の要素が見つかったらテキストを取得
            if (insideMusic && reader.name() == attribute) {
                QString text = reader.readElementText();
                attributeList.append(text);
            }
        } else if (token == QXmlStreamReader::EndElement) {
            // </music> 要素でフラグを下ろす
            if (reader.name() == "music") {
                insideMusic = false;
            }
        }
    }

    file.close();
    return attributeList;
}

#include <QStringList>
#include <QFile>
#include <QXmlStreamReader>

QStringList DownloadThread::getAttribute(const QString &url, const QString &attribute) {
    QStringList attributeList;
    QFile file(url);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return attributeList; // ファイルが開けなければ空リストを返す
    }

    QXmlStreamReader reader(&file);
    bool insideMusic = false;  // <music> 要素内にいるかどうかのフラグ

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            // <music> 要素の開始を検出
            if (reader.name() == QLatin1String("music")) {
                insideMusic = true;
            }
            // <music> 内で目的の要素名に一致した場合、テキストを取得
            else if (insideMusic && reader.name().toString() == attribute) {
                attributeList.append(reader.readElementText());
            }
        } else if (token == QXmlStreamReader::EndElement) {
            // </music> 要素の終了でフラグを下ろす
            if (reader.name() == QLatin1String("music")) {
                insideMusic = false;
            }
        }
    }

    file.close();
    return attributeList;
}


#include <tuple>
#include <QStringList>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>

std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList>
DownloadThread::getAttribute1(const QString &url)
{
    QStringList fileList;
    QStringList kouzaList;
    QStringList hdateList;
    QStringList nendoList;
    QStringList dirList;

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    // 新しいシグナル/スロットの接続構文（Qt5/Qt6 両対応）
    QObject::connect(&mgr, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);

    QUrl url_xml(url);
    QNetworkRequest req(url_xml);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // finished() シグナルを受けるまで待機

    QXmlStreamReader reader(reply);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartDocument())
            continue;
        if (reader.isEndDocument())
            break;

        // 各属性の値を取得（Qt5/Qt6 両方で有効）
        fileList.append(reader.attributes().value("file").toString());
        kouzaList.append(reader.attributes().value("kouza").toString());
        hdateList.append(reader.attributes().value("hdate").toString());
        nendoList.append(reader.attributes().value("nendo").toString());
        dirList.append(reader.attributes().value("dir").toString());
    }

    reply->deleteLater();
    return { fileList, kouzaList, hdateList, nendoList, dirList };
}

#ifdef QT5
QStringList DownloadThread::getAttribute( QString url, QString attribute ) {
	const QString xmlUrl = "doc('" + url + "')/musicdata/music/" + attribute + "/string()";
	QStringList attributeList;
	QXmlQuery query;
	query.setQuery( xmlUrl );
	if ( query.isValid() )
		query.evaluateTo( &attributeList );
	return attributeList;
}
#endif






QStringList DownloadThread::getAttribute(const QString &url, const QString &attribute) {
    const QString xmlQuery = "doc('" + url + "')/musicdata/music/" + attribute + "/string()";
    QStringList attributeList;
    QXmlQuery query;

    query.setQuery(xmlQuery); // Qt5 でも Qt6 でも共通の記述

    if (query.isValid()) {
        query.evaluateTo(&attributeList);
    }

    return attributeList;
}

#ifdef QT6
std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> DownloadThread::getAttribute1( QString url ) {
	QStringList fileList;			fileList.clear();
	QStringList kouzaList;			kouzaList.clear();
	QStringList hdateList;			hdateList.clear();
	QStringList nendoList;			nendoList.clear();
	QStringList dirList;			dirList.clear();

    	QEventLoop eventLoop;	
	QNetworkAccessManager mgr;
 	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	QUrl url_xml( url );
	QNetworkRequest req;
	req.setUrl(url_xml);
	QNetworkReply *reply = mgr.get(req);
	QXmlStreamReader reader( reply );
	eventLoop.exec();
	
	while (!reader.atEnd()) {
		reader.readNext();
		if (reader.isStartDocument()) continue;
		if (reader.isEndDocument()) break;

		fileList += reader.attributes().value( "file" ).toString();
		kouzaList += reader.attributes().value( "kouza" ).toString();
		hdateList += reader.attributes().value( "hdate" ).toString();
		nendoList += reader.attributes().value( "nendo" ).toString();
		dirList += reader.attributes().value( "dir" ).toString();
	}
	return { fileList, kouzaList, hdateList, nendoList, dirList };	
}
#endif

QString DownloadThread::getJsonFile( QString jsonUrl ) {
    	QEventLoop eventLoop;
    	QString attribute;
	QTimer timer;    
	timer.setSingleShot(true);
	QNetworkAccessManager mgr;
	QObject::connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
 	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*) ), &eventLoop, SLOT(quit()));
	QUrl url_json( jsonUrl );
	QNetworkRequest req;
	req.setUrl(url_json);
	timer.start(400);  // use miliseconds
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec(); // blocks stack until "finished()" has been called

	if(timer.isActive()) {
		timer.stop();
		
		if (reply->error() == QNetworkReply::NoError) {
			attribute = (QString)reply->readAll();
		} else {
			return "error";
		}  
	} else {
          // timeout
		QObject::disconnect(&mgr, SIGNAL(finished(QNetworkReply*) ), &eventLoop, SLOT(quit()));
		reply->abort();
		return "error";
	}
	return attribute;
}

std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> DownloadThread::getJsonData( QString url ) {
	QStringList fileList;			fileList.clear();
	QStringList kouzaList;			kouzaList.clear();
	QStringList file_titleList;		file_titleList.clear();
	QStringList hdateList;			hdateList.clear();
	QStringList yearList;			yearList.clear();
	int l = 10 ;				int l_length = url.length();
	if ( l_length != 13 ) l = l_length -3 ;

	int json_ohyo = 0 ;
	if ( url.contains( "_x1" ) ) { url.replace( "_x1", "_01" ); json_ohyo = 1 ; };
	if ( url.contains( "_y1" ) ) { url.replace( "_y1", "_01" ); json_ohyo = 2 ; };

 	const QString jsonUrl1 = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" + url.left( l ) + "&corner_site_id=" + url.right(2);
//	const QString jsonUrl2 = json_prefix + url.left(4) + "/bangumi_" + url + ".json";
 
	QString strReply;
	int flag = 0;
	int TimerMin = 100;
	int TimerMax = 5000;
	int Timer = TimerMin;
	int retry = 15;
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
	case 0: kouzaList += ""; emit critical( QString::fromUtf8( "番組ID：" ) + url + QString::fromUtf8( "のデータ取得エラー" ) ); break;
	case 1: std::tie( fileList, kouzaList, file_titleList, hdateList, yearList ) = Utility::getJsonData1( strReply, json_ohyo ); break;
	default: kouzaList += ""; emit critical( QString::fromUtf8( "番組ID：" ) + url + QString::fromUtf8( "のデータ取得エラー" ) ); break;
	}

	if ( kouzaList.count() > file_titleList.count() ) while ( kouzaList.count() == file_titleList.count() ) file_titleList += "\0";
	if ( kouzaList.count() > fileList.count() ) while ( kouzaList.count() == fileList.count() ) fileList += "\0";
	if ( kouzaList.count() > hdateList.count() ) while ( kouzaList.count() == hdateList.count() ) hdateList += "\0";
	if ( kouzaList.count() > yearList.count() ) while ( kouzaList.count() == yearList.count() ) yearList += "\0";
	return { fileList, kouzaList, file_titleList, hdateList, yearList };
}

QString DownloadThread::getAttribute2( QString url, QString attribute ) {
    	QEventLoop eventLoop;	
	QNetworkAccessManager mgr;
 	QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	QUrl url_html( url );
	QNetworkRequest req;
	req.setUrl( url_html );
	QNetworkReply *reply = mgr.get(req);
	eventLoop.exec();

	QString content =  reply->readAll();

	QRegularExpression rx("https://vod-stream.nhk.jp/gogaku-stream/.+?/index.m3u8");
	QRegularExpressionMatch match = rx.match( content ); 
	attribute = match.captured(0);

	return attribute;
}

void DownloadThread::id_list() {
	QStringList key; key.clear();
	QStringList tmp_list = MainWindow::name_map.keys();
	QStringList tmp_list1 = { "英語", "英会話", "イングリッシュ", "ボキャブライダー", "Asian View" };
	QStringList tmp_list2 = { "まいにち", "中国語", "ハングル", "アラビア", "ポルトガル", "日本語", "Learn Japanese", "Living in Japan" };
	QMap<QString, QString> tmp_map;
	switch ( MainWindow::id_List_flag ) {
		case 1:
			for ( int i = 0; i < tmp_list.count() ; i++ ) {
				for ( int j = 0; j < tmp_list1.count() ; j++ ) {
					if ( tmp_list[i].contains( tmp_list1[j] ) && !tmp_list[i].contains( "【中級編】") ) tmp_map[ tmp_list[i] ] = "";
				}
			}
			key = tmp_map.keys();
			break;
		case 2:
			for ( int i = 0; i < tmp_list.count() ; i++ ) {
				for ( int j = 0; j < tmp_list2.count() ; j++ ) {
					if ( tmp_list[i].contains( tmp_list2[j] ) && !tmp_list[i].contains( "【中級編】") ) tmp_map[ tmp_list[i] ] = "";
				}
			}
			key = tmp_map.keys();
			break;
		case 3:
			key = MainWindow::name_map.keys();
			break;
		default:
			break;
	}

	emit current( QString::fromUtf8( "番組ＩＤ\t\t： 番組名 " ) );
	for ( int i = 0; i < key.count() ; i++ ) {
		if ( MainWindow::name_map[key[i]].left(1) == "F") {
			emit current( MainWindow::name_map[key[i]] + QString::fromUtf8( "\t\t： " ) + key[i] );
		} else {
			emit current( MainWindow::name_map[key[i]] + QString::fromUtf8( "\t： " ) + key[i] );
		}
	}
	key.clear(); tmp_map.clear(); tmp_list.clear(); tmp_list1.clear(); tmp_list2.clear();
	MainWindow::id_flag = false;
}

void DownloadThread::thumbnail_add( QString dstPath, QString tmp, QString json_path ) {
	int l = 10 ;
	int l_length = json_path.length();
	if ( l_length != 13 ) l = l_length -3 ;
	QString corner_site_id = json_path.right(2);
	if ( corner_site_id == "x1" || corner_site_id == "y1" ) corner_site_id = "01" ;
	if ( !MainWindow::thumbnail_map.contains( json_path.left( l ) + "_" + corner_site_id ) ) return;
	QFile::rename( dstPath, tmp );
	QString thumb = MainWindow::thumbnail_map.value( json_path.left( l ) + "_" + corner_site_id );
	QStringList arguments_t = { "-y", "-i", tmp, "-i", thumb, "-id3v2_version", "3", "-map", "0:a", "-map", "1:v", "-map_metadata", "0", "-codec", "copy", "-disposition:1", "attached_pic", dstPath };
	if ( dstPath.right( 3 ) == "mp3" )
		QStringList arguments_t = { "-y", "-i", tmp, "-i", thumb, "-id3v2_version", "3", "-write_xing", "0", "-map", "0:a", "-map", "1:v", "-map_metadata", "0", "-codec", "copy", "-disposition:1", "attached_pic", dstPath };
	QProcess process_t;
	process_t.setProgram( ffmpeg );
	process_t.setArguments( arguments_t );
	process_t.start();
	process_t.waitForFinished();
	QString str_t = process_t.readAllStandardError();
	process_t.kill();
	process_t.close();
	if ( str_t.contains( "error", Qt::CaseInsensitive )){
		QFile::remove( dstPath );
		QFile::rename( tmp, dstPath);
		return;
	}
	QFile::remove( tmp );
	return;
}

bool DownloadThread::checkExecutable( QString path ) {
	QFileInfo fileInfo( path );
	
	if ( !fileInfo.exists() ) {
		emit critical( path + QString::fromUtf8( "が見つかりません。" ) );
		return false;
	} else if ( !fileInfo.isExecutable() ) {
		emit critical( path + QString::fromUtf8( "は実行可能ではありません。" ) );
		return false;
	}
	
	return true;
}

bool DownloadThread::isFfmpegAvailable( QString& path ) {
	bool flag = MainWindow::ffmpegDirSpecified;
	if ( flag ) {
		path = MainWindow::ffmpeg_folder + "ffmpeg";	
	} else {
	path = Utility::applicationBundlePath() + "ffmpeg";

#ifdef QT4_QT5_MAC    // MacのみoutputDirフォルダに置かれたffmpegを優先する
	path = MainWindow::outputDir + "ffmpeg";
	QFileInfo fileInfo( path );
	if ( !fileInfo.exists() ) {
		path = Utility::appConfigLocationPath() + "ffmpeg";
		QFileInfo fileInfo( path );
		if ( !fileInfo.exists() ) {
			path = Utility::ConfigLocationPath() + "ffmpeg";
			QFileInfo fileInfo( path );
			if ( !fileInfo.exists() ) {
				path = "/usr/local/bin/ffmpeg";
				QFileInfo fileInfo( path );
				if ( !fileInfo.exists() ) {
					path = Utility::applicationBundlePath() + "ffmpeg";
				}
			}
		}
	} 
#endif
	}
#ifdef QT4_QT5_WIN
	path += ".exe";
#endif
	return checkExecutable( path );
}


//通常ファイルが存在する場合のチェックのために末尾にセパレータはついていないこと
bool DownloadThread::checkOutputDir( QString dirPath ) {
	bool result = false;
	QFileInfo dirInfo( dirPath );

	if ( dirInfo.exists() ) {
		if ( !dirInfo.isDir() )
			emit critical( QString::fromUtf8( "「" ) + dirPath + QString::fromUtf8( "」が存在しますが、フォルダではありません。" ) );
		else if ( !dirInfo.isWritable() )
			emit critical( QString::fromUtf8( "「" ) + dirPath + QString::fromUtf8( "」フォルダが書き込み可能ではありません。" ) );
		else
			result = true;
	} else {
		QDir dir;
		if ( !dir.mkpath( dirPath ) )
			emit critical( QString::fromUtf8( "「" ) + dirPath + QString::fromUtf8( "」フォルダの作成に失敗しました。" ) );
		else
			result = true;
	}

	return result;
}

//--------------------------------------------------------------------------------

#ifdef QT5
QStringList DownloadThread::getElements( QString url, QString path ) {
	const QString xmlUrl = "doc('" + url + "')" + path;
	QStringList elementList;
	QXmlQuery query;
	query.setQuery( xmlUrl );
	if ( query.isValid() )
		query.evaluateTo( &elementList );
	return elementList;
}
#endif

//--------------------------------------------------------------------------------
#ifdef QT5
QStringList one2two( QStringList hdateList ) {
	QStringList result;
	QRegExp rx("(\\d+)(?:\\D+)(\\d+)");

	for ( int i = 0; i < hdateList.count(); i++ ) {
		QString hdate = hdateList[i];
		if ( rx.indexIn( hdate, 0 ) != -1 ) {
			uint length = rx.cap( 2 ).length();
			if ( length == 1 )
				hdate.replace( rx.pos( 2 ), 1, "0" + rx.cap( 2 ) );
			length = rx.cap( 1 ).length();
			if ( length == 1 )
				hdate.replace( rx.pos( 1 ), 1, "0" + rx.cap( 1 ) );
		}
		result << hdate;
	}

	return result;
}

QStringList one2two2( QStringList hdateList2 ) {
	QStringList result;
	QRegExp rx("(\\d+)(?:\\D+)(\\d+)");

	for ( int i = 0; i < hdateList2.count(); i++ ) {
		QString hdate = hdateList2[i];
		if ( rx.indexIn( hdate, 0 ) != -1 ) {
			uint length = rx.cap( 2 ).length();
			if ( length == 1 )
				hdate.replace( rx.pos( 2 ), 1, "0" + rx.cap( 2 ) );
			length = rx.cap( 1 ).length();
			if ( length == 1 )
				hdate.replace( rx.pos( 1 ), 1, "0" + rx.cap( 1 ) );
		}
		QString month2 = hdate.left( 2 );
		QString day2 = hdate.mid( 3, 2 );
		QDate today;
		today.setDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
		QDateTime dt = QDateTime::fromString( month2 + "/" + day2, "MM/dd" ).addDays(7);
	
		QString str1 = dt.toString("MM");
		QString str2 = dt.toString("dd");

		hdate.replace( day2, str2 );
		hdate.replace( month2, str1 );

		result << hdate;
	}

	return result;
}
#endif
#ifdef QT6
QStringList one2two( QStringList hdateList ) {
	QStringList result;
	QRegularExpression rx("(\\d+)(?:\\D+)(\\d+)");

	for ( int i = 0; i < hdateList.count(); i++ ) {
		QString hdate = hdateList[i];
		QRegularExpressionMatch match = rx.match( hdate, 0 ); 
		int month = match.captured(1).toInt();
		int day = match.captured(2).toInt();
		hdate = QString::number( month + 100 ).right( 2 ) + "月" + QString::number( day + 100 ).right( 2 ) + "日放送分";

		result << hdate;
	}
	return result;
}
#endif

QStringList thisweekfile( QStringList fileList2, QStringList codeList ) {
	QStringList result;
	
	for ( int i = 0; i < fileList2.count(); i++ ) {
		QString filex = fileList2[i];
		int filexxx = codeList[i].toInt() + fileList2.count() ;
		filex.replace( codeList[i].right( 3 ) ,  QString::number( filexxx ).right( 3 ) );
		filex.remove( "-re01" );
			
		result << filex;
	}

	return result;
}

//--------------------------------------------------------------------------------

bool illegal( char c ) {
	bool result = false;
	switch ( c ) {
	case '/':
	case '\\':
	case ':':
	case '*':
	case '?':
	case '"':
	case '<':
	case '>':
	case '|':
	case '#':
	case '{':
	case '}':
	case '%':
	case '&':
	case '~':
		result = true;
		break;
	default:
		break;
	}
	return result;
}

QString DownloadThread::formatName( QString format, QString kouza, QString hdate, QString file, QString nendo, QString dupnmb, bool checkIllegal ) {
	int month = hdate.left( 2 ).toInt();
	int year = nendo.right( 4 ).toInt();
	int day = hdate.mid( 3, 2 ).toInt();
//	int year1 = QDate::currentDate().year();
	
	QDate on_air_date1(year, month, day);
	if ( on_air_date1 <= nendo_end_date1 ) nendo = nendo1;
	if ( on_air_date1 >= nendo_start_date1 ) nendo = nendo2;
//	if ( QString::compare(  kouza , QString::fromUtf8( "ボキャブライダー" ) ) ==0 ){
//		if ( month == 3 && ( day == 30 || day == 31) && year == 2022 ) 
//		year += 0;
// 		else
//		if ( month < 4 )
//		year += 1;
//	} else {
//	if ( month <= 4 && QDate::currentDate().year() > year )
//		year = year + (year1 - year);
//	}

	if ( file.right( 4 ) == ".flv" )
		file = file.left( file.length() - 4 );

	QString dupnmb1 = dupnmb;
	if ( format.contains( "%i", Qt::CaseInsensitive)) dupnmb1 = "";
	if ( format.contains( "%_%i", Qt::CaseInsensitive)) { dupnmb.replace( "-", "_" ); format.remove( "%_" ); }

	QString result;

	bool percent = false;
	for ( int i = 0; i < format.length(); i++ ) {
		QChar qchar = format[i];
		if ( percent ) {
			percent = false;
			char ascii = qchar.toLatin1();
			if ( checkIllegal && illegal( ascii ) )
				continue;
			switch ( ascii ) {
			case 'k': result += kouza; break;
			case 'h': result += hdate.left( 6 ) + QString::fromUtf8( "放送分" ) + dupnmb1; break;
			case 'f': result += file; break;
			//case 'r': result += MainWindow::applicationDirPath(); break;
			//case 'p': result += QDir::separator(); break;
			case 'Y': result += QString::number( year ); break;
			case 'y': result += QString::number( year ).right( 2 ); break;
			case 'N': result += nendo + QString::fromUtf8( "年度" ); break;
			case 'n': result += nendo.right( 2 ) + QString::fromUtf8( "年度" ); break;
			case 'M': result += QString::number( month + 100 ).right( 2 ); break;
			case 'm': result += QString::number( month ); break;
			case 'D': result += QString::number( day + 100 ).right( 2 ) + dupnmb1; break;
			case 'd': result += QString::number( day ) + dupnmb1; break;
			case 'i': result += dupnmb; break;
			case 'x': break;
			case 's': break;
			default: result += qchar; break;
			}
		} else {
			if ( qchar == QChar( '%' ) )
				percent = true;
			else if ( checkIllegal && illegal( qchar.toLatin1() ) )
				continue;
			else
				result += qchar;
		}
	}

	return result;
}

//--------------------------------------------------------------------------------

bool DownloadThread::captureStream( QString kouza, QString hdate, QString file, QString nendo, QString dir, QString this_week, QString json_path, bool nogui_flag ) {
	QString titleFormat;
	QString fileNameFormat;
	CustomizeDialog::formats( "xml", titleFormat, fileNameFormat );
	QString outputDir = MainWindow::outputDir;
	QString extension = ui->comboBox_extension->currentText();
	if ( nogui_flag ) 
		std::tie( titleFormat, fileNameFormat, outputDir, extension ) = Utility::nogui_option( titleFormat, fileNameFormat, outputDir, extension );


	if ( this_week == "R" )
		outputDir = outputDir + QString::fromUtf8( "[前週]" )+ "/" + kouza;
	else
		outputDir = outputDir + kouza;
	if ( !checkOutputDir( outputDir ) )
		return false;
	outputDir += QDir::separator();	//通常ファイルが存在する場合のチェックのために後から追加する

	int month = hdate.left( 2 ).toInt();
	int year = nendo.right( 4 ).toInt();
	int day = hdate.mid( 3, 2 ).toInt();
	if ( 2022 > year ) return false;
	int year1 = QDate::currentDate().year();

//	if ( QString::compare(  kouza , QString::fromUtf8( "ボキャブライダー" ) ) ==0 ){
//		if ( month == 3 && ( day == 30 || day == 31) && year == 2022 ) 
//		year += 0; 
//		else
//		if ( month < 4 )
//		year += 1;
//	} else {
	if ( month <= 4 && QDate::currentDate().year() > year )
		year = year + (year1 - year);
//	}
	QDate onair( year, month, day );
	QString yyyymmdd = onair.toString( "yyyy_MM_dd" );

	QString kon_nendo = "2024"; //QString::number(year1);

//	QString outputDir = MainWindow::outputDir + kouza;
//	if ( this_week == "R" )
//		outputDir = MainWindow::outputDir + QString::fromUtf8( "[前週]" )+ "/" + kouza;

//	if ( !checkOutputDir( outputDir ) )
//		return false;
//	outputDir += QDir::separator();	//通常ファイルが存在する場合のチェックのために後から追加する

//	QString titleFormat;
//	QString fileNameFormat;
//	CustomizeDialog::formats( "xml", titleFormat, fileNameFormat );
	QString id3tagTitle = formatName( titleFormat, kouza, hdate, file, yyyymmdd.left(4), "", false );
	QString outFileName = formatName( fileNameFormat, kouza, hdate, file, yyyymmdd.left(4), "", true );
	QFileInfo fileInfo( outFileName );
	QString outBasename = fileInfo.completeBaseName();
	
	// 2013/04/05 オーディオフォーマットの変更に伴って拡張子の指定に対応
//	QString extension = ui->comboBox_extension->currentText();
	QString extension1 = extension;
	if ( extension.left( 3 ) == "mp3" ) extension1 = "mp3";
	outFileName = outBasename + "." + extension1;

#ifdef QT4_QT5_WIN
	QString null( "nul" );
#else
	QString null( "/dev/null" );
#endif
	if ( ui->toolButton_skip->isChecked() && QFile::exists( outputDir + outFileName ) ) {
	   if ( this_week == "R" ) {
		emit current( QString::fromUtf8( "スキップ：[前週]　　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	   } else {
		emit current( QString::fromUtf8( "スキップ：　　　　　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	   }
		return true;
	}
	
	if ( this_week == "R" ) {
	  	emit current( QString::fromUtf8( "レコーディング中：[前週] " ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	} else {
  		emit current( QString::fromUtf8( "レコーディング中：　　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	}
	
	Q_ASSERT( ffmpegHash.contains( extension ) );
	QString dstPath;
#ifdef QT4_QT5_WIN
	if ( true ) {
		QTemporaryFile file;
		if ( file.open() ) {
			dstPath = file.fileName() + "." + extension1;
			file.close();
		} else {
			emit critical( QString::fromUtf8( "一時ファイルの作成に失敗しました：　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
			return false;
		}
	}
#else
	dstPath = outputDir + outFileName;
#endif
	QString filem3u8a; QString filem3u8b; QString prefix1a = prefix1;  QString prefix2a = prefix2;  QString prefix3a = prefix3;
	if ( dir ==  ""  ) { prefix1a.remove("/mp4");        prefix2a.remove("/mp4");        prefix3a.remove("/mp4");
	} else             { prefix1a.replace( "mp4", dir ); prefix2a.replace( "mp4", dir ); prefix3a.replace( "mp4", dir ); }; 
//	if ( file.right(4) != ".mp4" ) {
//		filem3u8a = prefix1a + file + ".mp4/index.m3u8";
//		filem3u8b = prefix2a + file + ".mp4/index.m3u8";
//	} else {
//		filem3u8a = prefix1a + file + "/index.m3u8";
//		filem3u8b = prefix2a + file + "/index.m3u8";
//	}
	filem3u8a = prefix1a + file + "/index.m3u8";
	filem3u8b = prefix2a + file + "/index.m3u8";
	QString filem3u8c = prefix3a + file + "/index.m3u8";
	QStringList arguments_v = { "-http_seekable", "0", "-version", "0" };
	QProcess process_v;
	process_v.setProgram( ffmpeg );
	process_v.setArguments( arguments_v );
	process_v.start();
	process_v.waitForFinished();
	QString str_v = process_v.readAllStandardError();
	process_v.kill();
	process_v.close();	 
	QString arguments00 = "-y -http_seekable 0 -i";
	if (str_v.contains( "Option not found" )) {
	                     arguments00 = "-y -i";
	}

	QString id3tag_album = kouza;
	if ( fileNameFormat.contains( "%x", Qt::CaseInsensitive) ) {
		id3tag_album.remove( "まいにち" );
		if ( kouza.contains( "レベル1", Qt::CaseInsensitive) ) id3tag_album = "L1_" + id3tag_album.remove( "【レベル1】" );
		if ( kouza.contains( "レベル2", Qt::CaseInsensitive) ) id3tag_album = "L2_" + id3tag_album.remove( "【レベル2】" );
		if ( kouza.contains( "入門", Qt::CaseInsensitive) ) id3tag_album = "入門_" + id3tag_album.remove( "【入門編】" );
		if ( kouza.contains( "初級", Qt::CaseInsensitive) ) id3tag_album = "初級_" + id3tag_album.remove( "【初級編】" );
		if ( kouza.contains( "中級", Qt::CaseInsensitive) ) id3tag_album = "中級_" + id3tag_album.remove( "【中級編】" );
		if ( kouza.contains( "応用", Qt::CaseInsensitive) ) id3tag_album = "応用_" + id3tag_album.remove( "【応用編】" );
	}

	QStringList arguments0 = arguments00.split(" ");
	QString arguments01 = "-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 120";
	QStringList arguments1 = arguments01.split(" ");
	QStringList arguments = arguments0 + ffmpegHash[extension]
			.arg( filem3u8a, dstPath, id3tagTitle, id3tag_album, QString::number( year ) ).split(",");
	QStringList arguments2 = arguments0 + ffmpegHash[extension]
			.arg( filem3u8b, dstPath, id3tagTitle, id3tag_album, QString::number( year ) ).split(","); 
	QStringList arguments3 = arguments1 + arguments0 + ffmpegHash[extension]
			.arg( filem3u8c, dstPath, id3tagTitle, id3tag_album, QString::number( year ) ).split(","); 

	//qDebug() << commandFfmpeg;
	//DebugLog( commandFfmpeg );
	QProcess process;
	process.setProgram( ffmpeg );
	process.setArguments( arguments );
	
	QProcess process2;
	process2.setProgram( ffmpeg );
	process2.setArguments( arguments2 );
	
	QProcess process3;
	process3.setProgram( ffmpeg );
	process3.setArguments( arguments3 );
	
	process.start();
//	process.start( commandFfmpeg );
	if ( !process.waitForStarted( -1 ) ) {
		emit critical( QString::fromUtf8( "ffmpeg起動エラー(%3)：　%1　　%2" )
				.arg( kouza, yyyymmdd,  processError[process.error()] ) );
		QFile::remove( dstPath );
		return false;
	}

	// ユーザのキャンセルを確認しながらffmpegの終了を待つ
	while ( !process.waitForFinished( CancelCheckTimeOut ) ) {
		// キャンセルボタンが押されていたらffmpegをkillし、ファイルを削除してリターン
		if ( isCanceled ) {
			process.kill();
			QFile::remove( dstPath );
			return false;
		}
		// 単なるタイムアウトは継続
		if ( process.error() == QProcess::Timedout )
			continue;
		// エラー発生時はメッセージを表示し、出力ファイルを削除してリターン
		emit critical( QString::fromUtf8( "ffmpeg実行エラー(%3)：　%1　　%2" )
				.arg( kouza, yyyymmdd,  processError[process.error()] ) );
		QFile::remove( dstPath );
		return false;
	}


	QString ffmpeg_Error;
	ffmpeg_Error.append(process.readAllStandardError());

	// ffmpeg終了ステータスに応じた処理をしてリターン
	if ( process.exitCode() || ffmpeg_Error.contains("HTTP error") || ffmpeg_Error.contains("Unable to open resource") || ffmpeg_Error.contains("parse_playlist error")) {
//	if ( process.exitCode()  ) {
	process.kill();
	process.close();
	process2.start();

		if ( !process2.waitForStarted( -1 ) ) {
			emit critical( QString::fromUtf8( "ffmpeg起動エラー2(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  processError[process2.error()] ) );
			QFile::remove( dstPath );
			return false;
		}

	// ユーザのキャンセルを確認しながらffmpegの終了を待つ
		while ( !process2.waitForFinished( CancelCheckTimeOut ) ) {
		// キャンセルボタンが押されていたらffmpegをkillし、ファイルを削除してリターン
			if ( isCanceled ) {
				process2.kill();
				QFile::remove( dstPath );
				return false;
			}
		// 単なるタイムアウトは継続
			if ( process2.error() == QProcess::Timedout )
				continue;
		// エラー発生時はメッセージを表示し、出力ファイルを削除してリターン
			emit critical( QString::fromUtf8( "ffmpeg実行エラー2(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  processError[process2.error()] ) );
			QFile::remove( dstPath );
			return false;
		}

	QString ffmpeg_Error2;
	ffmpeg_Error2.append(process2.readAllStandardError());

	// ffmpeg終了ステータスに応じた処理をしてリターン
	if ( process2.exitCode() || ffmpeg_Error2.contains("HTTP error") || ffmpeg_Error2.contains("Unable to open resource:") ) {
//	if ( process2.exitCode()  ) {
	process2.kill();
	process2.close();
	process3.start();

		if ( !process3.waitForStarted( -1 ) ) {
			emit critical( QString::fromUtf8( "ffmpeg起動エラー3(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  processError[process3.error()] ) );
			QFile::remove( dstPath );
			return false;
		}

	// ユーザのキャンセルを確認しながらffmpegの終了を待つ
		while ( !process3.waitForFinished( CancelCheckTimeOut ) ) {
		// キャンセルボタンが押されていたらffmpegをkillし、ファイルを削除してリターン
			if ( isCanceled ) {
				process3.kill();
				QFile::remove( dstPath );
				return false;
			}
		// 単なるタイムアウトは継続
			if ( process3.error() == QProcess::Timedout )
				continue;
		// エラー発生時はメッセージを表示し、出力ファイルを削除してリターン
			emit critical( QString::fromUtf8( "ffmpeg実行エラー(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  processError[process3.error()] ) );
			QFile::remove( dstPath );
			return false;
		}
	
	QString ffmpeg_Error3;
	ffmpeg_Error3.append(process3.readAllStandardError());
	
	// ffmpeg終了ステータスに応じた処理をしてリターン
	if ( process3.exitCode() || ffmpeg_Error3.contains("HTTP error") || ffmpeg_Error3.contains("Unable to open resource:") ) {	
				emit critical( QString::fromUtf8( "レコーディング失敗：　%1　　%2" ).arg( kouza, yyyymmdd ) );
			QFile::remove( dstPath );
			return false;
		}
	}}
	QString tmp = outputDir + "tmp"  + "." + extension1;
	if ( (ui->checkBox_thumbnail->isChecked() || Utility::option_check( "-a1" )) && extension1 != "aac" && !Utility::option_check( "-a0" ) ) thumbnail_add( dstPath, tmp, json_path );

#ifdef QT4_QT5_WIN
		QFile::rename( dstPath, outputDir + outFileName );
#endif
			return true;
}



bool DownloadThread::captureStream_json( QString kouza, QString hdate, QString file, QString nendo, QString title, QString dupnmb, QString json_path, bool nogui_flag ) {

	QString titleFormat;
	QString fileNameFormat;
	CustomizeDialog::formats( "json", titleFormat, fileNameFormat );
	QString outputDir = MainWindow::outputDir;
	QString extension = ui->comboBox_extension->currentText();
	QString Xml_koza = "";
	Xml_koza = map.value( json_path );
	bool ouyou_koza_separation_flag = Xml_koza.contains( "kouza3", Qt::CaseInsensitive) && (fileNameFormat.contains( "%s", Qt::CaseInsensitive) || fileNameFormat.contains( "%x", Qt::CaseInsensitive) || MainWindow::koza_separation_flag ) ;
	if (MainWindow::koza_separation_flag) fileNameFormat.remove( "%s" );	
	if ( nogui_flag ) {
		std::tie( titleFormat, fileNameFormat, outputDir, extension ) = Utility::nogui_option( titleFormat, fileNameFormat, outputDir, extension );
		ouyou_koza_separation_flag = Xml_koza.contains( "kouza3", Qt::CaseInsensitive) && (fileNameFormat.contains( "%s", Qt::CaseInsensitive) || fileNameFormat.contains( "%x", Qt::CaseInsensitive) || Utility::option_check( "-s" ) );
	}

//	QString id3tagTitle = title;
	if ( ouyou_koza_separation_flag ) {
		if( MainWindow::name_space_flag ) {
			if ( title.contains( "入門", Qt::CaseInsensitive) ) kouza = kouza + "【入門編】";
			if ( title.contains( "初級", Qt::CaseInsensitive) ) kouza = kouza + "【初級編】";
			if ( title.contains( "中級", Qt::CaseInsensitive) ) kouza = kouza + "【中級編】";
			if ( title.contains( "応用", Qt::CaseInsensitive) ) kouza = kouza + "【応用編】";
		} else {
			if ( title.contains( "入門", Qt::CaseInsensitive) ) kouza = kouza + " 入門編";
			if ( title.contains( "初級", Qt::CaseInsensitive) ) kouza = kouza + " 初級編";
			if ( title.contains( "中級", Qt::CaseInsensitive) ) kouza = kouza + " 中級編";
			if ( title.contains( "応用", Qt::CaseInsensitive) ) kouza = kouza + " 応用編";
		} 
	}

	QString id3tagTitle = formatName( titleFormat, kouza, hdate, title, nendo, dupnmb, false );
	QString outFileName = formatName( fileNameFormat, kouza, hdate, title, nendo, dupnmb, true );
	QFileInfo fileInfo( outFileName );
	QString outBasename = fileInfo.completeBaseName();
	QString kouza_tmp = kouza;
	if( MainWindow::tag_space_flag ) id3tagTitle = id3tagTitle.replace( " ", "_" );
	if( MainWindow::name_space_flag ) {
		outBasename = outBasename.replace( " ", "_" );
		kouza_tmp = kouza.replace( " ", "_" );
	}
	outputDir = outputDir + kouza_tmp;
	if ( !checkOutputDir( outputDir ) )
		return false;
	outputDir += QDir::separator();	//通常ファイルが存在する場合のチェックのために後から追加する
	
	// 2013/04/05 オーディオフォーマットの変更に伴って拡張子の指定に対応
//	QString extension = ui->comboBox_extension->currentText();
	QString extension1 = extension;
	if ( extension.left( 3 ) == "mp3" ) extension1 = "mp3";
	outFileName = outBasename + "." + extension1;

#ifdef QT4_QT5_WIN
	QString null( "nul" );
#else
	QString null( "/dev/null" );
#endif
	int month = hdate.left( 2 ).toInt();
	int year = nendo.right( 4 ).toInt();
	int day = hdate.mid( 3, 2 ).toInt();
//	if ( 2023 > year ) return false;
	int year1 = QDate::currentDate().year();

	if ( month <= 4 && QDate::currentDate().year() > year )
		year = year + (year1 - year);

	QDate onair( year, month, day );
	QString yyyymmdd = onair.toString( "yyyy_MM_dd" );

	QString kon_nendo = "2023"; //QString::number(year1);
	
	if ( ui->toolButton_skip->isChecked() && QFile::exists( outputDir + outFileName ) ) {
		emit current( QString::fromUtf8( "スキップ：　　　　　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd + dupnmb);
//		emit current( QString::fromUtf8( "スキップ：　　　　　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	   	return true;
	}
  		emit current( QString::fromUtf8( "レコーディング中：　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd + dupnmb );
//  		emit current( QString::fromUtf8( "レコーディング中：　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
	
	Q_ASSERT( ffmpegHash.contains( extension ) );
	QString dstPath;
#ifdef QT4_QT5_WIN
	if ( true ) {
		QTemporaryFile file;
		if ( file.open() ) {
			dstPath = file.fileName() + "." + extension1;
			file.close();
		} else {
			emit critical( QString::fromUtf8( "一時ファイルの作成に失敗しました：　" ) + kouza + QString::fromUtf8( "　" ) + yyyymmdd );
			return false;
		}
	}
#else
	dstPath = outputDir + outFileName;
#endif

	QStringList arguments_v = { "-http_seekable", "0", "-version", "0" };
	QProcess process_v;
	process_v.setProgram( ffmpeg );
	process_v.setArguments( arguments_v );
	process_v.start();
	process_v.waitForFinished();
	QString str_v = process_v.readAllStandardError();
	process_v.kill();
	process_v.close();	 
	QString arguments00 = "-y -http_seekable 0 -i";
	if (str_v.contains( "Option not found" )) {
	                     arguments00 = "-y -i";
	}
	
	QStringList arguments0 = arguments00.split(" ");
	QString arguments01 = "-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 120";
	QStringList arguments1 = arguments01.split(" ");

	QString filem3u8aA = file;
	QString dstPathA = outputDir + outFileName;
	QString id3tagTitleA = id3tagTitle;
	QString id3tag_album = kouza;
	
	if ( fileNameFormat.contains( "%x", Qt::CaseInsensitive) ) {
		id3tag_album.remove( "まいにち" );
		if ( kouza.contains( "レベル１", Qt::CaseInsensitive) ) id3tag_album = "L1_" + id3tag_album.remove( "レベル１" );
		if ( kouza.contains( "レベル２", Qt::CaseInsensitive) ) id3tag_album = "L2_" + id3tag_album.remove( "レベル２" );
		if ( kouza.contains( "入門", Qt::CaseInsensitive) ) id3tag_album = "入門_" + id3tag_album.remove( "入門編" );
		if ( kouza.contains( "初級", Qt::CaseInsensitive) ) id3tag_album = "初級_" + id3tag_album.remove( "初級編" );
		if ( kouza.contains( "中級", Qt::CaseInsensitive) ) id3tag_album = "中級_" + id3tag_album.remove( "中級編" );
		if ( kouza.contains( "応用", Qt::CaseInsensitive) ) id3tag_album = "応用_" + id3tag_album.remove( "応用編" );
	}
	
	QStringList argumentsA = arguments0 + ffmpegHash[extension]
			.arg( filem3u8aA, dstPathA, id3tagTitleA, id3tag_album,  nendo ).split(",");
	
	QStringList argumentsB = arguments1 + arguments0 + ffmpegHash[extension]
			.arg( filem3u8aA, dstPathA, id3tagTitleA, id3tag_album,  nendo ).split(",");
	QString tmp = outputDir + "tmp"  + "." + extension1;
	Error_mes = "";
	QString ffmpeg_Error;
	int retry = 5;
	
	for ( int i = 0 ; i < retry ; i++ ) {
		ffmpeg_Error = ffmpeg_process( argumentsA );
		if ( ffmpeg_Error == "" ) {
#ifdef QT4_QT5_WIN
			QFile::rename( dstPath, outputDir + outFileName );
#endif
			if ( (ui->checkBox_thumbnail->isChecked() || Utility::option_check( "-a1" )) && extension1 != "aac" && !Utility::option_check( "-a0" ) ) thumbnail_add( dstPathA, tmp, json_path );
			return true;
		}
		if ( ffmpeg_Error == "1" ) {
			emit critical( QString::fromUtf8( "ffmpeg起動エラー(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  Error_mes ) );		
			QFile::remove( dstPathA );
			return false;
		}
		if ( ffmpeg_Error == "2" ) { // キャンセルボタンが押されていたら、ファイルを削除してリターン
			QFile::remove( dstPathA );
			return false;
		}
		QThread::wait( 200 );
	}
				
	if ( ffmpeg_Error != "" ) { // エラー発生時はリトライ
		QFile::remove( dstPathA );
		ffmpeg_Error = ffmpeg_process( argumentsB );
		if ( ffmpeg_Error == "" ) {
#ifdef QT4_QT5_WIN
			QFile::rename( dstPath, outputDir + outFileName );
#endif
			if ( (ui->checkBox_thumbnail->isChecked() || Utility::option_check( "-a1" )) && extension1 != "aac" && !Utility::option_check( "-a0" ) ) thumbnail_add( dstPathA, tmp, json_path );
			return true;
		}
		if ( ffmpeg_Error == "1" ) {
			emit critical( QString::fromUtf8( "ffmpeg起動エラー(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  Error_mes ) );		
			QFile::remove( dstPathA );
			return false;
		}
		if ( ffmpeg_Error == "2" ) { // キャンセルボタンが押されていたら、ファイルを削除してリターン
			QFile::remove( dstPathA );
			return false;
		}
		if ( ffmpeg_Error == "3" ) { // エラー発生時はメッセージを表示し、出力ファイルを削除してリターン
			emit critical( QString::fromUtf8( "ffmpeg実行エラー(%3)：　%1　　%2" )
					.arg( kouza, yyyymmdd,  Error_mes ) );
			QFile::remove( dstPathA );
			return false;
		}
		if ( ffmpeg_Error != "" ) {
			emit critical( QString::fromUtf8( "レコーディング失敗：　%1　　%2" ).arg( kouza, yyyymmdd ) );
			QFile::remove( dstPathA );
			return false;
		}
	}
#ifdef QT4_QT5_WIN
	QFile::rename( dstPath, outputDir + outFileName );
#endif
	return true;
}

QString DownloadThread::ffmpeg_process( QStringList arguments ) {
	Error_mes = "";
	QProcess process;
	process.setProgram( ffmpeg );
	process.setArguments( arguments );
	
	process.start();
	if ( !process.waitForStarted( -1 ) ) {
		Error_mes = processError[process.error()];
		return "1";
	}

	// ユーザのキャンセルを確認しながらffmpegの終了を待つ
	while ( !process.waitForFinished( CancelCheckTimeOut ) ) {
		// キャンセルボタンが押されていたらffmpegをkillしてリターン
		if ( isCanceled ) {
			process.kill();
			return "2";
		}
		// 単なるタイムアウトは継続
		if ( process.error() == QProcess::Timedout )
			continue;
		if ( process.error()  != QProcess::Timedout ) {
		// エラー発生時はメッセージを表示し、出力ファイルを削除してリターン
			Error_mes = processError[process.error()];
			return "3";
		}
	}

	QString ffmpeg_Error;
	ffmpeg_Error.append(process.readAllStandardError());

	// ffmpeg終了ステータスに応じた処理をしてリターン
	if ( ffmpeg_Error.contains("HTTP error") || ffmpeg_Error.contains("Unable to open resource:") || ffmpeg_Error.contains("error") ) {
		Error_mes = "ffmpeg error";
		if ( ffmpeg_Error.contains("HTTP error") ) Error_mes = "HTTP error";
		if ( ffmpeg_Error.contains("Unable to open resource:") ) Error_mes = "Unable to open resource";
		process.kill();
		return "3";
	}
	if ( process.exitCode() ) {
		process.kill();
		return "4";	
	}
	process.kill();
	process.close();
	return "";
}




QString DownloadThread::paths[] = {
	"english/basic0", "english/basic1", "english/basic2", "english/basic3",
	"english/timetrial",  "english/enjoy", "english/kaiwa", "english/business1",
	"null", "english/vr-radio",
//	"english/business2", "english/everybody", "english/gendai", "english/enjoy", 
	"null_optional1", "null_optional2", "null_optional3", "null_optional4",
	"null_optional5", "null_optional6", "null_optional7", "null_optional8"
};

QString DownloadThread::json_paths[] = {
	"GGQY3M1929_01", "148W8XX226_01", "83RW6PK3GG_01", "B2J88K328M_01",
	"8Z6XJ6J415_01", "BR8Z3NX7XM_01", "PMMJ59J6N2_01", "368315KKP8_01", 
	"77RQWQX1L6_01", "7Y5N5G674R_01",
	"XQ487ZM61K_01", "N8PZRZ9WQY_01", "LJWZP7XVMX_01", "NRZWXVGQ19_01",
	"YRLK72JZ7Q_01", "0943_01", "983PKQPYN7_01", "LR47WW9K14_01"
};


QString DownloadThread::paths2[] = {
	"english/basic0", "english/basic1", "english/basic2", "english/basic3",
	"english/timetrial", "english/kaiwa", "english/business1", "english/enjoy",
	"french/kouza", "french/kouza2", "german/kouza", "german/kouza2",
	"spanish/kouza", "spanish/kouza2", "italian/kouza", "italian/kouza2",
	"russian/kouza","russian/kouza2", "chinese/kouza", "chinese/stepup",
	"hangeul/kouza", "hangeul/stepup", 
	"NULL"
};

QString DownloadThread::json_paths2[] = { 
	"小学生の基礎英語", "中学生の基礎英語 レベル１", "中学生の基礎英語 レベル２", "中高生の基礎英語 in English",
	"英会話タイムトライアル", "エンジョイ・シンプル・イングリッシュ", "ラジオ英会話", "ラジオビジネス英語", 
	"ニュースで学ぶ「現代英語」", "ボキャブライダー", 
	"まいにち中国語", "ステップアップ中国語", "まいにちハングル講座", "ステップアップ ハングル講座",
	"まいにちドイツ語入門", "まいにちドイツ語応用", "まいにちフランス語入門", "まいにちフランス語応用",
	"NULL"
};

QMap<QString, QString> DownloadThread::map = { 
	{ "小学生の基礎英語", "english/basic0" },		// 小学生の基礎英語
	{ "中学生の基礎英語 レベル１", "english/basic1" },		// 中学生の基礎英語 レベル1
	{ "中学生の基礎英語 レベル２", "english/basic2" },		// 中学生の基礎英語 レベル2
	{ "中高生の基礎英語 in English", "english/basic3" },		// 中高生の基礎英語 in English
	{ "英会話タイムトライアル", "english/timetrial" },	// 英会話タイムトライアル
	{ "ラジオ英会話", "english/kaiwa" },		// ラジオ英会話
	{ "ラジオビジネス英語", "english/business1" },	// ラジオビジネス英語
	{ "エンジョイ・シンプル・イングリッシュ", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
	{ "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
	{ "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
	{ "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
	{ "B2J88K328M_01", "english/basic3" },		// 中高生の基礎英語 in English
	{ "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
	{ "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
	{ "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
	{ "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
	{ "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
	{ "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
	{ "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
	{ "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
	{ "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
	{ "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
	{ "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
	{ "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
	{ "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
	{ "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
	{ "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
	{ "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
	{ "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
	{ "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
	{ "XQ487ZM61K_01", "french/kouza3" },		// まいにちフランス語 入門編/初級編/応用編
	{ "N8PZRZ9WQY_01", "german/kouza3" },		// まいにちドイツ語 入門編/初級編/応用編
	{ "NRZWXVGQ19_01", "spanish/kouza3" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
	{ "LJWZP7XVMX_01", "italian/kouza3" },		// まいにちイタリア語 入門編/初級編/応用編
	{ "YRLK72JZ7Q_01", "russian/kouza3" },		// まいにちロシア語 入門編/初級編/応用編
	{ "983PKQPYN7_s1", "chinese/kouza4" },		// まいにち中国語
	{ "LR47WW9K14_s1", "hangeul/kouza4" },		// まいにちハングル講座
};
	
QMultiMap<QString, QString> DownloadThread::multimap = { 
	{ "小学生の基礎英語", "english/basic0" },		// 小学生の基礎英語
	{ "中学生の基礎英語 レベル１", "english/basic1" },		// 中学生の基礎英語 レベル1
	{ "中学生の基礎英語 レベル２", "english/basic2" },		// 中学生の基礎英語 レベル2
	{ "中高生の基礎英語 in English", "english/basic3" },		// 中高生の基礎英語 in English
	{ "英会話タイムトライアル", "english/timetrial" },	// 英会話タイムトライアル
	{ "ラジオ英会話", "english/kaiwa" },		// ラジオ英会話
	{ "ラジオビジネス英語", "english/business1" },	// ラジオビジネス英語
	{ "エンジョイ・シンプル・イングリッシュ", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
	{ "GGQY3M1929_01", "english/basic0" },		// 小学生の基礎英語
	{ "148W8XX226_01", "english/basic1" },		// 中学生の基礎英語 レベル1
	{ "83RW6PK3GG_01", "english/basic2" },		// 中学生の基礎英語 レベル2
	{ "B2J88K328M_01", "english/basic3" },		// 中高生の基礎英語 in English
	{ "8Z6XJ6J415_01", "english/timetrial" },	// 英会話タイムトライアル
	{ "PMMJ59J6N2_01", "english/kaiwa" },		// ラジオ英会話
	{ "368315KKP8_01", "english/business1" },	// ラジオビジネス英語
	{ "BR8Z3NX7XM_01", "english/enjoy" },		// エンジョイ・シンプル・イングリッシュ
	{ "XQ487ZM61K_x1", "french/kouza" },		// まいにちフランス語 入門編
	{ "XQ487ZM61K_y1", "french/kouza2" },		// まいにちフランス語 応用編
	{ "N8PZRZ9WQY_x1", "german/kouza" },		// まいにちドイツ語 入門編
	{ "N8PZRZ9WQY_y1", "german/kouza2" },		// まいにちドイツ語 応用編
	{ "NRZWXVGQ19_x1", "spanish/kouza" },		// まいにちスペイン語 入門編
	{ "NRZWXVGQ19_y1", "spanish/kouza2" },		// まいにちスペイン語 応用編
	{ "LJWZP7XVMX_x1", "italian/kouza" },		// まいにちイタリア語 入門編
	{ "LJWZP7XVMX_y1", "italian/kouza2" },		// まいにちイタリア語 応用編
	{ "YRLK72JZ7Q_x1", "russian/kouza" },		// まいにちロシア語 入門編
	{ "YRLK72JZ7Q_y1", "russian/kouza2" },		// まいにちロシア語 応用編
	{ "983PKQPYN7_01", "chinese/kouza" },		// まいにち中国語
	{ "MYY93M57V6_01", "chinese/stepup" },		// ステップアップ中国語
	{ "LR47WW9K14_01", "hangeul/kouza" },		// まいにちハングル講座
	{ "NLJM5V3WXK_01", "hangeul/stepup" },		// ステップアップ ハングル講座
	{ "XQ487ZM61K_01", "french/kouza" },		// まいにちフランス語 入門編/初級編/応用編
	{ "XQ487ZM61K_01", "french/kouza2" },		// まいにちフランス語 入門編/初級編/応用編
	{ "N8PZRZ9WQY_01", "german/kouza" },		// まいにちドイツ語 入門編/初級編/応用編
	{ "N8PZRZ9WQY_01", "german/kouza2" },		// まいにちドイツ語 入門編/初級編/応用編
	{ "NRZWXVGQ19_01", "spanish/kouza" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
	{ "NRZWXVGQ19_01", "spanish/kouza2" },		// まいにちスペイン語 入門編/初級編/中級編/応用編
	{ "LJWZP7XVMX_01", "italian/kouza" },		// まいにちイタリア語 入門編/初級編/応用編
	{ "LJWZP7XVMX_01", "italian/kouza2" },		// まいにちイタリア語 入門編/初級編/応用編
	{ "YRLK72JZ7Q_01", "russian/kouza" },		// まいにちロシア語 入門編/初級編/応用編
	{ "YRLK72JZ7Q_01", "russian/kouza2" },		// まいにちロシア語 入門編/初級編/応用編
	{ "983PKQPYN7_s1", "chinese/kouza" },		// まいにち中国語
	{ "983PKQPYN7_s1", "chinese/stepup" },		// ステップアップ中国語
	{ "LR47WW9K14_s1", "hangeul/kouza" },		// まいにちハングル講座
	{ "LR47WW9K14_s1", "hangeul/stepup" },		// ステップアップ ハングル講座
};	

QMultiMap<QString, QString> DownloadThread::multimap1 = { 
	{ "983PKQPYN7_s1", "983PKQPYN7_01" },		// まいにち中国語
	{ "983PKQPYN7_s1", "MYY93M57V6_01" },		// ステップアップ中国語
	{ "LR47WW9K14_s1", "LR47WW9K14_01" },		// まいにちハングル講座
	{ "LR47WW9K14_s1", "NLJM5V3WXK_01" },		// ステップアップ ハングル講座
	{ "6LPPKP6W8Q_s1", "6LPPKP6W8Q_01" },		// やさしい日本語
	{ "6LPPKP6W8Q_s1", "D6RM27PGVM_01" },		// Learn Japanese from the News
	{ "6LPPKP6W8Q_s1", "4MY6Q8XP88_01" },		// Living in Japan
};	

void DownloadThread::run() {
	QAbstractButton* checkbox[] = {
		ui->toolButton_basic0, ui->toolButton_basic1, ui->toolButton_basic2, ui->toolButton_basic3,
		ui->toolButton_timetrial, ui->toolButton_enjoy, ui->toolButton_kaiwa, ui->toolButton_business1,
		ui->toolButton_gendai, ui->toolButton_vrradio,
		ui->toolButton_optional1, ui->toolButton_optional2, 
		ui->toolButton_optional3, ui->toolButton_optional4,
		ui->toolButton_optional5, ui->toolButton_optional6, 
		ui->toolButton_optional7, ui->toolButton_optional8, 
		NULL
	};

	if ( MainWindow::id_flag ) { id_list(); MainWindow::id_flag = false; return; }

	if ( !isFfmpegAvailable( ffmpeg ) )
		return;

	QStringList ProgList;	
	bool nogui_flag = Utility::nogui();
	if ( nogui_flag ) {
		ProgList = Utility::optionList();
		if ( ProgList[0] == "return" ) return;
		if ( ProgList[0] != "erorr" ) {			// -nogui + 番組IDオプション
			for ( int i = 0; i < ProgList.count() ; i++ ) {
			
				QString Xml_koza = "";
		   		Xml_koza = map.value( ProgList[i] );
				if ( Xml_koza == "" || !(Utility::option_check( "-z" )) || Utility::option_check( "-b" ) ) {
				   	QStringList fileList2;
					QStringList kouzaList2;
					QStringList file_titleList;
					QStringList hdateList1;
					QStringList yearList;
					
					QStringList site_id_List; site_id_List.clear();
					if ( multimap1.contains( ProgList[i] ) )
						site_id_List += multimap1.values( ProgList[i] );
					else
						site_id_List += ProgList[i];
					for ( int n = 0; n < site_id_List.count() && !isCanceled; n++ ){
						std::tie( fileList2, kouzaList2, file_titleList, hdateList1, yearList ) = getJsonData( site_id_List[n] );
						QStringList hdateList2 = one2two( hdateList1 );
						QStringList dupnmbList;
						dupnmbList.clear() ;
						int k = 1;
						for ( int ii = 0; ii < hdateList2.count() ; ii++ ) dupnmbList += "" ;
						for ( int ii = 0; ii < hdateList2.count() - 1 ; ii++ ) {
							if ( hdateList2[ii] == hdateList2[ii+1] ) {
								if ( k == 1 ) dupnmbList[ii].replace( "", "-1" );
								k = k + 1;
								QString dup = "-" + QString::number( k );
								dupnmbList[ii+1].replace( "", dup );
							} else {
								k = 1;
							}
						}
				
						if ( fileList2.count() && fileList2.count() == kouzaList2.count() && fileList2.count() == hdateList2.count() ) {
							for ( int j = 0; j < fileList2.count() && !isCanceled; j++ ){
								if ( fileList2[j] == "" || fileList2[j] == "null" ) continue;
								captureStream_json( kouzaList2[j], hdateList2[j], fileList2[j], yearList[j], file_titleList[j], dupnmbList[j], site_id_List[n], true );
							}
						}
					}
				}
				
				if ( Xml_koza != "" && (Utility::option_check( "-z" ) || Utility::option_check( "-b" ))) {
					QStringList Xml_koza_List; Xml_koza_List.clear();
					if ( multimap.contains( ProgList[i] ) )
						Xml_koza_List += multimap.values( ProgList[i] );
					else
						Xml_koza_List += Xml_koza;	   

					for ( int n = 0; n < Xml_koza_List.count() && !isCanceled; n++ ){
						Xml_koza = Xml_koza_List[n];				
				
//		     			int ik = 1;
//		     			if ( Xml_koza.contains( "kouza3" ) ) { ik = 2; Xml_koza.replace( "kouza3", "kouza" ); }
//		     			for ( int kk = 0 ; kk < ik ; kk++ ){
//		      				if ( kk == 1 ) Xml_koza = Xml_koza + "2";

#ifdef QT5
						QStringList fileList = getAttribute( prefix + Xml_koza + "/" + suffix, "@file" );
						QStringList kouzaList = getAttribute( prefix + Xml_koza + "/" + suffix, "@kouza" );
						QStringList hdateList = one2two( getAttribute( prefix + Xml_koza + "/" + suffix, "@hdate" ) );
						QStringList nendoList = getAttribute( prefix + Xml_koza + "/" + suffix, "@nendo" );
						QStringList dirList = getAttribute( prefix + Xml_koza + "/" + suffix, "@dir" );
#endif
#ifdef QT6

						QStringList fileList;
						QStringList kouzaList;
						QStringList hdateList1;
						QStringList nendoList;
						QStringList dirList;
						std::tie( fileList, kouzaList, hdateList1, nendoList, dirList ) = getAttribute1( prefix + Xml_koza + "/" + suffix );
						QStringList hdateList = one2two( hdateList1 );
#endif
						if ( fileList.count() && fileList.count() == kouzaList.count() && fileList.count() == hdateList.count() ) {
//						if ( Xml_koza == "NULL" && !(ui->checkBox_next_week2->isChecked()) )	continue;
							for ( int j = 0; j < fileList.count() && !isCanceled; j++ ){
								captureStream( kouzaList[j], hdateList[j], fileList[j], nendoList[j], dirList[j], "R", json_paths[i], true );
							}
						}
					}
				}				
				
				
			}
		return;
		}
	}
	
       for ( int i = 0; checkbox[i] && !isCanceled; i++ ) {
		QString site_id = json_paths[i];
		if ( MainWindow::name_map.contains( json_paths2[i] ) ) site_id = MainWindow::name_map.value( json_paths2[i] );
       
		optional1 = MainWindow::optional1;
		optional2 = MainWindow::optional2;
		optional3 = MainWindow::optional3;
		optional4 = MainWindow::optional4;
		optional5 = MainWindow::optional5;
		optional6 = MainWindow::optional6;
		optional7 = MainWindow::optional7;
		optional8 = MainWindow::optional8;
		if ( paths[i].right( 9 ).startsWith("optional1") ) site_id = optional1;
		if ( paths[i].right( 9 ).startsWith("optional2") ) site_id = optional2;
		if ( paths[i].right( 9 ).startsWith("optional3") ) site_id = optional3;
		if ( paths[i].right( 9 ).startsWith("optional4") ) site_id = optional4;
		if ( paths[i].right( 9 ).startsWith("optional5") ) site_id = optional5;
		if ( paths[i].right( 9 ).startsWith("optional6") ) site_id = optional6;
		if ( paths[i].right( 9 ).startsWith("optional7") ) site_id = optional7;
		if ( paths[i].right( 9 ).startsWith("optional8") ) site_id = optional8;
		
	    	QString pattern( "[A-Z0-9]{10}" );
    		pattern = QRegularExpression::anchoredPattern(pattern);
		if ( QRegularExpression(pattern).match( site_id ).hasMatch() ) site_id += "_01" ;

		if ( checkbox[i]->isChecked()) {
		   QString Xml_koza = "NULL";
		   Xml_koza = map.value( site_id );
		   		   	
//		   bool flag1 = false; bool flag2 = false;
//		   if ( (ui->checkBox_next_week2->isChecked() || site_id == "0000" ) && Xml_koza != "" ) flag1 = true;	// xml 放送翌週月曜から１週間
//		   if ( !(ui->checkBox_next_week2->isChecked()) || ( site_id != "0000" && Xml_koza == "" )) flag2 = true;	//json 放送後１週間
			
		   bool option_z_flag = false; option_z_flag = Utility::option_check( "-z" );			// nogui -z オプションあり　＝　true
		   bool option_b_flag = false; option_b_flag = Utility::option_check( "-b" );			// nogui -b オプションあり　＝　true
		   bool json_flag = false; if( site_id != "0000") json_flag = true;				// 放送後１週間の講座　＝　true
		   bool xml_flag  = false; if(Xml_koza != ""||multimap.contains( site_id )) xml_flag = true;	// 放送翌週月曜から１週間の講座　＝　true
		   bool pass_week = false; if(ui->checkBox_next_week2->isChecked()) pass_week = true;		// [前週]チェックボックスにチェック　＝　true
		   if( option_z_flag || option_b_flag ) pass_week = true;					// -nogui -z or -b オプションあり　＝　true	

		   
		   bool flag1 = false; bool flag2 = false; //bool flag3 = false; 
		   if ( !pass_week || ( json_flag && !xml_flag ) || option_b_flag ) flag1 = true;	//json 放送後１週間
		   if (( pass_week || !json_flag ) && xml_flag )  flag2 = true;	// xml 放送翌週月曜から１週間
		
		   if ( flag1 ) {
		   	QStringList fileList2;
			QStringList kouzaList2;
			QStringList file_titleList;
			QStringList hdateList1;
			QStringList yearList;
			QStringList site_id_List; site_id_List.clear();
			
			if ( multimap1.contains( site_id ) )
				site_id_List += multimap1.values( site_id );
			else
				site_id_List += site_id;
				
			for ( int n = 0; n < site_id_List.count() && !isCanceled; n++ ){

			std::tie( fileList2, kouzaList2, file_titleList, hdateList1, yearList ) = getJsonData( site_id_List[n] );
			QStringList hdateList2 = one2two( hdateList1 );
			QStringList dupnmbList;
			dupnmbList.clear() ;
			int k = 1;
			for ( int ii = 0; ii < hdateList2.count() ; ii++ ) dupnmbList += "" ;
			for ( int ii = 0; ii < hdateList2.count() - 1 ; ii++ ) {
				if ( hdateList2[ii] == hdateList2[ii+1] ) {
					if ( k == 1 ) dupnmbList[ii].replace( "", "-1" );
					k = k + 1;
					QString dup = "-" + QString::number( k );
					dupnmbList[ii+1].replace( "", dup );
				} else {
					k = 1;
				}
			}
				
			if ( fileList2.count() && fileList2.count() == kouzaList2.count() && fileList2.count() == hdateList2.count() ) {
					for ( int j = 0; j < fileList2.count() && !isCanceled; j++ ){
						if ( fileList2[j] == "" || fileList2[j] == "null" ) continue;
						captureStream_json( kouzaList2[j], hdateList2[j], fileList2[j], yearList[j], file_titleList[j], dupnmbList[j], site_id_List[n], false );
					}
			}
			}
		   }

		   if ( flag2 ) {
			QStringList Xml_koza_List; Xml_koza_List.clear();
			
			if ( multimap.contains( site_id ) )
				Xml_koza_List += multimap.values( site_id );
			else
				Xml_koza_List += Xml_koza;	   
//		     int ik = 1;
//		     if ( Xml_koza.contains( "kouza3" ) ) { ik = 2; Xml_koza.replace( "kouza3", "kouza" ); }
//		     for ( int kk = 0 ; kk < ik ; kk++ ){
//		      if ( kk == 1 ) Xml_koza = Xml_koza + "2";
		     for ( int n = 0; n < Xml_koza_List.count() && !isCanceled; n++ ){
		      Xml_koza = Xml_koza_List[n];
#ifdef QT5
			QStringList fileList = getAttribute( prefix + Xml_koza + "/" + suffix, "@file" );
			QStringList kouzaList = getAttribute( prefix + Xml_koza + "/" + suffix, "@kouza" );
			QStringList hdateList = one2two( getAttribute( prefix + Xml_koza + "/" + suffix, "@hdate" ) );
			QStringList nendoList = getAttribute( prefix + Xml_koza + "/" + suffix, "@nendo" );
			QStringList dirList = getAttribute( prefix + Xml_koza + "/" + suffix, "@dir" );
#endif
#ifdef QT6
		   	QStringList fileList;
			QStringList kouzaList;
			QStringList hdateList1;
			QStringList nendoList;
			QStringList dirList;
			std::tie( fileList, kouzaList, hdateList1, nendoList, dirList ) = getAttribute1( prefix + Xml_koza + "/" + suffix );
			QStringList hdateList = one2two( hdateList1 );
#endif
			if ( fileList.count() && fileList.count() == kouzaList.count() && fileList.count() == hdateList.count() && ( pass_week || site_id == "0000") ) {
//			     if ( Xml_koza == "NULL" && !(pass_week) )	continue;
//				if ( true /*ui->checkBox_this_week->isChecked()*/ ) {
					for ( int j = 0; j < fileList.count() && !isCanceled; j++ ){
						QString RR = "R";
						if ( site_id == "0000" )  RR = "G";
						captureStream( kouzaList[j], hdateList[j], fileList[j], nendoList[j], dirList[j], RR, json_paths[i], false );
					}
//				}
			}
		     }
		   }
		}		   
	  }
	
	//if ( !isCanceled && ui->checkBox_shower->isChecked() )
		//downloadShower();

	//if ( !isCanceled && ui->checkBox_14->isChecked() )
		//downloadENews( false );

	//if ( !isCanceled && ui->checkBox_15->isChecked() )
		//downloadENews( true );

	emit current( "" );
	//キャンセル時にはdisconnectされているのでemitしても何も起こらない
	emit information( QString::fromUtf8( "レコーディング作業が終了しました。" ) );
}
