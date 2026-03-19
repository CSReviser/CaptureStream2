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
#include "clicontroller.h"
#include "settings.h"
#include "commandlineparser.h"
#include "utility.h"

#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QIcon>
#include <QScreen>
#include <QDebug>
#include <QFont>



int main(int argc, char *argv[])
{
/*
#if defined(QT_NO_DEBUG)
    // ログ出力先の設定（これはQtに依存しないので最初でOK）
#ifdef Q_OS_WIN
    const char* nullDevice = "nul";
#else
    const char* nullDevice = "/dev/null";
#endif
    freopen(nullDevice, "a", stdout);
    freopen(nullDevice, "a", stderr);
#endif
*/

    // ★ Qtを作る前に最小パース
    SimpleCliOptions simple = CommandLineParser::parseSimple(argc, argv);

    // =========================================================
    // CLI MODE
    // =========================================================
    if (simple.nogui) {
    fprintf(stderr, ">>> Entering CLI Mode <<<\n");
        QCoreApplication app(argc, argv);

        // 1. appができてからSettingsを読み込む
        Settings::instance().load();
 
        CLIController cli(Settings::instance(), argc, argv);

        return cli.run();

    } else {
    // =========================================================
    // GUI MODE
    // =========================================================

        // 高解像度設定(High DPI)はQApplication生成前に行う（Qt5/6の仕様）
//        qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
//        qputenv("QT_SCALE_FACTOR", "1");

        QApplication a(argc, argv);
        
    QScreen* screen = QGuiApplication::primaryScreen();

    qDebug() << "\n===== DPI / Scale Info =====";
    qDebug() << "Screen:" << screen->name();

    qDebug() << "Logical DPI:" << screen->logicalDotsPerInch();
    qDebug() << "Physical DPI:" << screen->physicalDotsPerInch();
    qDebug() << "Device Pixel Ratio:" << screen->devicePixelRatio();

    QFont f = QApplication::font();
    qDebug() << "Font:" << f.family()
             << "PointSize:" << f.pointSizeF();

    qDebug() << "============================\n";

        // 1. appができてからSettingsを読み込む
        Settings::instance().load();

        // 2. 二重起動チェック
        if (!Utility::tryLockFile()) {
            return 0; 
        }
        QFont font = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
        a.setFont(font);
        // 3. 画面表示
        MainWindow w(Settings::instance());
        QGuiApplication::setWindowIcon(QIcon(":icon.png"));
        w.show();
        
        return a.exec();
    }
}

