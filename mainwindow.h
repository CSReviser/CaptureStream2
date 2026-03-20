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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>
#include <QCloseEvent>
#include <QObject>
#include <QNetworkAccessManager>
#include <QList>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>
#include <QMutex>
#include <QStringList>
#include <QToolButton>
#include "messagewindow.h"
#include "settings.h"
#include "runtimeconfig.h"

class RecordingCore;
//class RecordingCore;

namespace Ui {
	class MainWindowClass;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	enum ReadWriteMode {
		ReadMode, WriteMode
	};

public:
	MainWindow( Settings& settings, QWidget* parent = nullptr );
	~MainWindow();

	static QString outputDir;
	static QString optional[];
	static QString ffmpeg_folder;
	static bool multi_gui_flag;
	static QString findFfmpegPath();

	bool guiFlagValue(const QString& key) const;

protected:
	virtual void closeEvent( QCloseEvent *event );

public slots:
	void download();
	void toggled( bool checked );

private slots:
	void finished();
	void customizeTitle();
	void customizeFileName();
	void customizeSaveFolder();
	void customizeFolderOpen();
	void ffmpegFolder();
	void homepageOpen();
	void programlist();
	void customizeScramble();
	void customizeSettings();
	void closeEvent2( );
	bool isWineEnvironment();
	void openUrlWithFallbackDialog(const QUrl &url,QWidget *parent);
	QString normalizePathForWine(const QString &originalPath);
	QString convertWinePathToUnix(const QString &winePath);
	QString convertWinePathToUnixAuto(const QString &winePath);
	bool isWinePathAvailable();
	QString wineToUnixPath(const QString &winePath);
	QString unixToWinePath(const QString &unixPath);
	QString fallbackWineToUnixPath(const QString &winePath);
	bool isRunningUnderWine();
	bool isRunningOnWine();
	QString safeWineToUnixPath(const QString &maybeWinePath);
	QString getPortableFolderDialog(QWidget *parent, const QString &title, const QString &initialDir);
	QString getCompatibleFolderDialog(QWidget *parent, const QString &title, const QString &initialDir);
	bool isValidExt(const QString& ext);

private:
	QStringList getAttribute( QString url, QString attribute );
	Ui::MainWindowClass *ui;
	RecordingCore* recordingCore;
	QMenu* customizeMenu;
	MessageWindow messagewindow;
	QEventLoop eventLoop;

	Settings& settings;
		
	void restoreGui();
	void saveGui();
	template <typename Container>
	void updateProgramButtons(const Container &program, int count, const Settings &s);
	template <typename Container>
	void saveProgramButtons(const Container &programs, int count, Settings &s);
	void updateButtonUI(QToolButton* btn, bool checked, const QString& label);
	const Constants::ProgramDefinition* findEntryByObjectName(const QString& obj) const;

	void ffmpegFolderDialog();
	void showProgramList();
	int id_List_flag;

};

#endif // MAINWINDOW_H
