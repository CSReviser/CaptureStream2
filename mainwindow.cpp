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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloadthread.h"
#include "customizedialog.h"
#include "scrambledialog.h"
#include "utility.h"
#include "qt4qt5.h"

#ifdef QT5
#include <QXmlQuery>
#include <QDesktopWidget>
#include <QRegExp>
#endif
#ifdef QT6
#include <QRegularExpression>
#endif
#include <QMessageBox>
#include <QByteArray>
#include <QStringList>
#include <QProcess>
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <QSettings>
#include <QInputDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QtNetwork>
#include <QTemporaryFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QDesktopServices>

#define SETTING_GROUP "MainWindow"
#define SETTING_GEOMETRY "geometry"
#define SETTING_WINDOWSTATE "windowState"
#define SETTING_MAINWINDOW_POSITION "Mainwindow_Position"
#define SETTING_SAVE_FOLDER "save_folder"
#define SETTING_SCRAMBLE "scramble"
#define SETTING_SCRAMBLE_URL1 "scramble_url1"
#define SETTING_KOZA_SEPARATION "koza_separation"
#define SETTING_FILE_NAME1 "FILE_NAME1"
#define SETTING_FILE_NAME2 "FILE_NAME2"
#define SETTING_TITLE1 "FILE_TITLE1"
#define SETTING_TITLE2 "FILE_TITLE2"
#define FILE_NAME1 "%k_%Y_%M_%D"
#define FILE_NAME2 "%k_%Y_%M_%D"
#define FILE_TITLE1 "%f"
#define FILE_TITLE2 "%k_%Y_%M_%D"
#define SCRAMBLE_URL1 "http://www47.atwiki.jp/jakago/pub/scramble.xml"
#define SCRAMBLE_URL2 "http://cdn47.atwikiimg.com/jakago/pub/scramble.xml"
#define X11_WINDOW_VERTICAL_INCREMENT 5
#define KOZA_SEPARATION_FLAG false

#define SETTING_OPTIONAL1 "optional1"
#define SETTING_OPTIONAL2 "optional2"
#define SETTING_OPTIONAL3 "optional3"
#define SETTING_OPTIONAL4 "optional4"
#define SETTING_OPTIONAL5 "optional5"
#define SETTING_OPTIONAL6 "optional6"
#define SETTING_OPTIONAL7 "optional7"
#define SETTING_OPTIONAL8 "optional8"
#define SETTING_OPT_TITLE1 "opt_title1"
#define SETTING_OPT_TITLE2 "opt_title2"
#define SETTING_OPT_TITLE3 "opt_title3"
#define SETTING_OPT_TITLE4 "opt_title4"
#define SETTING_OPT_TITLE5 "opt_title5"
#define SETTING_OPT_TITLE6 "opt_title6"
#define SETTING_OPT_TITLE7 "opt_title7"
#define SETTING_OPT_TITLE8 "opt_title8"
#define OPTIONAL1 "0953_x1"	// まいにちフランス語 入門編／初級編
#define OPTIONAL2 "0953_y1"	// まいにちフランス語 応用編
#define OPTIONAL3 "0943_x1"	// まいにちドイツ語 入門編／初級編
#define OPTIONAL4 "0943_y1"	// まいにちドイツ語 応用編
#define OPTIONAL5 "0946_x1"	// まいにちイタリア語 入門編／初級編
#define OPTIONAL6 "0946_y1"	// まいにちイタリア語 応用編
#define OPTIONAL7 "0948_x1"	// まいにちスペイン語 入門編／初級編
#define OPTIONAL8 "0948_y1"	// まいにちスペイン語 中級編／応用編
#define Program_TITLE1 "任意らじる聴き逃し番組１"
#define Program_TITLE2 "任意らじる聴き逃し番組２"
#define Program_TITLE3 "任意らじる聴き逃し番組３"
#define Program_TITLE4 "任意らじる聴き逃し番組４"
#define Program_TITLE5 "任意らじる聴き逃し番組５"
#define Program_TITLE6 "任意らじる聴き逃し番組６"
#define Program_TITLE7 "任意らじる聴き逃し番組７"
#define Program_TITLE8 "任意らじる聴き逃し番組８"

#ifdef QT4_QT5_WIN
#define STYLE_SHEET "stylesheet-win.qss"
#else
#ifdef QT4_QT5_MAC
#define STYLE_SHEET "stylesheet-mac.qss"
#else
#define STYLE_SHEET "stylesheet-ubu.qss"
#endif
#endif

namespace {
	bool outputDirSpecified = false;
	QString version() {
		QString result;
		// 日本語ロケールではQDate::fromStringで曜日なしは動作しないのでQRegExpを使う
		// __DATE__の形式： "Jul  8 2011"
#ifdef QT5
		static QRegExp regexp( "([a-zA-Z]{3})\\s+(\\d{1,2})\\s+(\\d{4})" );
		static QStringList months = QStringList()
				<< "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"
				<< "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
		if ( regexp.indexIn( __DATE__ ) != -1 ) {
//			int month = months.indexOf( regexp.cap( 1 ) ) + 1;
//			int day = regexp.cap( 2 ).toInt();
//			result = QString( " (%1/%2/%3)" ).arg( regexp.cap( 3 ) )
//					.arg( month, 2, 10, QLatin1Char( '0' ) ).arg( day, 2, 10, QLatin1Char( '0' ) );
			result = QString( "  (2024/06/04)" ); 
		}
#endif
#ifdef QT6
			result = QString( "  (2024/06/04)" ); 
#endif
		return result;
	}
}

QString MainWindow::outputDir;
QString MainWindow::ini_file_path;
QString MainWindow::scramble;
QString MainWindow::scrambleUrl1;
QString MainWindow::scrambleUrl2;
QString MainWindow::customized_title1;
QString MainWindow::customized_title2;
QString MainWindow::customized_file_name1;
QString MainWindow::customized_file_name2;
QString MainWindow::OPTIONAL[] = { "0953", "0943", "0946", "0948" };
QString MainWindow::optional[] = {"0953", "4412", "0943", "4410", "0946", "4411", "0948", "4413"};
QString MainWindow::optional1;
QString MainWindow::optional2;
QString MainWindow::optional3;
QString MainWindow::optional4;
QString MainWindow::optional5;
QString MainWindow::optional6;
QString MainWindow::optional7;
QString MainWindow::optional8;

QString MainWindow::SETTING_OPTIONAL[] = { "optional1", "optional2", "optional3", "optional4" };
QString MainWindow::SETTING_OPT_TITLE[] = { "opt_title1", "opt_title2", "opt_title3", "opt_title4", "opt_title5", "opt_title6", "opt_title7", "opt_title8" };
QString MainWindow::program_title1;
QString MainWindow::program_title2;
QString MainWindow::program_title3;
QString MainWindow::program_title4;
QString MainWindow::program_title5;
QString MainWindow::program_title6;
QString MainWindow::program_title7;
QString MainWindow::program_title8;
QString MainWindow::prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
QString MainWindow::suffix = "listdataflv.xml";
QString MainWindow::json_prefix = "https://www.nhk.or.jp/radioondemand/json/";
QString MainWindow::no_write_ini;
bool MainWindow::koza_separation_flag;
bool MainWindow::id_flag = false;

MainWindow::MainWindow( QWidget *parent )
		: QMainWindow( parent ), ui( new Ui::MainWindowClass ), downloadThread( NULL ) {
#ifdef QT4_QT5_MAC
	ini_file_path = Utility::ConfigLocationPath();
#endif
#if !defined( QT4_QT5_MAC )
	ini_file_path = Utility::applicationBundlePath();
#endif	
	ui->setupUi( this );
	settings( ReadMode );
	this->setWindowTitle( this->windowTitle() + version() );
	no_write_ini = "yes";
	
#ifdef QT4_QT5_MAC		// Macのウィンドウにはメニューが出ないので縦方向に縮める
//	setMaximumHeight( maximumHeight() - menuBar()->height() );
//	setMinimumHeight( maximumHeight() - menuBar()->height() );
	menuBar()->setNativeMenuBar(false);		// 他のOSと同様にメニューバーを表示　2023/04/04
	setMaximumHeight( maximumHeight() );		// ダウンロードボタンが表示されない問題対策　2022/04/16
	setMinimumHeight( maximumHeight() );		// ダウンロードボタンが表示されない問題対策　2022/04/16
//	QRect rect = geometry();
//	rect.setHeight( rect.height() - menuBar()->height() );
//	rect.setHeight( rect.height() );		// ダウンロードボタンが表示されない問題対策　2022/04/16
//	rect.moveTop( rect.top() + menuBar()->height() );	// 4.6.3だとこれがないとウィンドウタイトルがメニューバーに隠れる
//	setGeometry( rect );
#endif
#ifdef Q_OS_LINUX		// Linuxでは高さが足りなくなるので縦方向に伸ばしておく
	menuBar()->setNativeMenuBar(false);					// メニューバーが表示されなくなったに対応
	setMaximumHeight( maximumHeight() + X11_WINDOW_VERTICAL_INCREMENT );
	setMinimumHeight( maximumHeight() + X11_WINDOW_VERTICAL_INCREMENT );
	QRect rect = geometry();
	rect.setHeight( rect.height() + X11_WINDOW_VERTICAL_INCREMENT );
	setGeometry( rect );
#endif

#if !defined( QT4_QT5_MAC ) && !defined( QT4_QT5_WIN )
	QPoint bottomLeft = geometry().bottomLeft();
	bottomLeft += QPoint( 0, menuBar()->height() + statusBar()->height() + 3 );
	messagewindow.move( bottomLeft );
#endif

	// 「カスタマイズ」メニューの構築
	customizeMenu = menuBar()->addMenu( QString::fromUtf8( "カスタマイズ" ) );

	QAction* action = new QAction( QString::fromUtf8( "保存フォルダ設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeSaveFolder() ) );
	customizeMenu->addAction( action );
	action = new QAction( QString::fromUtf8( "保存フォルダ開く..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeFolderOpen() ) );
	customizeMenu->addAction( action );
	customizeMenu->addSeparator();
	action = new QAction( QString::fromUtf8( "ファイル名設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeFileName() ) );
	customizeMenu->addAction( action );

	action = new QAction( QString::fromUtf8( "タイトルタグ設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeTitle() ) );
	customizeMenu->addAction( action );
	customizeMenu->addSeparator();
	action = new QAction( QString::fromUtf8( "任意番組設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeScramble() ) );
	customizeMenu->addAction( action );

	customizeMenu->addSeparator();
	action = new QAction( QString::fromUtf8( "設定削除（終了）..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( closeEvent2() ) );
	customizeMenu->addAction( action );

	
	//action = new QAction( QString::fromUtf8( "スクランブル文字列..." ), this );
	//connect( action, SIGNAL( triggered() ), this, SLOT( customizeScramble() ) );
	//customizeMenu->addAction( action );

	QString styleSheet;
	QFile real( Utility::applicationBundlePath() + STYLE_SHEET );
	if ( real.exists() ) {
		real.open( QFile::ReadOnly );
		styleSheet = QLatin1String( real.readAll() );
	} else {
		QFile res( QString( ":/" ) + STYLE_SHEET );
		res.open( QFile::ReadOnly );
		styleSheet = QLatin1String( res.readAll() );
	}
#ifdef QT4_QT5_MAC    // MacのみoutputDirフォルダに置かれたSTYLE_SHEETを優先する
	QFile real2( MainWindow::outputDir + STYLE_SHEET );
	if ( real2.exists() ) {
		real2.open( QFile::ReadOnly );
		styleSheet = QLatin1String( real2.readAll() );
	} else {
		QFile real3( Utility::appConfigLocationPath() + STYLE_SHEET );
		if ( real3.exists() ) {
			real3.open( QFile::ReadOnly );
			styleSheet = QLatin1String( real3.readAll() );
		} else {
			QFile real4( Utility::ConfigLocationPath() + STYLE_SHEET );
			if ( real4.exists() ) {
				real4.open( QFile::ReadOnly );
				styleSheet = QLatin1String( real4.readAll() );
			}
		}
	} 
#endif	
	qApp->setStyleSheet( styleSheet );

//	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // DPI support
//	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); //HiDPI pixmaps
//	adjustSize();                             //高DPIディスプレイ対応
//	setFixedSize(size());
//	int dpiX = qApp->desktop()->logicalDpiX();
//	QFont f = qApp->font();
//	int defaultFontSize = f.pointSize() * ( 96.0 / dpiX );
//	f.setPointSize( defaultFontSize );
//	qApp->setFont(f);
}

MainWindow::~MainWindow() {
	if ( downloadThread ) {
		downloadThread->terminate();
		delete downloadThread;
	}
	if ( !Utility::nogui() && no_write_ini == "yes" )
		settings( WriteMode );
	delete ui;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
	Q_UNUSED( event )
	if ( downloadThread ) {
		messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセル中..." ) );
		download();
	}
	messagewindow.close();
	QCoreApplication::exit();
}

void MainWindow::settings( enum ReadWriteMode mode ) {
	typedef struct CheckBox {
		QAbstractButton* checkBox;
		QString key;
		QVariant defaultValue;
//		QString titleKey;
//		QVariant titleFormat;
//		QString fileNameKey;
//		QVariant fileNameFormat;
	} CheckBox;
#define DefaultTitle "%k_%Y_%M_%D"
//#define DefaultTitle1 "%f"
//#define DefaultTitle2 "%k_%Y_%M_%D"
#define DefaultFileName "%k_%Y_%M_%D.m4a"
//#define DefaultFileName1 "%k_%Y_%M_%D"
//#define DefaultFileName2 "%k_%Y_%M_%D"
//#define DefaultFileName3 "%h"
//#define DefaultFileName4 "%f"
	CheckBox checkBoxes[] = {
		{ ui->toolButton_basic0, "basic0", false },
		{ ui->toolButton_basic1, "basic1", false },
		{ ui->toolButton_basic2, "basic2", false },
		{ ui->toolButton_basic3, "basic3", false },
		{ ui->toolButton_timetrial, "timetrial", false },
		{ ui->toolButton_enjoy, "enjoy", false },
		{ ui->toolButton_kaiwa, "kaiwa", false },
		{ ui->toolButton_business1, "business1", false },
		{ ui->toolButton_gendai, "gendai", false },
		{ ui->toolButton_vrradio, "vrradio", false },
		{ ui->toolButton_optional1, "optional_1", false },
		{ ui->toolButton_optional2, "optional_2", false },
		{ ui->toolButton_optional3, "optional_3", false },
		{ ui->toolButton_optional4, "optional_4", false },
		{ ui->toolButton_optional5, "optional_5", false },
		{ ui->toolButton_optional6, "optional_6", false },
		{ ui->toolButton_optional7, "optional_7", false },
		{ ui->toolButton_optional8, "optional_8", false },
		{ ui->toolButton_skip, "skip", true },
		{ ui->checkBox_this_week, "this_week", true },
		{ ui->toolButton_detailed_message, "detailed_message", false },
		{ NULL, NULL, false }
	};

	typedef struct ComboBox {
		QComboBox* comboBox;
		QString key;
		QVariant defaultValue;
	} ComboBox;
	ComboBox comboBoxes[] = {
//		{ ui->comboBox_enews, "e-news-index", ENewsSaveBoth },
//		{ ui->comboBox_shower, "shower_index", ENewsSaveBoth },
		{ NULL, NULL, false }
	};
	ComboBox textComboBoxes[] = {
		{ ui->comboBox_extension, "audio_extension", "m4a" },	// 拡張子のデフォルトを「mp3」から「m4a」に変更。
		{ NULL, NULL, false }
	};
	
	typedef struct CheckBox2 {
		QAbstractButton* checkBox;
		QString titleKey;
		QVariant defaultValue;
		QString idKey;
		QVariant defaul;
		QString id;
	} CheckBox2;
	CheckBox2 checkBoxes2[] = {
		{ ui->toolButton_optional1, "opt_title1", Program_TITLE1, "optional1", OPTIONAL1, optional1 },
		{ ui->toolButton_optional2, "opt_title2", Program_TITLE2, "optional2", OPTIONAL2, optional2 },
		{ ui->toolButton_optional3, "opt_title3", Program_TITLE3, "optional3", OPTIONAL3, optional3 },
		{ ui->toolButton_optional4, "opt_title4", Program_TITLE4, "optional4", OPTIONAL4, optional4 },
		{ ui->toolButton_optional5, "opt_title5", Program_TITLE5, "optional5", OPTIONAL5, optional5 },
		{ ui->toolButton_optional6, "opt_title6", Program_TITLE6, "optional6", OPTIONAL6, optional6 },
		{ ui->toolButton_optional7, "opt_title7", Program_TITLE7, "optional7", OPTIONAL7, optional7 },
		{ ui->toolButton_optional8, "opt_title8", Program_TITLE8, "optional8", OPTIONAL8, optional8 },
		{ NULL, NULL, "", "NULL", "", "" }
	};
	

	QSettings settings( ini_file_path + INI_FILE, QSettings::IniFormat );
	
	settings.beginGroup( SETTING_GROUP );

	if ( mode == ReadMode ) {	// 設定読み込み
		QVariant saved;
		
//#if !defined( QT4_QT5_MAC )
//#if defined( QT4_QT5_MAC ) || defined( QT4_QT5_WIN )	// X11では正しく憶えられないので位置をリストアしない(2022/11/01:Linux向けに変更）
		saved = settings.value( SETTING_GEOMETRY );
#ifdef QT5
		if ( saved.type() == QVariant::Invalid )
#endif
#ifdef QT6
		if ( saved.toString() == "" )
#endif
			move( 70, 22 );
		else {
			// ウィンドウサイズはバージョン毎に変わる可能性があるのでウィンドウ位置だけリストアする
			QSize windowSize = size();
			restoreGeometry( saved.toByteArray() );
			resize( windowSize );
		}
//#endif                                              　//(2022/11/01:Linux向けに変更） 
//#endif
#if 0
//#ifdef QT4_QT5_MAC
		saved = settings.value( SETTING_MAINWINDOW_POSITION );
		if ( saved.type() == QVariant::Invalid )
			move( 70, 22 );
		else {
			QSize windowSize = size();
			move( saved.toPoint() );
			resize( windowSize );
		}
		saved = settings.value( SETTING_WINDOWSTATE );
		if ( !(saved.type() == QVariant::Invalid) )
			restoreState( saved.toByteArray() );
#endif

		saved = settings.value( SETTING_SAVE_FOLDER );
#if !defined( QT4_QT5_MAC )
#ifdef QT5
		outputDir = saved.type() == QVariant::Invalid ? Utility::applicationBundlePath() : saved.toString();
#endif
#ifdef QT6
		outputDir = saved.toString() == "" ? Utility::applicationBundlePath() : saved.toString();
#endif
#endif
#ifdef QT4_QT5_MAC
#ifdef QT5
		if ( saved.type() == QVariant::Invalid ) {
#endif
#ifdef QT6
		if ( saved.toString() == "" ) {
#endif
			outputDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
			MainWindow::customizeSaveFolder();
		} else
			outputDir = saved.toString();
#endif

		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
			checkBoxes[i].checkBox->setChecked( settings.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
			comboBoxes[i].comboBox->setCurrentIndex( settings.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ ) {
			QString extension = settings.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString();
			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
		}
		for ( int i = 0; checkBoxes2[i].checkBox != NULL; i++ ) {
			checkBoxes2[i].checkBox->setText( settings.value( checkBoxes2[i].titleKey, checkBoxes2[i].defaultValue ).toString() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			optional[i] = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString();
			switch ( i ) {
				case 0: optional1 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 1: optional2 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 2: optional3 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 3: optional4 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 4: optional5 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 5: optional6 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 6: optional7 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				case 7: optional8 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString(); break;
				default: break;
			}
		}

		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
			checkBoxes[i].checkBox->setChecked( settings.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
			comboBoxes[i].comboBox->setCurrentIndex( settings.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ ) {
			QString extension = settings.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString();
			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
		}

		saved = settings.value( SETTING_KOZA_SEPARATION );
		koza_separation_flag = saved.toString() == "" ? KOZA_SEPARATION_FLAG : saved.toBool();		
	} else {	// 設定書き出し
#if !defined( QT4_QT5_MAC )
		settings.setValue( SETTING_GEOMETRY, saveGeometry() );
#endif
#ifdef QT4_QT5_MAC
		settings.setValue( SETTING_WINDOWSTATE, saveState());
		settings.setValue( SETTING_MAINWINDOW_POSITION, pos() );
#endif
		if ( outputDirSpecified )
			settings.setValue( SETTING_SAVE_FOLDER, outputDir );

		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
			settings.setValue( checkBoxes[i].key, checkBoxes[i].checkBox->isChecked() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
			settings.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ )
			settings.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText() );
			
		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
			settings.setValue( checkBoxes[i].key, checkBoxes[i].checkBox->isChecked() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
			settings.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ )
			settings.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText() );
		for ( int i = 0; checkBoxes2[i].checkBox != NULL; i++ ) {
			settings.setValue( checkBoxes2[i].titleKey, checkBoxes2[i].checkBox->text() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			settings.setValue( checkBoxes2[i].idKey, checkBoxes2[i].id );
		}
		settings.setValue( SETTING_KOZA_SEPARATION, koza_separation_flag );
	}

	settings.endGroup();
}

void MainWindow::customizeTitle() {
	CustomizeDialog dialog( Ui::TitleMode );
	dialog.exec();
}

void MainWindow::customizeFileName() {
	CustomizeDialog dialog( Ui::FileNameMode );
	dialog.exec();
}

void MainWindow::customizeSaveFolder() {
	QString dir = QFileDialog::getExistingDirectory( 0, QString::fromUtf8( "書き込み可能な保存フォルダを指定してください" ),
									   outputDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
	if ( dir.length() ) {
		outputDir = dir + QDir::separator();
		outputDirSpecified = true;
	}
}

void MainWindow::customizeFolderOpen() {
	QDesktopServices::openUrl(QUrl("file:///" + outputDir, QUrl::TolerantMode));
}

void MainWindow::customizeScramble() {
	MainWindow::id_flag = false;
	QString optional_temp[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8, "NULL" };
	ScrambleDialog dialog( optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 );
    if (dialog.exec() ) {
    	QString pattern( "[0-9]{4}" );
    	pattern = QRegularExpression::anchoredPattern(pattern);
	for ( int i = 0; optional_temp[i] != "NULL"; i++ ) 
	    	if ( QRegularExpression(pattern).match( optional_temp[i] ).hasMatch() ) optional_temp[i] += "_01";

	QString optional[] = { dialog.scramble1(), dialog.scramble2(), dialog.scramble3(), dialog.scramble4(), dialog.scramble5(), dialog.scramble6(), dialog.scramble7(), dialog.scramble8(), "NULL" };	
	QString title[8];
	QStringList idList;
	QStringList titleList;
	std::tie( idList, titleList ) = Utility::getProgram_List();
	for ( int i = 0; optional[i] != "NULL"; i++ ) {
		if ( idList.contains( optional[i] ) ) title[i] = titleList[idList.indexOf( optional[i] )]; 
//		for ( int k = 0; k < idList.count() ; k++ ) { if ( optional[i] == idList[k] ) {title[i] = titleList[k]; break;} }
		if ( title[i]  == "" ) { title[i] = Utility::getProgram_name( optional[i] ); }
		if ( title[i]  == "" ) { optional[i] = optional_temp[i]; title[i] = Utility::getProgram_name( optional[i] ); }
	}
	optional1 = optional[0]; optional2 = optional[1];
	optional3 = optional[2]; optional4 = optional[3];
	optional5 = optional[4]; optional6 = optional[5];
	optional7 = optional[6]; optional8 = optional[7];
	program_title1 = title[0]; program_title2 = title[1];
	program_title3 = title[2]; program_title4 = title[3];
	program_title5 = title[4]; program_title6 = title[5];
	program_title7 = title[6]; program_title8 = title[7];

	QString program_title[] = { program_title1, program_title2, program_title3, program_title4, program_title5, program_title6, program_title7, program_title8, "NULL" };
	QAbstractButton* checkboxx[] = { ui->toolButton_optional1, ui->toolButton_optional2,
					 ui->toolButton_optional3, ui->toolButton_optional4,
					 ui->toolButton_optional5, ui->toolButton_optional6,
					 ui->toolButton_optional7, ui->toolButton_optional8,
					 NULL
		 	};
	bool flag = false;
	for ( int i = 0; program_title[i] != "NULL"; i++ ) {
		if ( optional[i] == optional_temp[i] && checkboxx[i]->isChecked() ) flag = true; else flag = false;
				checkboxx[i]->setChecked(false);
				checkboxx[i]->setText( QString( program_title[i] ) );
				if ( flag ) checkboxx[i]->setChecked( true );
	}
	optional1 = optional[0]; optional2 = optional[1]; optional3 = optional[2]; optional4 = optional[3];
	optional5 = optional[4]; optional6 = optional[5]; optional7 = optional[6]; optional8 = optional[7];
	ScrambleDialog dialog( optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 );
    }
}

void MainWindow::download() {	//「レコーディング」または「キャンセル」ボタンが押されると呼び出される
	if ( !downloadThread ) {	//レコーディング実行
		if ( messagewindow.text().length() > 0 )
			messagewindow.appendParagraph( "\n----------------------------------------" );
		ui->downloadButton->setEnabled( false );
		downloadThread = new DownloadThread( ui );
		connect( downloadThread, SIGNAL( finished() ), this, SLOT( finished() ) );
		connect( downloadThread, SIGNAL( critical( QString ) ), &messagewindow, SLOT( appendParagraph( QString ) ), Qt::BlockingQueuedConnection );
		connect( downloadThread, SIGNAL( information( QString ) ), &messagewindow, SLOT( appendParagraph( QString ) ), Qt::BlockingQueuedConnection );
		connect( downloadThread, SIGNAL( current( QString ) ), &messagewindow, SLOT( appendParagraph( QString ) ) );
		connect( downloadThread, SIGNAL( messageWithoutBreak( QString ) ), &messagewindow, SLOT( append( QString ) ) );
		downloadThread->start();
		ui->downloadButton->setText( QString::fromUtf8( "キャンセル" ) );
		ui->downloadButton->setEnabled( true );
	} else {	//キャンセル
		downloadThread->disconnect();	//wait中にSIGNALが発生するとデッドロックするためすべてdisconnect
		finished();
	}
}

void MainWindow::toggled( bool checked ) {
	QObject* sender = this->sender();
	if ( sender ) {
		QToolButton* button = (QToolButton*)sender;
		QString text = button->text();
		if ( checked )
			text.insert( 0, QString::fromUtf8( "✓ " ) );
		else
			text.remove( 0, 2 );
		button->setText( text );
	}
}

void MainWindow::finished() {
	if ( downloadThread ) {
		ui->downloadButton->setEnabled( false );
		MainWindow::id_flag = false;
		if ( downloadThread->isRunning() ) {	//キャンセルでMainWindow::downloadから呼ばれた場合
			downloadThread->cancel();
			downloadThread->wait();
			messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセルしました。" ) );
		}
		delete downloadThread;
		downloadThread = NULL;
		ui->downloadButton->setText( QString::fromUtf8( "レコーディング" ) );
		ui->downloadButton->setEnabled( true );
	}
	//ui->label->setText( "" );
	if ( Utility::nogui() )
		QCoreApplication::exit();
}

void MainWindow::closeEvent2( ) {
	int res = QMessageBox::question(this, tr("設定削除"), tr("削除しますか？"));
	if (res == QMessageBox::Yes) {
	no_write_ini = "no";
	
	QFile::remove( ini_file_path + INI_FILE );
	
	if ( downloadThread ) {
		messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセル中..." ) );
		download();
	}
	messagewindow.close();
	QCoreApplication::exit();
	}
}

