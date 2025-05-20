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

#include "mainwindow.h"
#include "utility.h"
#include "qt4qt5.h"

#include <QApplication>
#include <QStandardPaths>
#include <stdio.h>

int main(int argc, char *argv[])
{
	qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
	qputenv("QT_SCALE_FACTOR", "1");
#if defined(QT_NO_DEBUG)
#ifdef QT4_QT5_WIN
	const char* null = "nul";
#else
	const char* null = "/dev/null";
#endif
	freopen( null, "a", stdout );
	freopen( null, "a", stderr );
#endif
	
	QApplication a(argc, argv);
	MainWindow w;
	if( !Utility::tryLockFile() )  return 1;
	QGuiApplication::setWindowIcon(QIcon(":icon.png"));
	Utility::nogui() ? w.download() : w.show();
	return a.exec();
}
