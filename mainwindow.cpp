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
#include "recordingcore.h"
#include "customizedialog.h"
#include "scrambledialog.h"
#include "settingsdialog.h"
#include "utility.h"
#include "programrepository.h"
#include "programlistservice.h"
#include "programformatter.h"
#include "guistate.h"

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
#include <QUrl>
#include <QUrlQuery>
#include <QTemporaryFile>
#include <QVariant>
#include <QDesktopServices>
#include <QSysInfo>
#include <QVector>
#include <QSet>
#include <QString>
#include <QProcessEnvironment>
#include <QWidget>
#include <QTimer>

namespace {

#ifdef Q_OS_WIN
	constexpr const char* STYLE_SHEET = "stylesheet-win.qss";
#elif defined(Q_OS_MACOS)
	constexpr const char* STYLE_SHEET = "stylesheet-mac.qss";
#else
	constexpr const char* STYLE_SHEET = "stylesheet-ubu.qss";
#endif

	QString version() {
		QString result;
			result = QString::fromUtf8( "  (" ) + QString::fromUtf8(Constants::AppVersion) + QString::fromUtf8( ")" );
		return result;
	}
}

QString MainWindow::outputDir;

QString MainWindow::optional[] = {"0953", "4412", "0943", "4410", "0946", "4411", "0948", "4413", "0948", "4413"};
QString MainWindow::ffmpeg_folder;
bool MainWindow::multi_gui_flag;
		
MainWindow::MainWindow( Settings& settings, QWidget *parent )
		: QMainWindow( parent ), ui( new Ui::MainWindowClass ), recordingCore( NULL )
		, settings(settings) {
	
	ui->setupUi( this );
	resize(540, 500);
	settings.load();

	// ★ 番組一覧の初期化（非同期）
	auto &repo = ProgramRepository::instance();
	repo.updatePrograms();

	// ★ 番組一覧更新後に UI を更新したい場合
//	connect(&repo, &ProgramRepository::programListUpdated,
//	    this, &MainWindow::onProgramListUpdated);


	ui->comboBox_extension->clear();
	for (int i = 0; i < Constants::AUDIO_EXT_COUNT; ++i) {
	    ui->comboBox_extension->addItem(QString::fromUtf8(Constants::AUDIO_EXT_LIST[i]));
	}
	restoreGui();
	
	this->setWindowTitle( Constants::AppName + version() );
	QString ver_tmp1 = Constants::AppVersion;
	QString ver_tmp2 = ver_tmp1.remove("/");
	QString ver_tmp3 = Utility::getLatest_version();
	int current_version = ver_tmp2.toInt();
	int Latest_version = ver_tmp3.left(8).toInt();
	if ( Latest_version > current_version )
		this->setWindowTitle( this->windowTitle() + QString("  upgrade!" ) );
	menuBar()->setNativeMenuBar(false);
#ifdef Q_OS_MACOS		// Macのウィンドウメニュー切り替え
	menuBar()->setNativeMenuBar(settings.checked[QString::fromUtf8(Constants::KEY_MAC_MENUBAR)]);
#endif

//#if !defined( Q_OS_MACOS ) && !defined( Q_OS_WIN )
	QPoint bottomLeft = geometry().bottomLeft();
	bottomLeft += QPoint( 0, menuBar()->height() + statusBar()->height() + 3 );
	messagewindow.move( bottomLeft );
//#endif
	
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

	connect(ui->comboBox_extension, &QComboBox::currentTextChanged,
	        this, [](const QString& text){
	            auto &s = Settings::instance();
	            s.audioExtension = text;
	        });
	
	//action = new QAction( QString::fromUtf8( "スクランブル文字列..." ), this );
	//connect( action, SIGNAL( triggered() ), this, SLOT( customizeScramble() ) );
	//customizeMenu->addAction( action );

	QFont f = qApp->font();
	f.setPointSize( 11 );
	qApp->setFont(f);


	auto &s = Settings::instance();
	QStringList candidates;
	candidates
	    << s.saveFolder + STYLE_SHEET
	    << Utility::appConfigLocationPath() + STYLE_SHEET
	    << Utility::ConfigLocationPath() + STYLE_SHEET
	    << Utility::applicationBundlePath() + STYLE_SHEET
	    << QString(":/") + STYLE_SHEET;

	QString styleSheet = Utility::loadFirstExistingTextFile(candidates);

	qApp->setStyleSheet(styleSheet);
        resize(540, 500);
        QTimer::singleShot(0, this, [this]{
		 adjustSize();
	});
#ifdef Q_OS_MACOS
	adjustSize();
	move( 70, 22 );
#endif 	
	multi_gui_flag = settings.checked[QString::fromUtf8(Constants::KEY_MULTI_GUI)];
	if(multi_gui_flag) Utility::remove_LockFile();
//	if ( !multi_gui_flag ) Utility::unLockFile();
//	Utility::remove_LockFile();
//	Utility::tryLockFile();
//	Utility::unLockFile();
//	adjustSize();                             //高DPIディスプレイ対応
//	setFixedSize(size());
//	int dpiX = qApp->desktop()->logicalDpiX();
//	QFont f = qApp->font();
//	int defaultFontSize = f.pointSize() * ( 96.0 / dpiX );
//	f.setPointSize( defaultFontSize );
//	f.setPointSize( 11 );
//	qApp->setFont(f);
}

MainWindow::~MainWindow() {
	if ( recordingCore ) {
		recordingCore->terminate();
		delete recordingCore;
	}
	saveGui();
	delete ui;
}

void MainWindow::closeEvent( QCloseEvent *event ) {
	Q_UNUSED( event )
	if ( recordingCore ) {
		messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセル中..." ) );
		download();
	}
	Utility::unLockFile();
	messagewindow.close();
	QCoreApplication::exit();
}
/*
void MainWindow::settings1( enum ReadWriteMode mode ) {
	if ( mode == ReadMode ) {	// 設定読み込み
		QVariant saved;
		
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

		restoreGui();
		multi_gui_flag = settings.checked[QString::fromUtf8(Constants::KEY_MULTI_GUI)];
		if(multi_gui_flag) Utility::remove_LockFile();

	} else {	// 設定書き出し
saveGui();
	}
}
*/
void MainWindow::restoreGui()
{
    auto &s = Settings::instance();
    QVariant saved;
		
    // geometry 復元
    if (!s.mainWindowGeometry.isEmpty()) {
        QSize windowSize = size();
        restoreGeometry(s.mainWindowGeometry);
        resize( windowSize );
    } else {
        resize(540, 500);
        move( 70, 22 );
    }

    // ===== English =====
    updateProgramButtons(Constants::EnglishPrograms, Constants::getEnglishCount(), s);
     // ===== Optional =====   
    updateProgramButtons(Constants::OptionalPrograms, Constants::getOptionalCount(), s);

    for (int i = 0; i < Constants::OptionalCount; i++) {
	const auto &p = Constants::OptionalPrograms[i];

    	// objectName からボタンを取得
	QAbstractButton* btn =
		this->findChild<QAbstractButton*>(QString::fromUtf8(p.objectName));

 	if (!btn)
 		continue; // UI に存在しない場合はスキップ

	// Settings の値を反映
	optional[i] = settings.ids[p.keyId];
    }

    // ===== Spec =====
    updateProgramButtons(Constants::SpecPrograms, Constants::getSpecCount(), s);
    // ===== Feature（チェックボックス）=====
    updateProgramButtons(Constants::FeatureSettings, Constants::getFeatureCount(), s);

    // saveFolder が未設定なら設定ダイアログを開く
     if (s.saveFolder.isEmpty()) {
        customizeSaveFolder();
    }
    // ffmpeg が未設定なら設定
    if (s.ffmpegFolder.isEmpty()) {
        s.ffmpegFolder = Utility::applicationBundlePath();
    }
    
    // audio_extension
    if (auto combo = findChild<QComboBox*>("comboBox_extension")) {
        int index = combo->findText(s.audioExtension);
        if (index >= 0)
            combo->setCurrentIndex(index);
     }           
    ui->checkBox_thumbnail->setChecked(settings.checked["thumbnail"]);

    multi_gui_flag = settings.checked[QString::fromUtf8(Constants::KEY_MULTI_GUI)];
    if(multi_gui_flag) Utility::remove_LockFile();

#if defined( Q_OS_WIN )
		outputDir = unixToWinePath(outputDir);
		ffmpeg_folder = unixToWinePath(ffmpeg_folder);
#else
		outputDir = convertWinePathToUnixAuto(outputDir);
		ffmpeg_folder = convertWinePathToUnixAuto(ffmpeg_folder);
#endif	
}

template <typename Container>
void MainWindow::updateProgramButtons(const Container &programs, int count, const Settings &s)
{
    for (int i =0; i< count; ++i) {
        const auto &p = programs[i];
        if (auto btn = findChild<QToolButton*>(QString::fromUtf8(p.objectName))) {

            QString label;
//          if (QString::fromUtf8(p.keyLabel).isEmpty()) {         
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
    saveProgramButtons(Constants::EnglishPrograms, Constants::getEnglishCount(), s);
    saveProgramButtons(Constants::OptionalPrograms, Constants::getOptionalCount(), s);
    saveProgramButtons(Constants::SpecPrograms, Constants::getSpecCount(), s);
    saveProgramButtons(Constants::FeatureSettings, Constants::getFeatureCount(), s);
    

    // audio_extension
    if (auto combo = findChild<QComboBox*>( QString::fromUtf8(Constants::KEY_AudioExtension)))
        s.audioExtension = combo->currentText();

    // 最後に settings.ini へ保存
    s.save();
}

bool MainWindow::isValidExt(const QString& ext) {
    for (int i = 0; i < Constants::AUDIO_EXT_COUNT; ++i) {
        if (ext == Constants::AUDIO_EXT_LIST[i]) return true;
    }
    return false;
}

template <typename Container>
void MainWindow::saveProgramButtons(const Container &programs, int count, Settings &s)
{
    for (int i =0; i< count; ++i) {
        const auto &p = programs[i];
        if (QString::fromUtf8(p.objectName).isEmpty())
            continue;

        // QAbstractButton で統一（QToolButton も QCheckBox も継承）
        if (auto btn = findChild<QAbstractButton*>(QString::fromUtf8(p.objectName))) {
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

	QStringList candidates;
	candidates
	    << s.saveFolder + STYLE_SHEET
	    << Utility::appConfigLocationPath() + STYLE_SHEET
	    << Utility::ConfigLocationPath() + STYLE_SHEET
	    << Utility::applicationBundlePath() + STYLE_SHEET
	    << QString(":/") + STYLE_SHEET;

	QString styleSheet = Utility::loadFirstExistingTextFile(candidates);

	qApp->setStyleSheet(styleSheet);
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

void MainWindow::customizeTitle() {
	CustomizeDialog dialog( Ui::TitleMode );
	dialog.exec();
}

void MainWindow::customizeFileName() {
	CustomizeDialog dialog( Ui::FileNameMode );
	dialog.exec();
}

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

	QMessageBox msgbox(this);
	
	// ★ 番組一覧の初期化（非同期）
	auto &repo = ProgramRepository::instance();
	repo.updatePrograms();
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
	
    if (button != QMessageBox::Cancel) {
    
        if (msgbox.clickedButton() == anyButton)  id_List_flag = 1;
        if (msgbox.clickedButton() == anyButton1) id_List_flag = 2;
        if (msgbox.clickedButton() == anyButton2) id_List_flag = 3;

        messagewindow.show();
        messagewindow.appendParagraph("\n----------------------------------------");
        messagewindow.appendParagraph("*****　　番組一覧　　*****");
        messagewindow.appendParagraph("----------------------------------------");

        showProgramList();
    }	
}

void MainWindow::showProgramList()
{
    QStringList list = ProgramListService::buildProgramList(id_List_flag);

    for (auto& line : ProgramFormatter::toLines(list))
        messagewindow.appendParagraph(line);
}

void MainWindow::customizeScramble() {
	ScrambleDialog dialog( Settings::instance(), this );

	if (!dialog.exec())
	    return;
	    
	auto &s = Settings::instance();    
	updateProgramButtons(Constants::OptionalPrograms, Constants::getOptionalCount(), s);
}

void MainWindow::customizeSettings() {
	Settingsdialog dialog( Settings::instance(), this );

	if (!dialog.exec())
	    return;
	    
	auto &s = Settings::instance();  
	updateProgramButtons(Constants::SpecPrograms, Constants::getSpecCount(), s);
#ifdef Q_OS_MACOS
	menuBar()->setNativeMenuBar(settings.checked[QString::fromUtf8(Constants::KEY_MAC_MENUBAR)]);
#endif
}
        
void MainWindow::download() {	//「レコーディング」または「キャンセル」ボタンが押されると呼び出される
	if ( !recordingCore ) {	//レコーディング実行
//		saveGui();
		GuiState gui = GuiState::fromMainWindow(*this);
		RuntimeConfig runtime;
		runtime.applySettings(Settings::instance());
		runtime.applyGui(gui);

		if ( messagewindow.text().length() > 0 )
			messagewindow.appendParagraph( "\n----------------------------------------" );
		ui->downloadButton->setEnabled( false );
		recordingCore = new RecordingCore( runtime );
		connect(recordingCore, &RecordingCore::messageGenerated,
		        &messagewindow, &MessageWindow::appendParagraph);

		connect(recordingCore, &RecordingCore::errorOccurred,
		        &messagewindow, &MessageWindow::appendParagraph);

		connect(recordingCore, &RecordingCore::finished,
		        this, &MainWindow::finished);

		connect(ui->downloadButton, &QPushButton::clicked,
		        recordingCore, &RecordingCore::requestCancel);
		recordingCore->start();
		ui->downloadButton->setText( QString::fromUtf8( "キャンセル" ) );
		ui->downloadButton->setEnabled( true );
	} else {	//キャンセル
		recordingCore->disconnect();	//wait中にSIGNALが発生するとデッドロックするためすべてdisconnect
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
    // 引数を「配列の先頭ポインタ」と「個数」に変更する
    auto search = [&](const Constants::ProgramDefinition* list, int count) -> const Constants::ProgramDefinition* {
        for (int i = 0; i < count; ++i) {
            const auto& p = list[i];
            if (QString(p.objectName) == obj)
                return &p;
        }
        return nullptr;
    };

    // 呼び出し時に Constants から取得した個数を渡す
    if (auto* p = search(Constants::EnglishPrograms, Constants::getEnglishCount()))  return p;
    if (auto* p = search(Constants::OptionalPrograms, Constants::getOptionalCount())) return p;
    if (auto* p = search(Constants::SpecPrograms, Constants::getSpecCount()))     return p;
    
    // FeatureSettings も同様に関数化されている前提です
    if (auto* p = search(Constants::FeatureSettings, Constants::getFeatureCount()))  return p;
    
    return nullptr;
}

void MainWindow::finished() {
	if ( recordingCore ) {
		ui->downloadButton->setEnabled( false );
		if ( recordingCore->isRunning() ) {	//キャンセルでMainWindow::downloadから呼ばれた場合
			recordingCore->cancel();
			recordingCore->wait();
			messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセルしました。" ) );
		}
		delete recordingCore;
		recordingCore = NULL;
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
		if ( recordingCore ) {
			messagewindow.appendParagraph( QString::fromUtf8( "レコーディングをキャンセル中..." ) );
			download();
		}
		if (!Settings::deleteSettingsFile()){
		        QMessageBox::warning(
		            this,
		            tr("エラー"),
		            tr("設定ファイル削除に失敗しました")
 	       		);
		}
		Utility::unLockFile();
		messagewindow.close();
		Settings::deleteSettingsFile();
		QCoreApplication::quit();
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
//   if (key == Constants::KEY_PROGRAM_LIST)return programList_all;
    if (key == Constants::KEY_NOGUI)       return false; // GUIでは常にfalse

    return false;
}

