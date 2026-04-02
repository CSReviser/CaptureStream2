/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2026 CSReviser Team

	This file is part of CaptureStream2, the recorder to support HLS for 
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

#include "networkclient.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QUrl>


NetworkClient::NetworkClient(QObject* parent)
    : QObject(parent)
{
}

QNetworkReply* NetworkClient::get(const QUrl& url)
{
    QNetworkRequest request(url);
    return m_manager.get(request);
}

QByteArray NetworkClient::getSync(
    const QUrl& url,
    int timeoutMs,
    int maxRetry)
{
    QNetworkRequest request(url);

    // NHK API 対策（User-Agent 必須）
    request.setHeader(QNetworkRequest::UserAgentHeader,
                      "NetworkClient/1.0");

    int wait = timeoutMs;

    for (int i = 0; i < maxRetry; ++i) {

        QEventLoop loop;
        QNetworkReply* reply = m_manager.get(request);

        QTimer timer;
        timer.setSingleShot(true);

        connect(reply, &QNetworkReply::finished,
                &loop, &QEventLoop::quit);

        connect(&timer, &QTimer::timeout,
                &loop, &QEventLoop::quit);

        timer.start(wait);
        loop.exec();

        QByteArray data;

        bool ok = reply->isFinished()
               && reply->error() == QNetworkReply::NoError;

        // HTTP ステータスコードも確認
        if (ok) {
            int status = reply->attribute(
                QNetworkRequest::HttpStatusCodeAttribute).toInt();

            if (status == 200) {
                data = reply->readAll();
            }
        } else {
            reply->abort();
        }

        reply->deleteLater();

        if (!data.isEmpty())
            return data;

        // バックオフ（指数的）
        wait = qMin(wait * 2, 5000);
    }

    return QByteArray();
}
