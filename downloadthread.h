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

#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>
#include <QStringList>
#include <QHash>
#include <QProcess>
#include <tuple>

#include "mainwindow.h"

class DownloadThread : public QThread {
	Q_OBJECT

public:
	DownloadThread( Ui::MainWindowClass* ui );
	~DownloadThread() {}
	void cancel() { isCanceled = true; }
	void id_list();
	
	static QString opt_title1;
	static QString opt_title2;
	static QString opt_title3;
	static QString opt_title4;
	static QString opt_title5;
	static QString opt_title6;
	static QString opt_title7;
	static QString opt_title8;
	static QString opt_title9;
	static QString opt_titlea;
	static QString nendo1;
	static QString nendo2;
	static QDate nendo_end_date1;
	static QDate nendo_end_date2;
	static QDate nendo_start_date1;
	static QDate nendo_start_date2;
	static QDate nendo_start_date;
	static QDate zenki_end_date;
	static QDate kouki_start_date;
	static QDate nendo_end_date;

protected:
	void run();

signals:
	void critical( QString message );
	void information( QString message );
	void current( QString );
	void messageWithoutBreak( QString );

private:
//	QStringList getAttribute( QString url, QString attribute );
//	QStringList getAttribute( const QString &url, const QString &attribute );
//	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getAttribute1( QString url );
	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getAttribute1( const QString &url );
	QString getAttribute2( QString url, QString attribute );
//	QStringList getJsonData( QString url, QString attribute );
	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getJsonData( const QString& urlInput );
	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getJsonData1( QString url );
	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getJsonData2( QString url );
	QStringList getJsonData_ouch( QString url, QString attribute );
	QString getJsonFile( QString jsonUrl );
	bool runFfmpeg(QProcess &process, const QString &ffmpeg, const QStringList &args, const QString &dstPath, const QString &kouza, const QString &yyyymmdd);
	bool checkExecutable( QString path );
	bool isFfmpegAvailable( QString& path );
	bool istestAvailable( QString& path );
	bool checkOutputDir( QString dirPath );
	void downloadENews( bool re_read );
	QString ffmpeg_process( QStringList arguments );
	void thumbnail_add( const QString &dstPath, const QString &tmp, const QString &json_path );
	
	bool captureStream( QString kouza, QString hdate, QString file, QString nendo, QString dir, QString this_week, QString json_path, bool nogui_flag );
	bool captureStream_json( QString kouza, QString hdate, QString file, QString nendo, QString title, QString dupnmb, QString json_path, bool nogui_flag );
	
	QString formatName( QString format, QString kouza, QString hdate, QString file, QString nendo, QString dupnmb, bool checkIllegal );
	QStringList getElements( QString url, QString path );
	void downloadShower();
	
	QDate getBroadcastDate(int fiscalYear, int broadcastMonth, int broadcastDay);
	QDate getNHKLectureStartDate(int fiscalYear);
	int getNHKLectureFiscalYear(const QDate& date);
	QStringList formatBroadcastDates(const QStringList &dates);
	QString getFfmpegFolder(const QString &ffmpegPath);	
	QString formatQDate(const QDate &date, bool year4Digits, bool monthTwoDigits, bool dayTwoDigits, const QString &separator);
	QStringList extractAllDates( const QString &contentId);
	QString extractNthDate( const QString &contentId, int index);
	QStringList filteredNames(const QStringList& sourceList, const QStringList& keywords, const QString& exclude);

	Ui::MainWindowClass* ui;
	bool isCanceled;
	bool failed1935;
	static QString Error_mes;

	static QString paths[];
	static QString paths2[];
	static QString paths3[];
	static QString json_paths[];
	static QString json_paths2[];
	static QMap<QString, QString> map;
	static QMultiMap<QString, QString> multimap;
	static QMultiMap<QString, QString> multimap1;
	static QString prefix;
	static QString prefix1;
	static QString prefix2;
	static QString prefix3;
	static QString suffix;
	static QString suffix1;
	static QString suffix2;
	static QString suffix3;
	static QString json_prefix;
	static QString Json_url;

	static QString flv_host;
	static QString flv_app;
	static QString flv_service_prefix;
	static QString Xml_koza;

	static QString flvstreamer;
	static QString ffmpeg;
	static QString test;
	static QString scramble;
	static QStringList malformed;
	
	static QString optional1;
	static QString optional2;
	static QString optional3;
	static QString optional4;
	static QString optional5;
	static QString optional6;
	static QString optional7;
	static QString optional8;
	static QString special1;
	static QString special2;
	static QString special3;
	static QString special4;

	static QHash<QString, QString> ffmpegHash;
	static QHash<QProcess::ProcessError, QString>processError;
	
//	static QStringList fileListX;
//	static QStringList kouzaListX;
//	static QStringList file_titleListX;
//	static QStringList hdateListX;
//	static QStringList yearListX;

};

#endif // DOWNLOADTHREAD_H
