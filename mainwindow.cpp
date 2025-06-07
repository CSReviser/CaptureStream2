/*
	Copyright (C) 2009-2014 jakago
	Copyright (C) 2018-2025 CSReviser Team

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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloadthread.h"
#include "customizedialog.h"
#include "scrambledialog.h"
#include "settingsdialog.h"
#include "utility.h"
#include "qt4qt5.h"

#include <QRegularExpression>
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
#include <QMap>
#include <QSysInfo>
#include <QVector>
#include <QSet>
#include <QString>
#include <QProcessEnvironment>


#define VERSION "2025/05/31"
#define SETTING_GROUP "MainWindow"
#define SETTING_GEOMETRY "geometry"
#define SETTING_WINDOWSTATE "windowState"
#define SETTING_MAINWINDOW_POSITION "Mainwindow_Position"
#define SETTING_SAVE_FOLDER "save_folder"
#define SETTING_FFMPEG_FOLDER "ffmpeg_folder"
#define SETTING_SCRAMBLE "scramble"
#define SETTING_SCRAMBLE_URL1 "scramble_url1"
#define SETTING_KOZA_SEPARATION "koza_separation"
#define SETTING_MULTI_GUI "multi_gui"
#define SETTING_NAME_SPACE "name_space"
#define SETTING_TAG_SPACE "tag_space"
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
#define KOZA_SEPARATION_FLAG true
#define NAME_SPACE_FLAG true
#define TAG_SPACE_FLAG false
#define MULTI_GUI_FLAG false

#define SETTING_OPTIONAL1 "optional1"
#define SETTING_OPTIONAL2 "optional2"
#define SETTING_OPTIONAL3 "optional3"
#define SETTING_OPTIONAL4 "optional4"
#define SETTING_OPTIONAL5 "optional5"
#define SETTING_OPTIONAL6 "optional6"
#define SETTING_OPTIONAL7 "optional7"
#define SETTING_OPTIONAL8 "optional8"
#define SETTING_OPTIONAL9 "optional9"
#define SETTING_OPTIONALa "optionala"
#define SETTING_SPECIAL1 "special1"
#define SETTING_SPECIAL2 "special2"
#define SETTING_SPECIAL3 "special3"
#define SETTING_SPECIAL4 "special4"
#define SETTING_OPT_TITLE1 "opt_title1"
#define SETTING_OPT_TITLE2 "opt_title2"
#define SETTING_OPT_TITLE3 "opt_title3"
#define SETTING_OPT_TITLE4 "opt_title4"
#define SETTING_OPT_TITLE5 "opt_title5"
#define SETTING_OPT_TITLE6 "opt_title6"
#define SETTING_OPT_TITLE7 "opt_title7"
#define SETTING_OPT_TITLE8 "opt_title8"
#define SETTING_OPT_TITLE9 "opt_title9"
#define SETTING_OPT_TITLEa "opt_titlea"
#define SETTING_SPEC_TITLE1 "spec_title1"
#define SETTING_SPEC_TITLE2 "spec_title2"
#define SETTING_SPEC_TITLE3 "spec_title3"
#define SETTING_SPEC_TITLE4 "spec_title4"
#define OPTIONAL1 "XQ487ZM61K_01"	 //まいにちフランス語
#define OPTIONAL2 "N8PZRZ9WQY_01"	 //まいにちドイツ語
#define OPTIONAL3 "LJWZP7XVMX_01"	 //まいにちイタリア語
#define OPTIONAL4 "NRZWXVGQ19_01"	 //まいにちスペイン語
#define OPTIONAL5 "YRLK72JZ7Q_01"	 //まいにちロシア語
#define OPTIONAL6 "N13V9K157Y_01"	 //ポルトガル語
#define OPTIONAL7 "983PKQPYN7_01"	 //まいにち中国語
#define OPTIONAL8 "LR47WW9K14_01"	 //まいにちハングル講座
#define OPTIONAL9 "XQ487ZM61K_01"	 //まいにちフランス語
#define OPTIONALa "N8PZRZ9WQY_01"	 //まいにちドイツ語
#define SPECIAL1 "6LPPKP6W8Q_01"	 //やさしい日本語
#define SPECIAL2 "WKMNWGMN6R_01"	 //アラビア語講座
#define SPECIAL3 "GLZQ4M519X_01"	 //Asian View
#define SPECIAL4 "4MY6Q8XP88_01"	 //Living in Japan
#define Program_TITLE1 "まいにちフランス語"
#define Program_TITLE2 "まいにちドイツ語"
#define Program_TITLE3 "まいにちイタリア語"
#define Program_TITLE4 "まいにちスペイン語"
#define Program_TITLE5 "まいにちロシア語"
#define Program_TITLE6 "ポルトガル語"
#define Program_TITLE7 "まいにち中国語"
#define Program_TITLE8 "まいにちハングル講座"
#define Program_TITLE9 "まいにちフランス語"
#define Program_TITLEa "まいにちドイツ語"
#define Special_TITLE1 "やさしい日本語"
#define Special_TITLE2 "アラビア語講座"
#define Special_TITLE3 "Asian View"
#define Special_TITLE4 "Living in Japan"

#ifdef Q_OS_WIN
#define STYLE_SHEET "stylesheet-win.qss"
#else
#ifdef Q_OS_MACOS
#define STYLE_SHEET "stylesheet-mac.qss"
#else
#define STYLE_SHEET "stylesheet-ubu.qss"
#endif
#endif

namespace {
	bool outputDirSpecified = false;
	bool ffmpegDirSpecified = false;
	QString version() {
		QString result;
		// 日本語ロケールではQDate::fromStringで曜日なしは動作しないのでQRegExpを使う
		// __DATE__の形式： "Jul  8 2011"

		static QRegularExpression regexp("([a-zA-Z]{3})\\s+(\\d{1,2})\\s+(\\d{4})");
		static QStringList months = QStringList()
			<< "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun"
			<< "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

		QRegularExpressionMatch match = regexp.match(__DATE__);
		if (match.hasMatch()) {
		    int month = months.indexOf(match.captured(1)) + 1;
		    int day = match.captured(2).toInt();
		    QString result = QString(" (%1/%2/%3)")
		            .arg(match.captured(3))
		            .arg(month, 2, 10, QLatin1Char('0'))
		            .arg(day, 2, 10, QLatin1Char('0'));
		    result = QString::fromUtf8("  (") + QString::fromUtf8(VERSION) + QString::fromUtf8(")");
		    // resultを利用する処理
		}
			result = QString::fromUtf8( "  (" ) + VERSION + QString::fromUtf8( ")" );
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
QString MainWindow::optional[] = {"0953", "4412", "0943", "4410", "0946", "4411", "0948", "4413", "0948", "4413"};
QString MainWindow::special[] = {"0953", "4412", "0943", "4410", "0946", "4411", "0948", "4413", "0948", "4413"};
QString MainWindow::optional1;
QString MainWindow::optional2;
QString MainWindow::optional3;
QString MainWindow::optional4;
QString MainWindow::optional5;
QString MainWindow::optional6;
QString MainWindow::optional7;
QString MainWindow::optional8;
QString MainWindow::optional9;
QString MainWindow::optionala;
QString MainWindow::special1;
QString MainWindow::special2;
QString MainWindow::special3;
QString MainWindow::special4;

QString MainWindow::SETTING_OPTIONAL[] = { "optional1", "optional2", "optional3", "optional4" };
QString MainWindow::SETTING_OPT_TITLE[] = { "opt_title1", "opt_title2", "opt_title3", "opt_title4", "opt_title5", "opt_title6", "opt_title7", "opt_title8", "opt_title7", "opt_title8"};
QString MainWindow::program_title1;
QString MainWindow::program_title2;
QString MainWindow::program_title3;
QString MainWindow::program_title4;
QString MainWindow::program_title5;
QString MainWindow::program_title6;
QString MainWindow::program_title7;
QString MainWindow::program_title8;
QString MainWindow::program_title9;
QString MainWindow::program_titlea;
QString MainWindow::special_title1;
QString MainWindow::special_title2;
QString MainWindow::special_title3;
QString MainWindow::special_title4;
QString MainWindow::prefix = "http://cgi2.nhk.or.jp/gogaku/st/xml/";
QString MainWindow::suffix = "listdataflv.xml";
QString MainWindow::json_prefix = "https://www.nhk.or.jp/radioondemand/json/";
QString MainWindow::no_write_ini;
QString MainWindow::ffmpeg_folder;
bool MainWindow::koza_separation_flag;
bool MainWindow::id_flag = false;
bool MainWindow::name_space_flag;
bool MainWindow::tag_space_flag;
int MainWindow::id_List_flag;
bool MainWindow::ffmpegDirSpecified;
bool MainWindow::multi_gui_flag;
QStringList MainWindow::idList;
QStringList MainWindow::titleList;
QMap<QString, QString> MainWindow::name_map;
QMap<QString, QString> MainWindow::id_map;
QMap<QString, QString> MainWindow::thumbnail_map;
		
MainWindow::MainWindow( QWidget *parent )
		: QMainWindow( parent ), ui( new Ui::MainWindowClass ), downloadThread( NULL ) {
#ifdef Q_OS_MACOS
	ini_file_path = Utility::ConfigLocationPath();
#endif
#if !defined( Q_OS_MACOS )
	ini_file_path = Utility::applicationBundlePath();
#endif	
	ui->setupUi( this );
	setmap();
	setAttribute(Qt::WA_InputMethodEnabled);
	settings( ReadMode );
	this->setWindowTitle( this->windowTitle() + version() );
	QString ver_tmp1 = QString::fromUtf8( VERSION) ;
	QString ver_tmp2 = ver_tmp1.remove("/");
	QString ver_tmp3 = Utility::getLatest_version();
	int current_version = ver_tmp2.toInt();
	int Latest_version = ver_tmp3.left(8).toInt();
	if ( Latest_version > current_version )
		this->setWindowTitle( this->windowTitle() + QString("  upgrade!" ) );
	no_write_ini = "yes";
	
#ifdef Q_OS_MACOS		// Macのウィンドウにはメニューが出ないので縦方向に縮める
///	setMaximumHeight( maximumHeight() - menuBar()->height() );
//	setMinimumHeight( maximumHeight() - menuBar()->height() );
	menuBar()->setNativeMenuBar(false);		// 他のOSと同様にメニューバーを表示　2023/04/04
	setMaximumHeight( maximumHeight() + ( menuBar()->height() - 24 ) * 2 );	// レコーディングボタンが表示されない問題対策　2024/06/06
	setMinimumHeight( maximumHeight() + ( menuBar()->height() - 24 ) * 2 );	// レコーディングボタンが表示されない問題対策　2024/06/06
//	setMaximumHeight( maximumHeight() );		// ダウンロードボタンが表示されない問題対策　2022/04/16
//	setMinimumHeight( maximumHeight() );		// ダウンロードボタンが表示されない問題対策　2022/04/16
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

#if !defined( Q_OS_MACOS ) && !defined( Q_OS_WIN )
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
	action = new QAction( QString::fromUtf8( "ffmpegパス設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( ffmpegFolder() ) );
	customizeMenu->addAction( action );
	customizeMenu->addSeparator();

	action = new QAction( QString::fromUtf8( "ファイル名設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeFileName() ) );
	customizeMenu->addAction( action );

	action = new QAction( QString::fromUtf8( "タイトルタグ設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeTitle() ) );
	customizeMenu->addAction( action );
	customizeMenu->addSeparator();

	action = new QAction( QString::fromUtf8( "番組一覧表示..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( programlist() ) );
	customizeMenu->addAction( action );

	customizeMenu->addSeparator();
	action = new QAction( QString::fromUtf8( "任意番組設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeScramble() ) );
	customizeMenu->addAction( action );
	
	action = new QAction( QString::fromUtf8( "その他設定..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( customizeSettings() ) );
	customizeMenu->addAction( action );

	customizeMenu->addSeparator();
	action = new QAction( QString::fromUtf8( "ホームページ表示..." ), this );
	connect( action, SIGNAL( triggered() ), this, SLOT( homepageOpen() ) );
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
#ifdef Q_OS_MACOS    // MacのみoutputDirフォルダに置かれたSTYLE_SHEETを優先する
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

//	setmap();
	if(multi_gui_flag) Utility::remove_LockFile();
//	if ( !multi_gui_flag ) Utility::unLockFile();
//	Utility::remove_LockFile();
//	Utility::tryLockFile();
//	Utility::unLockFile();
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
	bool nogui_flag = Utility::nogui();
	if ( !nogui_flag && no_write_ini == "yes" )
		settings( WriteMode );
	delete ui;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
	Q_UNUSED( event )
	if ( downloadThread ) {
		messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセル中..." ) );
		download();
	}
	Utility::unLockFile();
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
//		{ ui->toolButton_basic3, "basic3", false },
		{ ui->toolButton_timetrial, "timetrial", false },
		{ ui->toolButton_enjoy, "enjoy", false },
		{ ui->toolButton_kaiwa, "kaiwa", false },
		{ ui->toolButton_business1, "business1", false },
		{ ui->toolButton_gendai, "gendai", false },
//		{ ui->toolButton_vrradio, "vrradio", false },
		{ ui->toolButton_optional1, "optional_1", false },
		{ ui->toolButton_optional2, "optional_2", false },
		{ ui->toolButton_optional3, "optional_3", false },
		{ ui->toolButton_optional4, "optional_4", false },
		{ ui->toolButton_optional5, "optional_5", false },
		{ ui->toolButton_optional6, "optional_6", false },
		{ ui->toolButton_optional7, "optional_7", false },
		{ ui->toolButton_optional8, "optional_8", false },
		{ ui->toolButton_special1, "special_1", false },
		{ ui->toolButton_special2, "special_2", false },
		{ ui->toolButton_special3, "special_3", false },
		{ ui->toolButton_special4, "special_4", false },
		{ ui->toolButton_skip, "skip", true },
		{ ui->checkBox_this_week, "this_week", true },
		{ ui->toolButton_detailed_message, "detailed_message", false },
		{ ui->checkBox_thumbnail, "thumbnail", false },
		{ nullptr, "", false }
	};

	typedef struct ComboBox {
		QComboBox* comboBox;
		QString key;
		QVariant defaultValue;
	} ComboBox;
	ComboBox comboBoxes[] = {
//		{ ui->comboBox_enews, "e-news-index", ENewsSaveBoth },
//		{ ui->comboBox_shower, "shower_index", ENewsSaveBoth },
		{ nullptr, NULL, false }
	};
	ComboBox textComboBoxes[] = {
		{ ui->comboBox_extension, "audio_extension", "m4a" },	// 拡張子のデフォルトを「mp3」から「m4a」に変更。
		{ nullptr, NULL, false }
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
		{ nullptr, NULL, "", "NULL", "", "" }
	};
	CheckBox2 checkBoxes3[] = {
		{ ui->toolButton_special1, "spec_title1", Special_TITLE1, "special1", SPECIAL1, special1 },
		{ ui->toolButton_special2, "spec_title2", Special_TITLE2, "special2", SPECIAL2, special2 },
		{ ui->toolButton_special3, "spec_title3", Special_TITLE3, "special3", SPECIAL3, special3 },
		{ ui->toolButton_special4, "spec_title4", Special_TITLE4, "special4", SPECIAL4, special4 },
		{ nullptr, NULL, "", "NULL", "", "" }
	};
	
	QSettings settings( ini_file_path + INI_FILE, QSettings::IniFormat );
	
	settings.beginGroup( SETTING_GROUP );
	QSet<QString> validKeys;
	for ( int i = 0; checkBoxes[i].checkBox != nullptr; ++i ) {
        	validKeys.insert(checkBoxes[i].key);
	}
	for ( int i = 0; comboBoxes[i].comboBox != nullptr; ++i ) {
        	validKeys.insert(comboBoxes[i].key);
	}
	for ( int i = 0; textComboBoxes[i].comboBox != nullptr; ++i ) {
        	validKeys.insert(textComboBoxes[i].key);
	}
	for ( int i = 0; checkBoxes2[i].checkBox != nullptr; ++i ) {
        	validKeys.insert(checkBoxes2[i].titleKey);
        	validKeys.insert(checkBoxes2[i].idKey);
	}
	for ( int i = 0; checkBoxes3[i].checkBox != nullptr; ++i ) {
        	validKeys.insert(checkBoxes3[i].titleKey);
        	validKeys.insert(checkBoxes3[i].idKey);
	}
        validKeys.insert(SETTING_GEOMETRY);
        validKeys.insert(SETTING_SAVE_FOLDER);
	validKeys.insert(SETTING_FFMPEG_FOLDER);
        validKeys.insert(SETTING_KOZA_SEPARATION); 
        validKeys.insert(SETTING_NAME_SPACE);
        validKeys.insert(SETTING_TAG_SPACE);
	validKeys.insert(SETTING_MULTI_GUI);
	
	if ( mode == ReadMode ) {	// 設定読み込み
		QVariant saved;
		
//#if !defined( Q_OS_MACOS )
//#if defined( Q_OS_MACOS ) || defined( Q_OS_WIN )	// X11では正しく憶えられないので位置をリストアしない(2022/11/01:Linux向けに変更）
		saved = settings.value( SETTING_GEOMETRY );
		if ( !saved.isValid() )
			move( 70, 22 );
		else {
			// ウィンドウサイズはバージョン毎に変わる可能性があるのでウィンドウ位置だけリストアする
			QSize windowSize = size();
			restoreGeometry( saved.toByteArray() );
			resize( windowSize );
		}
//#endif                                              　//(2022/11/01:Linux向けに変更） 
//#endif

		saved = settings.value( SETTING_SAVE_FOLDER );
#if !defined( Q_OS_MACOS )
		outputDir = !saved.isValid() ? Utility::applicationBundlePath() : saved.toString();
#endif

#ifdef Q_OS_MACOS
		if ( !saved.isValid() ) {
			outputDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
			MainWindow::customizeSaveFolder();
		} else
			outputDir = saved.toString();
#endif
		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
			checkBoxes[i].checkBox->setChecked( settings.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
		}
		saved = settings.value( SETTING_FFMPEG_FOLDER );
		ffmpeg_folder = !saved.isValid() ? outputDir : saved.toString();
		if ( !saved.isValid() || saved.toString() == "" ) 
			ffmpegDirSpecified = false;
		else
			ffmpegDirSpecified = true;
	
		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
			comboBoxes[i].comboBox->setCurrentIndex( settings.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ ) {
			QString extension = settings.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString();
			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
		}
		for ( int i = 0; checkBoxes2[i].checkBox != nullptr; i++ ) {
			checkBoxes2[i].checkBox->setText( settings.value( checkBoxes2[i].titleKey, checkBoxes2[i].defaultValue ).toString().toUtf8() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			optional[i] = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8();
			switch ( i ) {
				case 0: optional1 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 1: optional2 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 2: optional3 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 3: optional4 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 4: optional5 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 5: optional6 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 6: optional7 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 7: optional8 = settings.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				default: break;
			}
		}
		for ( int i = 0; checkBoxes3[i].checkBox != nullptr; i++ ) {
			checkBoxes3[i].checkBox->setText( settings.value( checkBoxes3[i].titleKey, checkBoxes3[i].defaultValue ).toString().toUtf8() );
			if ( checkBoxes3[i].idKey == "NULL" ) continue;
			special[i] = settings.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8();
			switch ( i ) {
				case 0: special1 = settings.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 1: special2 = settings.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 2: special3 = settings.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 3: special4 = settings.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				default: break;
			}
		}

		for ( int i = 0; checkBoxes[i].checkBox != nullptr; i++ ) {
			checkBoxes[i].checkBox->setChecked( settings.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			comboBoxes[i].comboBox->setCurrentIndex( settings.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ ) {
			QString extension = settings.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString().toUtf8();
			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
		}

		saved = settings.value( SETTING_KOZA_SEPARATION );
		koza_separation_flag = !saved.isValid() ? KOZA_SEPARATION_FLAG : saved.toBool();
		saved = settings.value( SETTING_NAME_SPACE );
		name_space_flag = !saved.isValid() ? NAME_SPACE_FLAG : saved.toBool();
		saved = settings.value( SETTING_TAG_SPACE );
		tag_space_flag = !saved.isValid() ? TAG_SPACE_FLAG : saved.toBool();
		saved = settings.value( SETTING_MULTI_GUI );
		multi_gui_flag = !saved.isValid() ? MULTI_GUI_FLAG : saved.toBool();
		if(multi_gui_flag) Utility::remove_LockFile();
		// セクション内のすべてのキーを取得
	        QStringList keys = settings.childKeys();

	        for (const QString &key : keys) {
 	           // 未定義のキーを削除
 	           if (!validKeys.contains(key)) {
 	               settings.remove(key);
 	           }
        	}
	} else {	// 設定書き出し
#if !defined( Q_OS_MACOS )
		settings.setValue( SETTING_GEOMETRY, saveGeometry() );
#endif
#ifdef Q_OS_MACOS
		settings.setValue( SETTING_WINDOWSTATE, saveState());
		settings.setValue( SETTING_MAINWINDOW_POSITION, pos() );
#endif
		if ( outputDirSpecified )
			settings.setValue( SETTING_SAVE_FOLDER, outputDir );
		if ( ffmpegDirSpecified )
			settings.setValue( SETTING_FFMPEG_FOLDER, ffmpeg_folder );
		else
//			settings.setValue( SETTING_FFMPEG_FOLDER, "" );
			settings.remove( SETTING_FFMPEG_FOLDER );

		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			settings.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ )
			settings.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText().toUtf8() );
			
		for ( int i = 0; checkBoxes[i].checkBox != nullptr; i++ ) {
			settings.setValue( checkBoxes[i].key, checkBoxes[i].checkBox->isChecked() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			settings.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ )
			settings.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText().toUtf8() );
		for ( int i = 0; checkBoxes2[i].checkBox != nullptr; i++ ) {
			settings.setValue( checkBoxes2[i].titleKey, checkBoxes2[i].checkBox->text().toUtf8() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			settings.setValue( checkBoxes2[i].idKey, checkBoxes2[i].id );
		}
		for ( int i = 0; checkBoxes3[i].checkBox != nullptr; i++ ) {
			settings.setValue( checkBoxes3[i].titleKey, checkBoxes3[i].checkBox->text().toUtf8() );
			if ( checkBoxes3[i].idKey == "NULL" ) continue;
			settings.setValue( checkBoxes3[i].idKey, checkBoxes3[i].id );
		}
		
		settings.setValue( SETTING_KOZA_SEPARATION, koza_separation_flag );
		settings.setValue( SETTING_NAME_SPACE, name_space_flag );
		settings.setValue( SETTING_TAG_SPACE, tag_space_flag );
		settings.setValue( SETTING_MULTI_GUI, multi_gui_flag );
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
    bool success = false;
#if defined(Q_OS_WIN)
	if (isWineEnvironment()) {
		QString dir = convertWinePathToUnix( outputDir );
		openUrlWithFallbackDialog(QUrl::fromLocalFile( dir ),this);
		success = true;
	} else {
		success = QDesktopServices::openUrl(QUrl("file:///" + outputDir, QUrl::TolerantMode));
	}
#elif defined(Q_OS_MAC)
	success = QDesktopServices::openUrl(QUrl("file:///" + outputDir, QUrl::TolerantMode));
#elif defined(Q_OS_LINUX)
	QString dir = safeWineToUnixPath( outputDir );
	QString cmd = QString("xdg-open \"%1\"").arg(dir);
	openUrlWithFallbackDialog(QUrl::fromLocalFile( dir ),this);
	success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
	if (!success) {
       		success = QDesktopServices::openUrl(outputDir);
	}
#else
	success = QDesktopServices::openUrl(QUrl("file:///" + outputDir, QUrl::TolerantMode));
	if (!success) {
       		success = QDesktopServices::openUrl(outputDir);
	}
#endif
	if (!success) {
       		success = QDesktopServices::openUrl(outputDir);
	}

    QString fallbackMessage;
    if (!success) {
        fallbackMessage = QObject::tr("フォルダを開くことができませんでした。\nパス: %1").arg(outputDir);
        QMessageBox::warning( nullptr, QObject::tr("エラー"), fallbackMessage);
    }       
}

void MainWindow::homepageOpen() {
	QString versionStr = QString::fromUtf8(VERSION).remove("/");
	QString latestVersionRaw = Utility::getLatest_version();
	QString latestVersionFormatted = latestVersionRaw.left(4) + "/" + latestVersionRaw.mid(4, 2) + "/" + latestVersionRaw.mid(6, 2);

	int currentVersion = versionStr.toInt();
	int latestVersion = latestVersionRaw.left(8).toInt();

	QString message;
	if (latestVersion > currentVersion) {
		message = QString::fromUtf8("最新版があります\n現在：") + VERSION +
		          QString::fromUtf8("\n最新：") + latestVersionFormatted +
		          QString::fromUtf8("\n表示しますか？");
	} else if (latestVersion < currentVersion) {
		message = QString::fromUtf8("最新版を確認して下さい\n現在：") + VERSION +
		          QString::fromUtf8("\n表示しますか？");
	} else {
		message = QString::fromUtf8("最新版です\n現在：") + VERSION +
		          QString::fromUtf8("\n表示しますか？");
	}

	int res = QMessageBox::question(this, tr("ホームページ表示"), message);
	if (res == QMessageBox::Yes) {
		openUrlWithFallbackDialog(QUrl("https://csreviser.github.io/CaptureStream2/", QUrl::TolerantMode),this);
//		QDesktopServices::openUrl(QUrl("https://csreviser.github.io/CaptureStream2/", QUrl::TolerantMode));
	}
}

void MainWindow::ffmpegFolder() {
	QMessageBox msgBox(this);
	QString message = QString::fromUtf8("ffmpegがあるフォルダを設定しますか？\n現在設定：\n") + ffmpeg_folder;
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setWindowTitle(tr("ffmpegがあるフォルダ設定"));
	msgBox.setText(message);

	QPushButton* setButton = msgBox.addButton(tr("設定する"), QMessageBox::ActionRole);
	QPushButton* searchButton = msgBox.addButton(tr("検索"), QMessageBox::ActionRole);
	QPushButton* bundledButton = msgBox.addButton(tr("同梱"), QMessageBox::ActionRole);
	QPushButton* resetButton = msgBox.addButton(tr("初期値に戻す"), QMessageBox::ActionRole);
	msgBox.setStandardButtons(QMessageBox::Cancel);

	if (msgBox.exec() == QMessageBox::Cancel) return;

	QPushButton* clicked = qobject_cast<QPushButton*>(msgBox.clickedButton());


QString folderPath;
if (isWineEnvironment()) {
    folderPath = getNativeUbuntuFolderViaZenity(this, tr("ffmpegがあるフォルダを指定してください"), QDir::homePath());
} else {
    folderPath = QFileDialog::getExistingDirectory(this, tr("ffmpegがあるフォルダを指定してください"),
                                                   QDir::homePath(),
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}

	if (clicked == setButton) {
		QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("ffmpegがあるフォルダを指定してください"),
														ffmpeg_folder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if (!dir.isEmpty()) {
			ffmpeg_folder = dir + QDir::separator();
			ffmpegDirSpecified = true;
		}
	} else if (clicked == resetButton) {
		ffmpeg_folder = Utility::applicationBundlePath();
		ffmpegDirSpecified = false;
	} else if (clicked == searchButton) {
		QString dir = findFfmpegPath();
		if (!dir.isEmpty()) {
			message = QString::fromUtf8("ffmpegがある下記フォルダを見つけました。\n設定しますか？\n変更後の設定：\n") + dir;
			if (QMessageBox::Yes == QMessageBox::question(this, tr("ffmpegがあるフォルダ設定"), message)) {
				ffmpeg_folder = dir + QDir::separator();
				ffmpegDirSpecified = true;
			}
		} else {
			if (QMessageBox::Yes == QMessageBox::question(this, tr("ffmpegがあるフォルダ設定"), tr("ffmpegを見つけられませんでした。\n初期値に戻します。"))) {
				ffmpeg_folder = Utility::applicationBundlePath();
				ffmpegDirSpecified = false;
			}
		}
	} else if (clicked == bundledButton) {
		QString dir = Utility::applicationBundlePath();
		message = QString::fromUtf8("語学講座CS2に同梱のffmpegを使用します。\n設定しますか？\n変更後の設定：\n") + dir;
		if (QMessageBox::Yes == QMessageBox::question(this, tr("同梱のffmpegフォルダ設定"), message)) {
			ffmpeg_folder = dir + QDir::separator();
			ffmpegDirSpecified = true;
		}
	}
}

QString MainWindow::findFfmpegPath() {
	QProcess process;
	QString ffmpegPath;

#ifdef Q_OS_WIN
	process.start("cmd.exe", QStringList() << "/c" << "where" << "ffmpeg");
#else
	process.start("which", QStringList() << "ffmpeg");
#endif
	process.waitForFinished();

	ffmpegPath = QString::fromUtf8(process.readAllStandardOutput()).split("\n").first().trimmed();

	if (!QFileInfo::exists(ffmpegPath)) {
#ifdef Q_OS_MAC
		QString arch = QSysInfo::buildCpuArchitecture();
		if (arch == "x86_64") {
			ffmpegPath = "/usr/local/bin/ffmpeg";
		} else if (arch == "arm64") {
			ffmpegPath = "/opt/homebrew/bin/ffmpeg";
			if (!QFile::exists(ffmpegPath)) {
				ffmpegPath = "/usr/local/bin/ffmpeg";
			}
		}
#elif defined(Q_OS_LINUX)
		ffmpegPath = "/usr/bin/ffmpeg";
#elif defined(Q_OS_WIN)
		ffmpegPath = "C:\\Program Files\\ffmpeg\\bin\\ffmpeg.exe";
		if (!QFile::exists(ffmpegPath)) {
			ffmpegPath = "C:\\ffmpeg\\bin\\ffmpeg.exe";
		}
#endif
	}

	if (QFile::exists(ffmpegPath)) {
		return QFileInfo(ffmpegPath).absolutePath();
	}
	return QString();
}

void MainWindow::programlist() {
	MainWindow::id_flag = true;

	QMessageBox msgbox(this);
	setmap();
	msgbox.setIcon(QMessageBox::Question);
	msgbox.setWindowTitle(tr("番組一覧表示"));
	msgbox.setText(tr("番組一覧を表示しますか？(レコーディング中は表示しません)\nEnglish\t\t：英語講座のみ\nOther Languages\t：語学講座のみ(英語講座除く)\nAll\t\t：らじる★らじる(聞き逃し)全番組"));
	QPushButton *anyButton = msgbox.addButton(tr("English"), QMessageBox::ActionRole);
	QPushButton *anyButton1 = msgbox.addButton(tr("Other Languages"), QMessageBox::ActionRole);
	QPushButton *anyButton2 = msgbox.addButton(tr("All"), QMessageBox::ActionRole);

//	msgbox.setStandardButtons(QMessageBox::Open | QMessageBox::YesToAll | QMessageBox::No);
	msgbox.setStandardButtons(QMessageBox::Cancel);
	msgbox.setDefaultButton(QMessageBox::Cancel);
	int button = msgbox.exec();	
	
	
    if ( button != QMessageBox::Cancel) {
	if ( msgbox.clickedButton() == anyButton) id_List_flag = 1;
	if ( msgbox.clickedButton() == anyButton1) id_List_flag = 2;
	if ( msgbox.clickedButton() == anyButton2) id_List_flag = 3;
	
	if ( !downloadThread ) {	//レコーディング実行
//		if ( messagewindow.text().length() > 0 )
			messagewindow.appendParagraph( "\n----------------------------------------" );
		messagewindow.appendParagraph( "*****　　番組一覧　　*****" );
		messagewindow.appendParagraph( "----------------------------------------" );
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
	} 
   }
}

void MainWindow::customizeScramble() {
	MainWindow::id_flag = false;
	setmap();
	QString optional_temp[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8, "NULL" };
	ScrambleDialog dialog( optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 );
    if (dialog.exec() ) {
    	QString pattern( "_01" );
    	pattern = QRegularExpression::anchoredPattern(pattern);
//	for ( int i = 0; optional_temp[i] != "NULL"; i++ ) 
//		    	if ( QRegularExpression(pattern).match( optional_temp[i].right(3) ).hasMatch() ) optional_temp[i] += "_01";

	QString optional[] = { dialog.scramble1(), dialog.scramble2(), dialog.scramble3(), dialog.scramble4(), dialog.scramble5(), dialog.scramble6(), dialog.scramble7(), dialog.scramble8(), "NULL" };	
	QString title[8];
//	QStringList idList;
//	QStringList titleList;
//	std::tie( idList, titleList ) = Utility::getProgram_List();
	for ( int i = 0; optional[i] != "NULL"; i++ ) {
		if ( id_map.contains( optional[i] ) ) title[i] = id_map.value( optional[i] );
//		if ( idList.contains( optional[i] ) ) title[i] = titleList[idList.indexOf( optional[i] )]; 
//		for ( int k = 0; k < idList.count() ; k++ ) { if ( optional[i] == idList[k] ) {title[i] = titleList[k]; break;} }
		if ( title[i]  == "" ) { title[i] = Utility::getProgram_name( optional[i] ); }
		if ( title[i]  == "" || optional[i]  == "error" ) { optional[i] = optional_temp[i]; title[i] = Utility::getProgram_name( optional[i] ); }
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

void MainWindow::customizeSettings() {
	setmap();
	QSettings settings( ini_file_path + INI_FILE, QSettings::IniFormat );
	settings.beginGroup( SETTING_GROUP );
	QVariant saved;
	saved = settings.value( SETTING_MULTI_GUI );
	multi_gui_flag = saved.toString() == "" ? MULTI_GUI_FLAG : saved.toBool();	
	MainWindow::id_flag = false;
	QString special_temp[] = { special1, special2, special3, special4, "NULL" };
	Settingsdialog dialog( special1, special2, special3, special4 );
    if (dialog.exec() ) {
    	QString pattern( "_01" );
    	pattern = QRegularExpression::anchoredPattern(pattern);

	QString special[] = { dialog.scramble1(), dialog.scramble2(), dialog.scramble3(), dialog.scramble4(), "NULL" };	
	QString title[4];
	for ( int i = 0; special[i] != "NULL"; i++ ) {
		if ( id_map.contains( special[i] ) ) title[i] = id_map.value( special[i] );
		if ( title[i]  == "" ) { title[i] = Utility::getProgram_name( special[i] ); }
		if ( title[i]  == "" || special[i]  == "error" ) { special[i] = special_temp[i]; title[i] = Utility::getProgram_name( special[i] ); }
	}
	special1 = special[0]; special2 = special[1];
	special3 = special[2]; special4 = special[3];
	special_title1 = title[0]; special_title2 = title[1];
	special_title3 = title[2]; special_title4 = title[3];

	QString special_title[] = { special_title1, special_title2, special_title3, special_title4, "NULL" };
	QAbstractButton* checkboxx[] = { ui->toolButton_special1, ui->toolButton_special2,
					 ui->toolButton_special3, ui->toolButton_special4,
					 NULL
		 	};
	bool flag = false;
	for ( int i = 0; special_title[i] != "NULL"; i++ ) {
		if ( special[i] == special_temp[i] && checkboxx[i]->isChecked() ) flag = true; else flag = false;
				checkboxx[i]->setChecked(false);
				checkboxx[i]->setText( QString( special_title[i] ) );
				if ( flag ) checkboxx[i]->setChecked( true );
	}
	special1 = special[0]; special2 = special[1]; special3 = special[2]; special4 = special[3];
	Settingsdialog dialog( special1, special2, special3, special4 );
	if(multi_gui_flag) Utility::remove_LockFile(); else Utility::tryLockFile();
	settings.setValue( SETTING_MULTI_GUI, multi_gui_flag );
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
//	if ( Utility::nogui() )
	bool nogui_flag = Utility::nogui();
	if ( nogui_flag )
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
	Utility::unLockFile();
	messagewindow.close();
	QCoreApplication::exit();
	}
}

void MainWindow::setmap()
{
    QStringList kozaList = { "まいにちイタリア語", "まいにちスペイン語", "まいにちドイツ語", "まいにちフランス語", "まいにちロシア語" };

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    const QUrl url("https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/corners/new_arrivals");

    QNetworkRequest request(url);
    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        QByteArray response_data = reply->readAll();
        reply->deleteLater();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["corners"].toArray();

        for (const QJsonValue& value : jsonArray) {
            QJsonObject objxx = value.toObject();
            QString title = objxx["title"].toString();
            QString corner_name = objxx["corner_name"].toString();
            QString series_site_id = objxx["series_site_id"].toString();
            QString corner_site = objxx["corner_site_id"].toString();
            QString thumbnail_url = objxx["thumbnail_url"].toString();

            QString program_name = Utility::getProgram_name3(title, corner_name);
            QString url_id = series_site_id + "_" + corner_site;

            id_map.insert(url_id, program_name);
            name_map.insert(program_name, url_id);
            thumbnail_map.insert(url_id, thumbnail_url);
        }

        // 次の非同期処理へ
        fetchKozaSeries(kozaList);
    });
}

void MainWindow::fetchKozaSeries(const QStringList& kozaList)
{
    for (const QString& koza : kozaList) {
        if (!name_map.contains(koza)) continue;

        QString url = name_map[koza];
        int l = url.length() != 13 ? url.length() - 3 : 10;
        QString fullUrl = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
                          url.left(l) + "&corner_site_id=" + url.right(2);

	QUrl fulurl(fullUrl);
        QNetworkRequest request(fulurl);
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkReply* reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {
            QByteArray response_data = reply->readAll();
            reply->deleteLater();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray jsonArray = jsonObject["episodes"].toArray();

            for (const QJsonValue& value : jsonArray) {
                QJsonObject objxx = value.toObject();
                QString file_title = objxx["program_title"].toString();

                QString temp1, temp2;
                if (file_title.contains("入門編")) {
                    temp1 = koza + "【入門編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("初級編")) {
                    temp1 = koza + "【初級編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("応用編")) {
                    temp1 = koza + "【応用編】";
                    temp2 = url.left(l) + "_y1";
                }
                if (file_title.contains("中級編")) {
                    temp1 = koza + "【中級編】";
                    temp2 = url.left(l) + "_y1";
                }

                if (!temp1.isEmpty() && !temp2.isEmpty()) {
                    name_map.insert(temp1, temp2);
                    id_map.insert(temp2, temp1);
                }
            }
        });
    }
}

/// Wine環境かどうかを判定
bool MainWindow::isWineEnvironment() {
    if (qEnvironmentVariableIsSet("WINEPREFIX")) {
        return true;
    }
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\Software\\Wine", QSettings::NativeFormat);
    if (!reg.allKeys().isEmpty()) {
        return true;
    }
#endif
    return false;
}
/*
/// 汎用URL/ファイルパスオープン処理 + 失敗時の警告表示
void MainWindow::openUrlWithFallbackDialog(const QUrl &url, QWidget *parent = nullptr) {

    bool success = false;

#if defined(Q_OS_WIN)
    if (isWineEnvironment()) {
        // ホストLinux側のシェルを明示的に呼び出す
        QString cmd = QString("xdg-open \"%1\"").arg(url.toString());
        success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
    } else {
        success = QDesktopServices::openUrl(url);
    }
#elif defined(Q_OS_MAC)
    success = QProcess::startDetached("open", QStringList() << url.toString());
    if (!success) {
        success = QDesktopServices::openUrl(url);
    }
#elif defined(Q_OS_LINUX)
    QString cmd = QString("xdg-open \"%1\"").arg(url.toString());
    success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
    if (!success) {
        success = QDesktopServices::openUrl(url);
    }
#else
    success = QDesktopServices::openUrl(url);
#endif
    QString fallbackMessage;
    if (!success) {
            if (url.isLocalFile()) {
                fallbackMessage = QObject::tr("フォルダまたはファイルを開くことができませんでした。\nパス: %1").arg(url.toLocalFile());
            } else {
                fallbackMessage = QObject::tr("ブラウザでURLを開くことができませんでした。\nURL: %1").arg(url.toString());
            }
        QMessageBox::warning(parent, QObject::tr("エラー"), fallbackMessage);
    }       
}


bool isWineEnvironment() {
    if (qEnvironmentVariableIsSet("WINEPREFIX")) {
        return true;
    }
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\Software\\Wine", QSettings::NativeFormat);
    if (!reg.allKeys().isEmpty()) {
        return true;
    }
#endif
    return false;
}
*/
/// URLを開く。失敗したら警告ダイアログを表示する
void MainWindow::openUrlWithFallbackDialog(const QUrl &url, QWidget *parent = nullptr) {
    bool success = false;

#if defined(Q_OS_WIN)
    if (isWineEnvironment()) {
        // ホストLinux側のシェルを明示的に呼び出す
        QString cmd = QString("xdg-open \"%1\"").arg(url.toString());
        success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
    } else {
        success = QDesktopServices::openUrl(url);
    }
#elif defined(Q_OS_MAC)
    success = QProcess::startDetached("open", QStringList() << url.toString());
    if (!success) {
        success = QDesktopServices::openUrl(url);
    }
#elif defined(Q_OS_LINUX)
    QString cmd = QString("xdg-open \"%1\"").arg(url.toString());
    success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
    if (!success) {
        success = QDesktopServices::openUrl(url);
    }
#else
    success = QDesktopServices::openUrl(url);
#endif
    QString fallbackMessage;
    if (!success) {
            if (url.isLocalFile()) {
                fallbackMessage = QObject::tr("フォルダまたはファイルを開くことができませんでした。\nパス: %1").arg(url.toLocalFile());
            } else {
                fallbackMessage = QObject::tr("ブラウザでURLを開くことができませんでした。\nURL: %1").arg(url.toString());
            }
        QMessageBox::warning(parent, QObject::tr("エラー"), fallbackMessage);
    }       

 //   if (!success) {
 //       QMessageBox::warning(parent,
//                             QObject::tr("エラー"),
//                             QObject::tr("ホームページを既定のブラウザで開けませんでした。\nURL: %1").arg(url.toString()));
//    }
}

#include <QRegularExpression>

QString MainWindow::convertWinePathToUnix(const QString &winePath)
{
    // 判定：先頭が英字1文字 + ":/" で始まる（例: "Z:/", "D:/", ...）
    static QRegularExpression driveRegex("^[A-Z]:/", QRegularExpression::CaseInsensitiveOption);

    if (!driveRegex.match(winePath).hasMatch())
        return winePath;  // 通常の UNIX パスとみなしてそのまま返す

    QString localPath = winePath;

    // "X:/" → "/" に変換（例: "Z:/home/user" → "/home/user"）
    localPath.remove(0, 2);  // "X:" を削除
    if (!localPath.startsWith('/'))
        localPath.prepend('/');  // "home/user" → "/home/user"

    return localPath;
}

QString MainWindow::normalizePathForWine(const QString &originalPath) {
    if (originalPath.startsWith("Z:/", Qt::CaseInsensitive)) {
        QString path = originalPath.mid(2); // "Z:" を除去
        path.replace("\\", "/");            // バックスラッシュをスラッシュに
        return path;
    }
    return originalPath;
}

bool MainWindow::isWinePathAvailable()
{
    return !QStandardPaths::findExecutable("winepath").isEmpty();
}

QString MainWindow::wineToUnixPath(const QString &winePath)
{
    if (!isWinePathAvailable())
        return QFileInfo(winePath).absoluteFilePath();

    QProcess process;
    process.start("winepath", QStringList() << "-u" << winePath);
    if (!process.waitForFinished(1000))
        return winePath;

    QString result = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    return result.isEmpty() ? winePath : result;
}

QString MainWindow::unixToWinePath(const QString &unixPath)
{
    if (!isWinePathAvailable())
        return unixPath;

    QProcess process;
    process.start("winepath", QStringList() << "-w" << unixPath);
    if (!process.waitForFinished(1000))
        return unixPath;

    QString result = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    return result.isEmpty() ? unixPath : result;
}

QString MainWindow::fallbackWineToUnixPath(const QString &winePath)
{
    static QRegularExpression driveRegex("^[A-Z]:/", QRegularExpression::CaseInsensitiveOption);
    if (!driveRegex.match(winePath).hasMatch())
        return winePath;

    QString localPath = QFileInfo(winePath).absoluteFilePath();
    localPath.remove(0, 2);
    if (!localPath.startsWith('/'))
        localPath.prepend('/');
    return localPath;
}

bool MainWindow::isRunningUnderWine()
{
#ifdef Q_OS_WIN
    QProcess process;
    process.start("cmd", QStringList() << "/C" << "ver");
    process.waitForFinished();
    QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
    return output.contains("Wine", Qt::CaseInsensitive);
#else
    return false;
#endif
}

QString MainWindow::safeWineToUnixPath(const QString &maybeWinePath)
{
    if (!isRunningUnderWine())
        return maybeWinePath;

    if (isWinePathAvailable())
        return wineToUnixPath(maybeWinePath);

    return fallbackWineToUnixPath(maybeWinePath);
}

QString MainWindow::getNativeUbuntuFolderViaZenity(QWidget *parent, const QString &message, const QString &initialDir)
{
    QStringList args;
    args << "-c"
         << QString("zenity --file-selection --directory --title='%1' --filename='%2/'")
                .arg(message, initialDir);

    QProcess process;
    process.start("/bin/sh", args);
    if (!process.waitForFinished())
        return QString();

    QString result = QString::fromUtf8(process.readAllStandardOutput()).trimmed();

    if (result.isEmpty()) {
        QMessageBox::warning(parent, QObject::tr("選択がキャンセルされました"),
                             QObject::tr("フォルダが選択されませんでした。"));
    }

    return result;
}
/*
void MainWindow::fetchKozaSeries(const QStringList& kozaList)
{
    int total = kozaList.count();
    int* completed = new int(0);  // 注意：後でdelete予定（またはQSharedPointer使用可）

    for (const QString& koza : kozaList) {
        if (!name_map.contains(koza)) {
            total--;
            continue;
        }

        QString url = name_map[koza];
        int l = (url.length() != 13) ? url.length() - 3 : 10;
        QString fullUrl = "https://www.nhk.or.jp/radio-api/app/v1/web/ondemand/series?site_id=" +
                          url.left(l) + "&corner_site_id=" + url.right(2);

        QNetworkRequest request(QUrl(fullUrl));
        QNetworkAccessManager* manager = new QNetworkAccessManager(this);
        QNetworkReply* reply = manager->get(request);

        connect(reply, &QNetworkReply::finished, this, [=]() {
            QByteArray response_data = reply->readAll();
            reply->deleteLater();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray jsonArray = jsonObject["episodes"].toArray();

            for (const QJsonValue& value : jsonArray) {
                QJsonObject objxx = value.toObject();
                QString file_title = objxx["program_title"].toString();

                QString temp1, temp2;
                if (file_title.contains("入門編")) {
                    temp1 = koza + "【入門編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("初級編")) {
                    temp1 = koza + "【初級編】";
                    temp2 = url.left(l) + "_x1";
                }
                if (file_title.contains("応用編")) {
                    temp1 = koza + "【応用編】";
                    temp2 = url.left(l) + "_y1";
                }
                if (file_title.contains("中級編")) {
                    temp1 = koza + "【中級編】";
                    temp2 = url.left(l) + "_y1";
                }

                if (!temp1.isEmpty() && !temp2.isEmpty()) {
                    name_map.insert(temp1, temp2);
                    id_map.insert(temp2, temp1);
                }
            }

            // カウンターインクリメント
            (*completed)++;
            if (*completed == total) {
                // 全件完了時の処理
                qDebug() << "All koza series fetched.";
                finalizeKozaData();

                delete completed; // メモリ解放
            }
        });
    }
}

void MainWindow::finalizeKozaData()
{
    QStringList kozaList1 = {
        "4MY6Q8XP88_01", "GLZQ4M519X_01", "6LPPKP6W8Q_01", "D6RM27PGVM_01",
        "X4X6N1XG8Z_01", "D85RZVGX7W_01", "LRK2VXPK5X_01", "M65G6QLKMY_01",
        "R5XR783QK3_01", "DK83KZ8848_01", "5L3859P515_01", "XKR4W8GY15_01",
        "4K58V66ZGQ_01", "X78J5NKWM9_01", "MVYJ6PRZMX_01", "JWQ88ZVWQK_01"
    };

    for (const QString& id : kozaList1) {
        if (!id_map.contains(id)) {
            id_map.insert(id, Utility::getProgram_name(id));
        }
    }

    name_map.insert("日本語講座", "6LPPKP6W8Q_s1");
    id_map.insert("6LPPKP6W8Q_s1", "日本語講座");

    qDebug() << "All mappings finalized.";
}
*/
