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
#pragma once
#include <QObject>
#include <QMap>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QNetworkAccessManager;
class QNetworkReply;

class ProgramRepository : public QObject
{
    Q_OBJECT

public:
    static ProgramRepository& instance();

    // 取得した番組一覧
    QMap<QString, QString> id_map;        // url_id → program_name
    QMap<QString, QString> name_map;      // program_name → url_id
    QMap<QString, QString> thumbnail_map; // url_id → thumbnail_url

    // 起動後にネットから番組一覧を取得
    void updatePrograms();
    
    void start();          // 起動（非同期開始）
    bool waitUntilReady(); // CLI用同期待機
    bool isReady() const;
    
    QString getProgramNameById(const QString& url);

signals:
    void programListUpdated();  // GUI に通知したい場合

private:
    ProgramRepository();
    Q_DISABLE_COPY(ProgramRepository)
    void fetchKozaSeries(const QStringList& kozaList);
    void checkIfAllRequestsFinished();
    QString fetchProgramJson(const QString& url);
    std::tuple<QString, QString> parseProgramJson(const QString& str);
    void normalizeWidth(QString& s);
    QString formatProgramName( const QString& title, const QString& corner_name );
    QString buildBaseProgramName( const QString& title, const QString& corner_name);
    QString normalizeProgramName(QString attribute);
    
    bool m_started = false;
    bool m_ready   = false;
    int m_pendingRequests = 0;
};






