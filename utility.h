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

#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QDate>

namespace Utility {
	QString applicationBundlePath();
	QString appLocaldataLocationPath();
	QString appConfigLocationPath();
	QString ConfigLocationPath();
	QString DownloadLocationPath();	
	QString HomeLocationPath();
	QString flare( QString& error );
	QString gnash( QString& error );
	QString wiki();
	QString getJsonFile( QString jsonUrl, int Timer );
	QString getProgram_name( QString url );
	std::tuple<QString, QString> getProgram_name1( QString strReply );
	QString getProgram_name3( QString title, QString corner_name );
	QString getLatest_version();
	std::tuple<QStringList, QStringList> getProgram_List();
	std::tuple<QStringList, QStringList> getProgram_List1( QString strReply );
	std::tuple<QStringList, QStringList, QStringList, QStringList, QStringList> getJsonData1( const QString& strReply, int json_ohyo );
	std::tuple<QString, QString, QString, QString> nogui_option( QString titleFormat, QString fileNameFormat, QString outputDir, QString extension );
	bool nogui();
	bool gui();
	bool option_check( QString option );
	bool multi_gui_flag_check();
	bool tryLockFile();
	void unLockFile();
	void remove_LockFile();
	QStringList optionList();
	QString getSettingsPath();
}

#endif // UTILITY_H
