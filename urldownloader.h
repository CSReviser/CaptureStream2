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

#ifndef URLDOWNLOADER_H
#define URLDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

class UrlDownloader: public QObject {
	Q_OBJECT

public:
	UrlDownloader();
	void doDownload( const QUrl& url );
	const QByteArray contents() { return byteArray; }

private:
	QNetworkAccessManager manager;
	QUrl url;
	QEventLoop eventLoop;
	QByteArray byteArray;

public slots:
	void execute();
	void downloadFinished( QNetworkReply* reply );
};

#endif // URLDOWNLOADER_H
