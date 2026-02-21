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

#include "mainwindow.h"
#include "settings.h"
#include "runtimeconfig.h"
#include "utility.h"
#include "qt4qt5.h"

#include <QApplication>
#include <QStandardPaths>
#include <stdio.h>
#include <QTimer>

int main(int argc, char *argv[])
{
#if defined(QT_NO_DEBUG)
#ifdef QT4_QT5_WIN
	const char* null = "nul";
#else
	const char* null = "/dev/null";
#endif
	freopen( null, "a", stdout );
	freopen( null, "a", stderr );
#endif

	QCoreApplication app(argc, argv);

	// ★ Repositoryをアプリとして起動（待たない）
	ProgramRepository::instance().start();

	// Settings（永続データ）を読み込む
	Settings::instance().load();
	
    if (Utility::nogui()) {
        // CLIだけ待つ
        if (!ProgramRepository::instance().waitUntilReady()) {
            qCritical() << "Failed to initialize program repository";
            return 1;
        }

        CLIController cli(settings, argc, argv);
        return cli.run();
    } else {   
    	qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
	qputenv("QT_SCALE_FACTOR", "1");
	QApplication a(argc, argv);
	// 2. 二重起動チェック（MainWindowを作る前に！）
	// ここで失敗したら即終了
	if (!Utility::tryLockFile()) {
	    return 0; 
	}
	// MainWindow に Settings を渡す
	MainWindow w(Settings::instance());
        QGuiApplication::setWindowIcon(QIcon(":icon.png"));
        w.show();
    }
	return a.exec();
	
}


//	if( !Utility::tryLockFile() )  return 1;
//	QGuiApplication::setWindowIcon(QIcon(":icon.png"));
//	Utility::nogui() ? w.download() : w.show();
