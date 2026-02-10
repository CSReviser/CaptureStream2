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

#include "mainwindow.h"
#include "constants.h"
#include "settings.h"
#include "runtimeconfig.h"
#include "ui_mainwindow.h"
#include "downloadthread.h"
#include "customizedialog.h"
#include "scrambledialog.h"
#include "settingsdialog.h"
#include "utility.h"
#include "qt4qt5.h"
#include "programrepository.h"

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
#include <QWidget>

#define X11_WINDOW_VERTICAL_INCREMENT 5
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
			result = QString::fromUtf8( "  (" ) + QString::fromUtf8(Constants::AppVersion) + QString::fromUtf8( ")" );
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
		
MainWindow::MainWindow( Settings& settings, RuntimeConfig* runtime, QWidget *parent )
		: QMainWindow( parent ), ui( new Ui::MainWindowClass ), downloadThread( NULL )
		, settings(settings), runtime(runtime) {
#ifdef Q_OS_MACOS
	ini_file_path = Utility::ConfigLocationPath();
#endif
#if !defined( Q_OS_MACOS )
	ini_file_path = Utility::applicationBundlePath();
#endif	
	ui->setupUi( this );
	settings.load();

	// ★ 番組一覧の初期化（非同期）
	auto &repo = ProgramRepository::instance();
	repo.updatePrograms();

	// ★ 番組一覧更新後に UI を更新したい場合
//	connect(&repo, &ProgramRepository::programListUpdated,
//	    this, &MainWindow::onProgramListUpdated);

	setmap();

	setAttribute(Qt::WA_InputMethodEnabled);
	settings1( ReadMode );

	this->setWindowTitle( Constants::AppName + version() );
	QString ver_tmp1 = Constants::AppVersion;
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
		settings1( WriteMode );
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

void MainWindow::settings1( enum ReadWriteMode mode ) {
	typedef struct CheckBox {
		QAbstractButton* checkBox;
		QString key;
		QVariant defaultValue;
//		QString titleKey;
//		QVariant titleFormat;
//		QString fileNameKey;
//		QVariant fileNameFormat;
	} CheckBox;
//#define DefaultTitle "%k_%Y_%M_%D"
//#define DefaultTitle1 "%f"
//#define DefaultTitle2 "%k_%Y_%M_%D"
//#define DefaultFileName "%k_%Y_%M_%D.m4a"
//#define DefaultFileName1 "%k_%Y_%M_%D"
//#define DefaultFileName2 "%k_%Y_%M_%D"
//#define DefaultFileName3 "%h"
//#define DefaultFileName4 "%f"
/*	CheckBox checkBoxes[] = {
		{ ui->toolButton_basic0, Constants::KEY_basic0, false },
		{ ui->toolButton_basic1, Constants::KEY_basic1, false },
		{ ui->toolButton_basic2, Constants::KEY_basic2, false },
//		{ ui->toolButton_basic3, "basic3", false },
		{ ui->toolButton_timetrial, Constants::KEY_timetrial, false },
		{ ui->toolButton_enjoy, Constants::KEY_enjoy, false },
		{ ui->toolButton_kaiwa, Constants::KEY_kaiwa, false },
		{ ui->toolButton_business1, Constants::KEY_business, false },
		{ ui->toolButton_gendai, Constants::KEY_gendai, false },
//		{ ui->toolButton_vrradio, "vrradio", false },
		{ ui->toolButton_optional1, Constants::OptionalPrograms[0].keyChecked, false },
		{ ui->toolButton_optional2, Constants::OptionalPrograms[1].keyChecked, false },
		{ ui->toolButton_optional3, Constants::OptionalPrograms[2].keyChecked, false },
		{ ui->toolButton_optional4, Constants::OptionalPrograms[3].keyChecked, false },
		{ ui->toolButton_optional5, Constants::OptionalPrograms[4].keyChecked, false },
		{ ui->toolButton_optional6, Constants::OptionalPrograms[5].keyChecked, false },
		{ ui->toolButton_optional7, Constants::OptionalPrograms[6].keyChecked, false },
		{ ui->toolButton_optional8, Constants::OptionalPrograms[7].keyChecked, false },
		{ ui->toolButton_special1, Constants::SpecPrograms[0].keyChecked, false },
		{ ui->toolButton_special2, Constants::SpecPrograms[1].keyChecked, false },
		{ ui->toolButton_special3, Constants::SpecPrograms[2].keyChecked, false },
		{ ui->toolButton_special4, Constants::SpecPrograms[3].keyChecked, false },
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
		{ ui->toolButton_optional1, "opt_title1", Constants::OptionalPrograms[0].titleDefault, "optional1", Constants::OptionalPrograms[0].idDefault, optional1 },
		{ ui->toolButton_optional2, "opt_title2", Constants::OptionalPrograms[1].titleDefault, "optional2", Constants::OptionalPrograms[1].idDefault, optional2 },
		{ ui->toolButton_optional3, "opt_title3", Constants::OptionalPrograms[2].titleDefault, "optional3", Constants::OptionalPrograms[2].idDefault, optional3 },
		{ ui->toolButton_optional4, "opt_title4", Constants::OptionalPrograms[3].titleDefault, "optional4", Constants::OptionalPrograms[3].idDefault, optional4 },
		{ ui->toolButton_optional5, "opt_title5", Constants::OptionalPrograms[4].titleDefault, "optional5", Constants::OptionalPrograms[4].idDefault, optional5 },
		{ ui->toolButton_optional6, "opt_title6", Constants::OptionalPrograms[5].titleDefault, "optional6", Constants::OptionalPrograms[5].idDefault, optional6 },
		{ ui->toolButton_optional7, "opt_title7", Constants::OptionalPrograms[6].titleDefault, "optional7", Constants::OptionalPrograms[6].idDefault, optional7 },
		{ ui->toolButton_optional8, "opt_title8", Constants::OptionalPrograms[7].titleDefault, "optional8", Constants::OptionalPrograms[7].idDefault, optional8 },
		{ nullptr, NULL, "", "NULL", "", "" }
	};
	CheckBox2 checkBoxes3[] = {
		{ ui->toolButton_special1, "spec_title1", Constants::SpecPrograms[0].titleDefault, "special1", Constants::SpecPrograms[0].idDefault, special1 },
		{ ui->toolButton_special2, "spec_title2", Constants::SpecPrograms[1].titleDefault, "special2", Constants::SpecPrograms[1].idDefault, special2 },
		{ ui->toolButton_special3, "spec_title3", Constants::SpecPrograms[2].titleDefault, "special3", Constants::SpecPrograms[2].idDefault, special3 },
		{ ui->toolButton_special4, "spec_title4", Constants::SpecPrograms[3].titleDefault, "special4", Constants::SpecPrograms[3].idDefault, special4 },
		{ nullptr, NULL, "", "NULL", "", "" }
	};
*/	
	QSettings settings1( ini_file_path + Constants::IniFileName, QSettings::IniFormat );
/*	
	settings1.beginGroup( Constants::SETTING_GROUP_MainWindow );
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
        validKeys.insert("geometry");
        validKeys.insert(Constants::KEY_SaveFolder);
	validKeys.insert(Constants::KEY_FfmpegFolder);
        validKeys.insert(Constants::KEY_KOZA_SEPARATION); 
        validKeys.insert(Constants::KEY_NAME_SPACE);
        validKeys.insert(Constants::KEY_TAG_SPACE);
	validKeys.insert(Constants::KEY_MULTI_GUI);
*/	
	if ( mode == ReadMode ) {	// 設定読み込み
		QVariant saved;
		
//#if !defined( Q_OS_MACOS )
//#if defined( Q_OS_MACOS ) || defined( Q_OS_WIN )	// X11では正しく憶えられないので位置をリストアしない(2022/11/01:Linux向けに変更）
//		saved = settings1.value( "geometry" );
//		saved = settings.mainWindowGeometry;
		QByteArray mainWindowGeometry = settings.mainWindowGeometry;
//		if ( !saved.isValid() || mainWindowGeometry.isEmpty() )
		if ( mainWindowGeometry.isEmpty() )
			move( 70, 22 );
		else {
			// ウィンドウサイズはバージョン毎に変わる可能性があるのでウィンドウ位置だけリストアする
			QSize windowSize = size();
//			restoreGeometry( saved.toByteArray() );
			restoreGeometry( mainWindowGeometry );	
			resize( windowSize );
		}
//#endif                                              　//(2022/11/01:Linux向けに変更） 
//#endif

//		saved = settings1.value( Constants::KEY_SaveFolder );
		saved = settings.saveFolder;
#if !defined( Q_OS_MACOS )
		outputDir = !saved.isValid() ? Utility::applicationBundlePath() : saved.toString();
		if ( settings.saveFolder.isNull() ) outputDir = Utility::applicationBundlePath();
#endif

#ifdef Q_OS_MACOS
		if ( !saved.isValid() || settings.saveFolder.isNull() ) {
			outputDir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
			MainWindow::customizeSaveFolder();
		} else
			outputDir = saved.toString();
#endif
//		for ( int i = 0; checkBoxes[i].checkBox != NULL; i++ ) {
//			checkBoxes[i].checkBox->setChecked( settings1.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
//		}
//		saved = settings1.value( Constants::KEY_SaveFolder );
		saved = settings.ffmpegFolder;		
		ffmpeg_folder = !saved.isValid() ? outputDir : saved.toString();
		if ( !saved.isValid() || saved.toString() == "" ) 
			ffmpegDirSpecified = false;
		else
			ffmpegDirSpecified = true;
	
#if defined( Q_OS_WIN )
		outputDir = unixToWinePath(outputDir);
		ffmpeg_folder = unixToWinePath(ffmpeg_folder);
#else
		outputDir = convertWinePathToUnixAuto(outputDir);
		ffmpeg_folder = convertWinePathToUnixAuto(ffmpeg_folder);
#endif	

//		for ( int i = 0; comboBoxes[i].comboBox != NULL; i++ )
//			comboBoxes[i].comboBox->setCurrentIndex( settings1.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
//		for ( int i = 0; textComboBoxes[i].comboBox != NULL; i++ ) {
//			QString extension = settings1.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString();
//			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
//		}
//		textComboBoxes[0].comboBox->setCurrentIndex( textComboBoxes[0].comboBox->findText( settings.audioExtension ) );
/*
		for ( int i = 0; checkBoxes2[i].checkBox != nullptr; i++ ) {
			checkBoxes2[i].checkBox->setText( settings1.value( checkBoxes2[i].titleKey, checkBoxes2[i].defaultValue ).toString().toUtf8() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			optional[i] = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8();
			switch ( i ) {
				case 0: optional1 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 1: optional2 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 2: optional3 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 3: optional4 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 4: optional5 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 5: optional6 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 6: optional7 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				case 7: optional8 = settings1.value( checkBoxes2[i].idKey, checkBoxes2[i].defaul ).toString().toUtf8(); break;
				default: break;
			}
		}
	
		for ( int i = 0; checkBoxes3[i].checkBox != nullptr; i++ ) {
			checkBoxes3[i].checkBox->setText( settings1.value( checkBoxes3[i].titleKey, checkBoxes3[i].defaultValue ).toString().toUtf8() );
			if ( checkBoxes3[i].idKey == "NULL" ) continue;
			special[i] = settings1.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8();
			switch ( i ) {
				case 0: special1 = settings1.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 1: special2 = settings1.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 2: special3 = settings1.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				case 3: special4 = settings1.value( checkBoxes3[i].idKey, checkBoxes3[i].defaul ).toString().toUtf8(); break;
				default: break;
			}
		}
*/		

/*
		for ( int i = 0; checkBoxes[i].checkBox != nullptr; i++ ) {
			checkBoxes[i].checkBox->setChecked( settings1.value( checkBoxes[i].key, checkBoxes[i].defaultValue ).toBool() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			comboBoxes[i].comboBox->setCurrentIndex( settings1.value( comboBoxes[i].key, comboBoxes[i].defaultValue ).toInt() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ ) {
			QString extension = settings1.value( textComboBoxes[i].key, textComboBoxes[i].defaultValue ).toString().toUtf8();
			textComboBoxes[i].comboBox->setCurrentIndex( textComboBoxes[i].comboBox->findText( extension ) );
		}

		saved = settings1.value( SETTING_KOZA_SEPARATION );
		koza_separation_flag = !saved.isValid() ? KOZA_SEPARATION_FLAG : saved.toBool();
		saved = settings1.value( Constants::KEY_NAME_SPACE );
		name_space_flag = !saved.isValid() ? NAME_SPACE_FLAG : saved.toBool();
		name_space_flag = settings.checkBoxChecked[Constants::KEY_NAME_SPACE];
		saved = settings1.value( SETTING_TAG_SPACE );
		tag_space_flag = !saved.isValid() ? TAG_SPACE_FLAG : saved.toBool();
		tag_space_flag = settings.checkBoxChecked[Constants::KEY_TAG_SPACE];
//		saved = settings1.value( Constants::KEY_MULTI_GUI );
//		multi_gui_flag = !saved.isValid() ? MULTI_GUI_FLAG : saved.toBool();
*/

restoreGui();
		// ===== 英語講座 （固定番組）=====
//		restoreEnglishProgramUI();
/*
		for (int i = 0; i < Constants::EnglishCount; i++) {
		    const auto &p = Constants::EnglishPrograms[i];

 		   // objectName からボタンを取得
		    QAbstractButton* btn =
		        this->findChild<QAbstractButton*>(p.objectName);

 		   if (!btn)
 		       continue; // UI に存在しない場合はスキップ

		    // Settings の値を反映
//		    btn->setText(p.title);
		    btn->setChecked(settings.englishChecked[p.key]);
		}
*/
		// ===== Optional（ユーザー編集可能）=====		
//		restoreOptionalProgramUI();
/*
		for (int i = 0; i < Constants::OptionalCount; i++) {
		    const auto &p = Constants::OptionalPrograms[i];

 		   // objectName からボタンを取得
		    QAbstractButton* btn =
		        this->findChild<QAbstractButton*>(qs(p.objectName));

 		   if (!btn)
 		       continue; // UI に存在しない場合はスキップ

		    // Settings の値を反映
		    btn->setText(settings.optionalTitle[p.keyTitle]);
		    optional[i] = settings.optionalId[p.keyId];
		    btn->setChecked(settings.optionalChecked[p.keyChecked]);
		}
*/
//		optional1 = optional[0]; optional2 = optional[1]; optional3 = optional[2]; optional4 = optional[3];
//		optional5 = optional[4]; optional6 = optional[5]; optional7 = optional[6]; optional8 = optional[7];	

		// ===== Spec（特番）=====
//		restoreSpecialProgramUI();
		
/*
		for (int i = 0; i < Constants::SpecialCount; i++) {
		    const auto &p = Constants::SpecPrograms[i];

 		   // objectName からボタンを取得
		    QAbstractButton* btn =
		        this->findChild<QAbstractButton*>(qs(p.objectName));

 		   if (!btn)
 		       continue; // UI に存在しない場合はスキップ

		    // Settings の値を反映
		    btn->setText(settings.specTitle[p.keyTitle]);
		    special[i] = settings.specId[p.keyId];
		    btn->setChecked(settings.specChecked[p.keyChecked]);
		}
*/
//		special1 = special[0]; special2 = special[1]; special3 = special[2]; special4 = special[3];
/*
		// ===== CheckBox =====
		for (int i = 0; i < Constants::CheckBoxCount; i++) {
		    const auto &c = Constants::CheckBoxSettings[i];
        
		    // objectName からCheckBoxを取得
		    QAbstractButton* btn =
		        this->findChild<QAbstractButton*>(qs(c.objectName));
            
		    if (!btn)
		    continue; // UI に存在しない場合はスキップ
		    // Settings の値を反映
		    btn->setChecked(settings.checkBoxChecked[c.keyChecked]);
		}

		koza_separation_flag = settings.checkBoxChecked[Constants::KEY_KOZA_SEPARATION];
		name_space_flag = settings.checkBoxChecked[Constants::KEY_NAME_SPACE];
		tag_space_flag = settings.checkBoxChecked[Constants::KEY_TAG_SPACE];
		multi_gui_flag = settings.checkBoxChecked[Constants::KEY_MULTI_GUI];
		if(multi_gui_flag) Utility::remove_LockFile();
		// セクション内のすべてのキーを取得
	        QStringList keys = settings1.childKeys();

	        for (const QString &key : keys) {
 	           // 未定義のキーを削除
 	           if (!validKeys.contains(key)) {
 	               settings1.remove(key);
 	           }
        	}
*/
	} else {	// 設定書き出し
//#if !defined( Q_OS_MACOS )
//		settings1.setValue( "geometry", saveGeometry() );
		settings.mainWindowGeometry = saveGeometry();
//#endif
//#ifdef Q_OS_MACOS
//		settings1.setValue( SETTING_WINDOWSTATE, saveState());
//		settings1.setValue( SETTING_MAINWINDOW_POSITION, pos() );
//#endif
		if ( outputDirSpecified )
			settings1.setValue( Constants::KEY_SaveFolder, outputDir );
		if ( ffmpegDirSpecified )
			settings1.setValue( Constants::KEY_SaveFolder, ffmpeg_folder );
		else
//			settings1.setValue( Constants::KEY_SaveFolder, "" );
			settings1.remove( Constants::KEY_SaveFolder );
/*
		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			settings1.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ )
			settings1.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText().toUtf8() );
			
		for ( int i = 0; checkBoxes[i].checkBox != nullptr; i++ ) {
			settings1.setValue( checkBoxes[i].key, checkBoxes[i].checkBox->isChecked() );
		}
		for ( int i = 0; comboBoxes[i].comboBox != nullptr; i++ )
			settings1.setValue( comboBoxes[i].key, comboBoxes[i].comboBox->currentIndex() );
		for ( int i = 0; textComboBoxes[i].comboBox != nullptr; i++ )
			settings1.setValue( textComboBoxes[i].key, textComboBoxes[i].comboBox->currentText().toUtf8() );
		for ( int i = 0; checkBoxes2[i].checkBox != nullptr; i++ ) {
			settings1.setValue( checkBoxes2[i].titleKey, checkBoxes2[i].checkBox->text().toUtf8() );
			if ( checkBoxes2[i].idKey == "NULL" ) continue;
			settings1.setValue( checkBoxes2[i].idKey, checkBoxes2[i].id );
		}
		for ( int i = 0; checkBoxes3[i].checkBox != nullptr; i++ ) {
			settings1.setValue( checkBoxes3[i].titleKey, checkBoxes3[i].checkBox->text().toUtf8() );
			if ( checkBoxes3[i].idKey == "NULL" ) continue;
			settings1.setValue( checkBoxes3[i].idKey, checkBoxes3[i].id );
		}
		
		settings1.setValue( SETTING_KOZA_SEPARATION, koza_separation_flag );
		settings1.setValue( Constants::KEY_NAME_SPACE, name_space_flag );
		settings1.setValue( SETTING_TAG_SPACE, tag_space_flag );
		settings1.setValue( Constants::KEY_MULTI_GUI, multi_gui_flag );
*/		

//		settings.audioExtension = textComboBoxes[0].comboBox->currentText().toUtf8();
//		MainWindow::saveAllSettings();
	}
saveGui();
	settings1.endGroup();
}

void MainWindow::restoreGui()
{
    auto &s = Settings::instance();

    // geometry 復元
    if (!s.mainWindowGeometry.isEmpty()) {
        restoreGeometry(s.mainWindowGeometry);
    }

    // ===== English =====
    updateProgramButtons(Constants::EnglishPrograms, s);
     // ===== Optional =====   
    updateProgramButtons(Constants::OptionalPrograms, s);
    // ===== Spec =====
    updateProgramButtons(Constants::SpecPrograms, s);
    // ===== Feature（チェックボックス）=====
    updateProgramButtons(Constants::FeatureSettings, s);

    // saveFolder が未設定なら設定ダイアログを開く
     if (s.saveFolder.isEmpty()) {
        customizeSaveFolder();
    }
    // ffmpeg が未設定なら設定ダイアログを開く
    if (s.ffmpegFolder.isEmpty()) {
        ffmpegFolderDialog();
    }
    
    // audio_extension
    if (auto combo = findChild<QComboBox*>("comboBox_extension")) {
        int index = combo->findText(s.audioExtension);
        if (index >= 0)
            combo->setCurrentIndex(index);
     }           
    ui->checkBox_thumbnail->setChecked(settings.checked["thumbnail"]);

}

template <typename Container>
void MainWindow::updateProgramButtons(const Container &programs, const Settings &s)
{
    for (const auto &p : programs) {
        if (auto btn = findChild<QToolButton*>(qs(p.objectName))) {

            QString label;
//          if (qs(p.keyLabel).isEmpty()) {         
            if (p.hasLabel) {
               label = s.labels[p.keyLabel];
            }

            updateButtonUI(btn, s.checked[p.keyChecked], label);
        }
    }
}

void MainWindow::updateButtonUI(QToolButton* btn, bool checked, const QString& label)
{
    btn->blockSignals(true);
    btn->setChecked(checked);
    btn->blockSignals(false);

    if (label.isEmpty())
        return;

    static const QString mark = QString::fromUtf8("✓ ");	// 状態に応じて「✓」付与

    btn->setText(checked ? mark + label : label);
}

void MainWindow::saveGui()
{
    auto &s = Settings::instance();

    // geometry 保存
    s.saveMainWindow(saveGeometry());

    // English / Optional / Spec / Feature をすべて保存
    saveProgramButtons(Constants::EnglishPrograms, s);
    saveProgramButtons(Constants::OptionalPrograms, s);
    saveProgramButtons(Constants::SpecPrograms, s);
    saveProgramButtons(Constants::FeatureSettings, s);
    

    // audio_extension
    if (auto combo = findChild<QComboBox*>("comboBox_extension"))
        s.audioExtension = combo->currentText();

    // 最後に settings.ini へ保存
    s.save();
}

template <typename Container>
void MainWindow::saveProgramButtons(const Container &programs, Settings &s)
{
    for (const auto &p : programs) {
        if (qs(p.objectName).isEmpty())
            continue;

        // QAbstractButton で統一（QToolButton も QCheckBox も継承）
        if (auto btn = findChild<QAbstractButton*>(qs(p.objectName))) {
            s.checked[p.keyChecked] = btn->isChecked();
        }
    }
}

void MainWindow::ffmpegFolder() {
	ffmpegFolderDialog();
}

void MainWindow::ffmpegFolderDialog()
{
    auto &s = Settings::instance();

    QMessageBox msgBox(this);
    QString message = QString::fromUtf8("ffmpegがあるフォルダを設定しますか？\n現在設定：\n") 
                      + s.ffmpegFolder;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle(tr("ffmpegがあるフォルダ設定"));
    msgBox.setText(message);

    QPushButton* setButton = msgBox.addButton(tr("設定する"), QMessageBox::ActionRole);
    QPushButton* searchButton = msgBox.addButton(tr("検索"), QMessageBox::ActionRole);
    QPushButton* bundledButton = msgBox.addButton(tr("同梱"), QMessageBox::ActionRole);
    QPushButton* resetButton = msgBox.addButton(tr("初期値に戻す"), QMessageBox::ActionRole);
    msgBox.setStandardButtons(QMessageBox::Cancel);

    if (msgBox.exec() == QMessageBox::Cancel)
        return;

    QPushButton* clicked = qobject_cast<QPushButton*>(msgBox.clickedButton());

    if (clicked == setButton) {

        QString dir = QFileDialog::getExistingDirectory(
            this, tr("ffmpegがあるフォルダを指定してください"),
            s.ffmpegFolder,
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (!dir.isEmpty())
            s.ffmpegFolder = dir + QDir::separator();

    } else if (clicked == resetButton) {

        s.ffmpegFolder = Utility::applicationBundlePath();

    } else if (clicked == searchButton) {

        QString dir = Settings::instance().detectFfmpegFolder();
        if (!dir.isEmpty()) {
            QString msg = QString::fromUtf8("ffmpegがある下記フォルダを見つけました。\n設定しますか？\n\n") + dir;
            if (QMessageBox::Yes == QMessageBox::question(this, tr("ffmpegフォルダ設定"), msg))
                s.ffmpegFolder = dir + QDir::separator();
        }

    } else if (clicked == bundledButton) {

        QString dir = Utility::applicationBundlePath();
        QString msg = QString::fromUtf8("同梱のffmpegを使用します。\n設定しますか？\n\n") + dir;
        if (QMessageBox::Yes == QMessageBox::question(this, tr("同梱ffmpeg設定"), msg))
            s.ffmpegFolder = dir + QDir::separator();
    }
}

void MainWindow::customizeSaveFolder()
{
    auto &s = Settings::instance();
    QString base = s.saveFolder;

#if defined(Q_OS_WIN)
    QString folderPath;
    if (isWineEnvironment()) {
        folderPath = getPortableFolderDialog(
            this,
            tr("書き込み可能な保存フォルダを指定してください"),
            base
        );
    } else {
        folderPath = QFileDialog::getExistingDirectory(
            this,
            tr("書き込み可能な保存フォルダを指定してください"),
            base,
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    }
    QString dir = QFileInfo(folderPath).absoluteFilePath();
#else
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("書き込み可能な保存フォルダを指定してください"),
        base,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
#endif

    if (!dir.isEmpty()) {
        s.saveFolder = dir + QDir::separator();
    }
}

void MainWindow::customizeFolderOpen()
{
    auto &s = Settings::instance();
    QString folder = s.saveFolder;

    bool success = false;

#if defined(Q_OS_WIN)
    if (isWineEnvironment()) {
        QString dir = convertWinePathToUnix(folder);
        openUrlWithFallbackDialog(QUrl::fromLocalFile(dir), this);
        success = true;
    } else {
        success = QDesktopServices::openUrl(QUrl("file:///" + folder, QUrl::TolerantMode));
    }
#elif defined(Q_OS_MAC)
    success = QDesktopServices::openUrl(QUrl("file:///" + folder, QUrl::TolerantMode));
#elif defined(Q_OS_LINUX)
    QString dir = convertWinePathToUnixAuto(folder);
    QString cmd = QString("xdg-open \"%1\"").arg(dir);
    openUrlWithFallbackDialog(QUrl::fromLocalFile(dir), this);
    success = QProcess::startDetached("/bin/sh", QStringList() << "-c" << cmd);
    if (!success) {
        success = QDesktopServices::openUrl(folder);
    }
#else
    success = QDesktopServices::openUrl(QUrl("file:///" + folder, QUrl::TolerantMode));
    if (!success) {
        success = QDesktopServices::openUrl(folder);
    }
#endif

    if (!success) {
        success = QDesktopServices::openUrl(folder);
    }

    if (!success) {
        QString fallbackMessage =
            tr("フォルダを開くことができませんでした。\nパス: %1").arg(folder);
        QMessageBox::warning(nullptr, tr("エラー"), fallbackMessage);
    }
}

/*
void MainWindow::updateButtonUI(QToolButton* btn, bool checked, const QString& baseLabel)
{
    const QString check = QString::fromUtf8("✓ ");

    btn->blockSignals(true);
    btn->setChecked(checked);
    btn->blockSignals(false);

    if (baseLabel.isEmpty()) return;
    QString text = baseLabel;
    if (checked) {		
        text.prepend(check);	            // 状態に応じて「✓」付与
    }
    btn->setText(text);
}

void MainWindow::saveGui()
{
    auto &s = Settings::instance();

    // geometry 保存
    s.saveMainWindow(saveGeometry());

    // checked の書き戻し
    for (const auto &p : Constants::EnglishPrograms) {
        if (!qs(p.objectName).isEmpty()) {
            if (auto btn = findChild<QToolButton*>(qs(p.objectName))) {
                s.checked[p.keyChecked] = btn->isChecked();
            }
        }
    }

    for (const auto &p : Constants::OptionalPrograms) {
        if (!qs(p.objectName).isEmpty()) {
            if (auto btn = findChild<QToolButton*>(qs(p.objectName))) {
                s.checked[p.keyChecked] = btn->isChecked();
            }
        }
    }

    for (const auto &p : Constants::SpecPrograms) {
        if (!qs(p.objectName).isEmpty()) {
            if (auto btn = findChild<QToolButton*>(qs(p.objectName))) {
                s.checked[p.keyChecked] = btn->isChecked();
            }
        }
    }

    for (const auto &p : Constants::FeatureSettings) {
        if (!qs(p.objectName).isEmpty()) {
            if (auto cb = findChild<QAbstractButton*>(qs(p.objectName))) {
                s.checked[p.keyChecked] = cb->isChecked();
            }
        }
    }

    // 最後に settings.ini へ保存
    s.save();
}
*/

void MainWindow::customizeTitle() {
	CustomizeDialog dialog( Ui::TitleMode );
	dialog.exec();
}

void MainWindow::customizeFileName() {
	CustomizeDialog dialog( Ui::FileNameMode );
	dialog.exec();
}
/*
void MainWindow::customizeSaveFolder() {
#if defined(Q_OS_WIN)
	QString folderPath;
	if (isWineEnvironment()) {
	   	 folderPath = getPortableFolderDialog(this, tr("書き込み可能な保存フォルダを指定してください"), outputDir);
	} else {
	   	 folderPath = QFileDialog::getExistingDirectory(this, tr("書き込み可能な保存フォルダを指定してください"),
                                                  outputDir,
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	}
	QString dir = QFileInfo(folderPath).absoluteFilePath();
#else
	QString dir = QFileDialog::getExistingDirectory( 0, QString::fromUtf8( "書き込み可能な保存フォルダを指定してください" ),
							   outputDir, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
#endif
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
	QString dir = convertWinePathToUnixAuto( outputDir );
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
*/
void MainWindow::homepageOpen() {
	QString versionStr = Constants::AppVersion;
	QString latestVersionRaw = Utility::getLatest_version();
	QString latestVersionFormatted = latestVersionRaw.left(4) + "/" + latestVersionRaw.mid(4, 2) + "/" + latestVersionRaw.mid(6, 2);

	int currentVersion = versionStr.remove("/").toInt();
	int latestVersion = latestVersionRaw.left(8).toInt();

	QString message;
	if (latestVersion > currentVersion) {
		message = QString::fromUtf8("最新版があります\n現在：") + Constants::AppVersion +
		          QString::fromUtf8("\n最新：") + latestVersionFormatted +
		          QString::fromUtf8("\n表示しますか？");
	} else if (latestVersion < currentVersion) {
		message = QString::fromUtf8("最新版を確認して下さい\n現在：") + Constants::AppVersion +
		          QString::fromUtf8("\n表示しますか？");
	} else {
		message = QString::fromUtf8("最新版です\n現在：") + Constants::AppVersion +
		          QString::fromUtf8("\n表示しますか？");
	}

	int res = QMessageBox::question(this, tr("ホームページ表示"), message);
	if (res == QMessageBox::Yes) {
		openUrlWithFallbackDialog(QUrl("https://csreviser.github.io/CaptureStream2/", QUrl::TolerantMode),this);
//		QDesktopServices::openUrl(QUrl("https://csreviser.github.io/CaptureStream2/", QUrl::TolerantMode));
	}
}
/*
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

	if (clicked == setButton) {
#if defined(Q_OS_WIN)	
		QString folderPath;
		if (isWineEnvironment()) {
   		folderPath = getPortableFolderDialog(this, tr("ffmpegがあるフォルダを指定してください"), ffmpeg_folder);
		} else {
  		  folderPath = QFileDialog::getExistingDirectory(this, tr("ffmpegがあるフォルダを指定してください"),
                                                   ffmpeg_folder,
                                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		}
		QString dir = QFileInfo(folderPath).absoluteFilePath();
#else
		QString dir = QFileDialog::getExistingDirectory(this, QString::fromUtf8("ffmpegがあるフォルダを指定してください"),
						ffmpeg_folder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif	
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
*/
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
    	programList_english = false; programList_others =false; programList_all = false;
	if ( msgbox.clickedButton() == anyButton) id_List_flag = 1;
	if ( msgbox.clickedButton() == anyButton1) id_List_flag = 2;
	if ( msgbox.clickedButton() == anyButton2) { id_List_flag = 3; programList_all=true; }
	
	if ( !downloadThread ) {	//レコーディング実行
//		if ( messagewindow.text().length() > 0 )
		messagewindow.appendParagraph( "\n----------------------------------------" );
		messagewindow.appendParagraph( "*****　　番組一覧　　*****" );
		messagewindow.appendParagraph( "----------------------------------------" );
		ui->downloadButton->setEnabled( false );
		downloadThread = new DownloadThread( Settings::instance(), runtime, ui );
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
	ScrambleDialog dialog( Settings::instance(), this );

	if (!dialog.exec())
	    return;
	    
	auto &s = Settings::instance();    
	updateProgramButtons(Constants::OptionalPrograms, s);
}

void MainWindow::customizeSettings() {
	Settingsdialog dialog( Settings::instance(), this );

	if (!dialog.exec())
	    return;
	    
	auto &s = Settings::instance();  
	updateProgramButtons(Constants::SpecPrograms, s);
}
        
void MainWindow::download() {	//「レコーディング」または「キャンセル」ボタンが押されると呼び出される
	if ( !downloadThread ) {	//レコーディング実行
		GuiState gui = GuiState::fromMainWindow(*this);
		RuntimeConfig runtime;
		runtime.applySettings(Settings::instance());
		runtime.applyGuiState(guiState);

		if ( messagewindow.text().length() > 0 )
			messagewindow.appendParagraph( "\n----------------------------------------" );
		ui->downloadButton->setEnabled( false );
		downloadThread = new DownloadThread( runtime, ui );
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

void MainWindow::toggled(bool checked)
{
    auto* button = qobject_cast<QToolButton*>(sender());
    if (!button)
        return;

    const QString obj = button->objectName();

    // ProgramDefinition を objectName から直接検索
    const Constants::ProgramDefinition* p = findEntryByObjectName(obj);
    if (!p)
        return;

    // Settings を更新
    Settings& s = Settings::instance();
    s.checked[p->keyChecked] = checked;

    // タイトルは Settings から取得（ここが最重要）
    QString baseLabel;
    if (p->hasLabel) {
        // ユーザーが変更したタイトル
        baseLabel = s.labels[p->keyLabel];
    } else {
        // English など固定タイトル
        baseLabel = p->labelDefault;
    }

    // UI 更新（✓ の付け外しだけ担当）
    updateButtonUI(button, checked, baseLabel);
}

const Constants::ProgramDefinition* MainWindow::findEntryByObjectName(const QString& obj) const
{
    auto search = [&](const auto& list) -> const Constants::ProgramDefinition* {
        for (const auto& p : list) {
            if (p.objectName == obj)
                return &p;
        }
        return nullptr;
    };

    if (auto* p = search(Constants::EnglishPrograms))  return p;
    if (auto* p = search(Constants::OptionalPrograms)) return p;
    if (auto* p = search(Constants::SpecPrograms))     return p;
    if (auto* p = search(Constants::FeatureSettings))  return p;
    
    return nullptr;
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
	
	QFile::remove( ini_file_path + Constants::IniFileName );
	
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
//        if (!name_map.contains(koza)) continue;

//        QString url = name_map[koza];
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

bool MainWindow::isRunningOnWine()
{
#ifdef Q_OS_WIN
    QFile file("/proc/version");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray content = file.readAll();
        return content.contains("Wine");
    }
#endif
    return false;
}

QString MainWindow::safeWineToUnixPath(const QString &maybeWinePath)
{
    if (!isRunningUnderWine())
        return maybeWinePath;

    if (isWinePathAvailable())
        return wineToUnixPath(maybeWinePath);

    return fallbackWineToUnixPath(maybeWinePath);
}

QString MainWindow::getPortableFolderDialog(QWidget *parent, const QString &title, const QString &initialDir)
{
    QFileDialog dialog(parent, title, initialDir);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setOption(QFileDialog::DontUseNativeDialog, true); // ★重要
    if (dialog.exec() == QDialog::Accepted) {
        return dialog.selectedFiles().first();
    } else {
        QMessageBox::information(parent, QObject::tr("キャンセル"),
                                 QObject::tr("フォルダが選択されませんでした。"));
        return QString();
    }
}

QString MainWindow::getCompatibleFolderDialog(QWidget *parent, const QString &title, const QString &initialDir)
{
    QFileDialog dialog(parent, title, initialDir);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);

    if (isRunningOnWine()) {
        // Wine環境下では非ネイティブダイアログを強制使用
        dialog.setOption(QFileDialog::DontUseNativeDialog, true);
    }

    if (dialog.exec() == QDialog::Accepted) {
        return dialog.selectedFiles().first();
    } else {
        QMessageBox::information(parent, QObject::tr("キャンセル"),
                                 QObject::tr("フォルダが選択されませんでした。"));
        return QString();
    }
}

QString MainWindow::convertWinePathToUnixAuto(const QString &winePath)
{
    // まず Windows パス形式かどうかを正規表現で確認
    QRegularExpression regex("^([A-Z]):/(.+)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = regex.match(winePath);
    if (!match.hasMatch())
        return winePath; // すでに Unix 形式と思われる

    // winepath を試す
    QProcess proc;
    proc.start("winepath", QStringList() << "-u" << winePath);
    if (proc.waitForFinished(1000)) {
        QString output = QString::fromUtf8(proc.readAllStandardOutput()).trimmed();
        if (!output.isEmpty() && QFileInfo::exists(output)) {
            return output;
        }
    }

    // winepath が使えなかった場合、フォールバック手動変換（Z: → /、それ以外 → /mnt/x/...）
    QString driveLetter = match.captured(1).toUpper();
    QString subPath = match.captured(2);

    if (driveLetter == "Z") {
        return "/" + subPath;
    } else {
        return QString("/mnt/%1/%2").arg(driveLetter.toLower(), subPath);
    }
}

bool MainWindow::guiFlagValue(const QString& key) const
{
    if (key == Constants::KEY_LAST_WEEK)   return ui->checkBox_next_week2->isChecked();
    if (key == Constants::KEY_PROGRAM_LIST)return programList_all;
    if (key == Constants::KEY_NOGUI)       return false; // GUIでは常にfalse

    return false;
}
