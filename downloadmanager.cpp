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

#include "downloadmanager.h"

#include <QRegularExpression>
#include <QFileInfo>
#include <QStringList>
#include <QDate>
#include <QThread>
#include <QtDebug>
#include <QTimer>
#include <QMutexLocker>

#define SEARCH_20100323 "http://www.google.co.jp/search?q=video_player_wide.swf+site:cgi2.nhk.or.jp&hl=ja&lr=lang_ja&num=100&filter=0&start=0"
#define SEARCH_20090330 "http://www.google.co.jp/search?q=video_player.swf+site:cgi2.nhk.or.jp&hl=ja&lr=lang_ja&num=100&filter=0&start=0"
#define SEARCH_AT_ONCE 100
#define VIDEO_PLAYER_WIDE "video_player_wide.swf"

DownloadManager::DownloadManager( bool _reread, bool _past ) : reread(_reread), past(_past) {
	connect( &manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinished(QNetworkReply*)) );
}

void DownloadManager::singleShot() {
	QTimer::singleShot( 0, this, SLOT(execute()) );
	eventLoop.exec();
}

void DownloadManager::doDownload( const QUrl &url ) {
	QNetworkRequest request( url );
	QNetworkReply *reply = manager.get( request );

	QMutexLocker locker( &mutex );
	currentDownloads.append( reply );
}

void DownloadManager::execute() {
	QDate today = QDate::currentDate();
	QDate from( 2009, 3, 30 );	//ダウンロード可能な一番古い日付

	if ( !reread || !past )
		from = today.addDays( -7 );

	for ( QDate i = today; i >= from; i = i.addDays( -1 ) ) {
		if ( i.dayOfWeek() >= 1 && i.dayOfWeek() <= 5 ) {
			QUrl url( "http://cgi2.nhk.or.jp/e-news/news/index.cgi?ymd=" + i.toString( "yyyyMMdd" ) );
			doDownload( url );
		}
	}

	if ( !reread && past ) {
		doDownload( QUrl(SEARCH_20100323 ) );
		doDownload( QUrl(SEARCH_20090330 ) );
	}
}


void DownloadManager::downloadFinished(QNetworkReply *reply) {
	QMutexLocker locker(&mutex);

	QUrl url = reply->url();

	if (reply->error()) {
		// エラーハンドリング（必要に応じて有効化）
		// emit critical("ページ(" + url.toEncoded() + ")を取得できませんでした: " + reply->errorString());
	} else {
		QString urlStr = url.toString();
		QString page = QString::fromUtf8(reply->readAll());

		if (!reread && urlStr.startsWith("http://www.google.co.jp/")) {
			QString rx = R"(http://cgi2.nhk.or.jp/e-news/swfp/video_player(?:_wide)?\.swf\.type=real&amp;m_name=([^\"]*))";
			QRegularExpression regexp(rx, QRegularExpression::CaseInsensitiveOption);

			QList<QString> tempList;
			QRegularExpressionMatchIterator it = regexp.globalMatch(page);
			while (it.hasNext()) {
				QRegularExpressionMatch match = it.next();
				QString matchStr = match.captured(1);
				if (!flvList.contains(matchStr))
					tempList << matchStr;
			}

			QRegularExpression newPlayer(VIDEO_PLAYER_WIDE);
			if (newPlayer.match(urlStr).hasMatch())
				flvList << tempList;
			else
				flvListBefore20100323 << tempList;

			if (tempList.count() >= SEARCH_AT_ONCE) {
				QRegularExpression prefix(R"(^(.*&start=)(\d+)$)", QRegularExpression::CaseInsensitiveOption);
				QRegularExpressionMatch match = prefix.match(urlStr);
				if (match.hasMatch()) {
					QString cap1 = match.captured(1);
					int cap2 = match.captured(2).toInt();

					QUrl newUrl(cap1 + QString::number(cap2 + SEARCH_AT_ONCE));
					QNetworkRequest request(newUrl);
					QNetworkReply* newReply = manager.get(request);
					currentDownloads.append(newReply);
				}
			}
		} else {
			QString rx = reread
				? R"(mp3player\.swf\.type=real&m_name=([^&\"]*))"
				: R"(video_player_wide\.swf\.type=real&m_name=([^\"]*))";
			QRegularExpression regexp(rx, QRegularExpression::CaseInsensitiveOption);
			QRegularExpressionMatch match = regexp.match(page);
			if (match.hasMatch()) {
				QString matchStr = match.captured(1);
				if (!flvList.contains(matchStr))
					flvList << matchStr;
			}
		}
	}

	currentDownloads.removeAll(reply);
	reply->deleteLater();

	if (currentDownloads.isEmpty()) {
		manager.disconnect();
		eventLoop.exit();
	}
}


void DownloadManager::downloadFinished( QNetworkReply *reply ) {
	QMutexLocker locker( &mutex );

	QUrl url = reply->url();

#ifdef QT5
	if (reply->error()) {
		//emit critical( QString::fromUtf8( "ページ(" ) + url.toEncoded().constData() +
					   //QString::fromUtf8( ")を取得できませんでした: " ) + qPrintable( reply->errorString() ) );
	} else {
		QString urlStr = url.toString();
		if ( !reread && urlStr.startsWith( "http://www.google.co.jp/" ) ) {
			QString page = QString::fromUtf8( reply->readAll().constData() );
			QString rx = "http://cgi2.nhk.or.jp/e-news/swfp/video_player(?:_wide)?.swf.type=real&amp;m_name=([^\"]*)";
			QRegExp regexp( rx, Qt::CaseInsensitive );
			QList<QString> tempList;
			int pos = 0;
			while ( ( pos = regexp.indexIn( page, pos ) ) != -1) {
				if ( !flvList.contains( regexp.cap( 1 ) ) )
					tempList << regexp.cap( 1 );
				pos += regexp.matchedLength();
			}
			QRegExp newPlayer( VIDEO_PLAYER_WIDE );
			if ( newPlayer.indexIn( urlStr, 0 ) != -1 )
				flvList << tempList;
			else
				flvListBefore20100323 << tempList;
			if ( tempList.count() >= SEARCH_AT_ONCE ) {
				QRegExp prefix( "^(.*&start=)(\\d+)$", Qt::CaseInsensitive );
				if ( prefix.indexIn( urlStr, 0 ) != -1 ) {
					QString cap1 = prefix.cap( 1 );
					int cap2 = prefix.cap( 2 ).toInt();
					QUrl url( cap1 + QString::number( cap2 + SEARCH_AT_ONCE ) );
					QNetworkRequest request( url );
					QNetworkReply* reply = manager.get( request );
					currentDownloads.append( reply );
				}
			}
		} else {
			QString page( reply->readAll() );
			QString rx = reread ? "mp3player.swf.type=real&m_name=([^&\"]*)" : "video_player_wide.swf.type=real&m_name=([^\"]*)";
			QRegExp regexp( rx, Qt::CaseInsensitive );
			if ( regexp.indexIn( page ) > -1 && !flvList.contains( regexp.cap( 1 ) ) )
				flvList << regexp.cap( 1 );
		}
	}
#endif

	currentDownloads.removeAll(reply);
	reply->deleteLater();

	if (currentDownloads.isEmpty()) {
		manager.disconnect();
		eventLoop.exit();
	}
}
