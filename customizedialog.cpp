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

#include "customizedialog.h"
#include "settings.h"
#include "constants.h"
#include "mainwindow.h"

CustomizeDialog::CustomizeDialog(Ui::DialogMode mode, QWidget *parent)
    : QDialog(parent), mode(mode)
{
    ui.setupUi(this);

    setWindowTitle(mode == Ui::TitleMode
                   ? QStringLiteral("タイトルタグ設定")
                   : QStringLiteral("ファイル名設定"));

    loadSettings();

    // ラジオボタン → プリセット適用
    connect(ui.radioButton, &QRadioButton::clicked, this, [this](){ applyPreset(0); });
    connect(ui.radioButton_1, &QRadioButton::clicked, this, [this](){ applyPreset(1); });
    connect(ui.radioButton_2, &QRadioButton::clicked, this, [this](){ applyPreset(2); });
    connect(ui.radioButton_3, &QRadioButton::clicked, this, [this](){ applyPreset(3); });
    connect(ui.radioButton_4, &QRadioButton::clicked, this, [this](){ applyPreset(4); });
    connect(ui.radioButton_5, &QRadioButton::clicked, this, [this](){ applyPreset(5); });
    connect(ui.radioButton_6, &QRadioButton::clicked, this, [this](){ applyPreset(6); });

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
}

/* ============================================================
 *  formats()
 *  course → settings.ini から titleFormat / fileNameFormat を取得
 * ============================================================ */
void CustomizeDialog::formats(QString course, QString& titleFormat, QString& fileNameFormat)
{
    int index = Constants::COURSES.indexOf(course);
    if (index < 0)
        index = 0;

    titleFormat    = Settings::titleFormat(index);
    fileNameFormat = Settings::fileNameFormat(index);
}

/* ============================================================
 *  設定読み込み
 * ============================================================ */
void CustomizeDialog::loadSettings()
{
    ui.lineEdit->setText(
        mode == Ui::TitleMode
            ? Settings::titleFormat(0)
            : Settings::fileNameFormat(0)
    );

    ui.lineEdit_2->setText(
        mode == Ui::TitleMode
            ? Settings::titleFormat(1)
            : Settings::fileNameFormat(1)
    );

    if (mode == Ui::TitleMode)
        ui.checkBox->setChecked(Settings::tagSpaceFlag());
    else
        ui.checkBox->setChecked(Settings::nameSpaceFlag());
}

/* ============================================================
 *  設定保存
 * ============================================================ */
void CustomizeDialog::saveSettings()
{
    if (mode == Ui::TitleMode) {
        Settings::setTitleFormat(0, ui.lineEdit->text());
        Settings::setTitleFormat(1, ui.lineEdit_2->text());
        Settings::setTagSpaceFlag(ui.checkBox->isChecked());
    } else {
        Settings::setFileNameFormat(0, ui.lineEdit->text());
        Settings::setFileNameFormat(1, ui.lineEdit_2->text());
        Settings::setNameSpaceFlag(ui.checkBox->isChecked());
    }
}

/* ============================================================
 *  OK ボタン
 * ============================================================ */
void CustomizeDialog::accepted()
{
    saveSettings();
}

/* ============================================================
 *  プリセット適用（構造体ベース）
 * ============================================================ */
void CustomizeDialog::applyPreset(int index)
{
    if (mode == Ui::TitleMode) {
        ui.lineEdit->setText(Constants::TITLE_PRESETS[index].value);
    } else {
        ui.lineEdit->setText(Constants::FILENAME_PRESETS[index].value);
    }
}


/*
#include "customizedialog.h"
#include "settings.h"
#include "constants.h"
#include "mainwindow.h"

CustomizeDialog::CustomizeDialog(Ui::DialogMode mode, QWidget *parent)
    : QDialog(parent), mode(mode)
{
    ui.setupUi(this);

    setWindowTitle(mode == Ui::TitleMode
                   ? QStringLiteral("タイトルタグ設定")
                   : QStringLiteral("ファイル名設定"));

    loadSettings();

    connect(this, SIGNAL(accepted()), this, SLOT(accepted()));
}

void CustomizeDialog::loadSettings()
{
    // index 0,1 の設定値を読み込む
    ui.lineEdit->setText(
        mode == Ui::TitleMode
            ? Settings::titleFormat(0)
            : Settings::fileNameFormat(0)
    );

    ui.lineEdit_2->setText(
        mode == Ui::TitleMode
            ? Settings::titleFormat(1)
            : Settings::fileNameFormat(1)
    );

    // チェックボックス
    if (mode == Ui::TitleMode)
        ui.checkBox->setChecked(Settings::tagSpaceFlag());
    else
        ui.checkBox->setChecked(Settings::nameSpaceFlag());
}

void CustomizeDialog::saveSettings()
{
    if (mode == Ui::TitleMode) {
        Settings::setTitleFormat(0, ui.lineEdit->text());
        Settings::setTitleFormat(1, ui.lineEdit_2->text());
        Settings::setTagSpaceFlag(ui.checkBox->isChecked());
    } else {
        Settings::setFileNameFormat(0, ui.lineEdit->text());
        Settings::setFileNameFormat(1, ui.lineEdit_2->text());
        Settings::setNameSpaceFlag(ui.checkBox->isChecked());
    }
}

void CustomizeDialog::accepted()
{
    saveSettings();
}



#include "customizedialog.h"
#include "mainwindow.h"
#include "utility.h"

#include <QDir>
#include <QSettings>

#define SETTING_GROUP "CustomizeDialog"
#define DefaultTitle "%k_%Y_%M_%D"
#define DefaultTitle1 "%f"
#define DefaultTitle2 "%k_%Y_%M_%D"
#define DefaultFileName "%k_%Y_%M_%D"
#define DefaultFileName1 "%f_%Y_%M_%D"
#define DefaultFileName2 "%k_%Y-%M-%D"
#define DefaultFileName3 "%h"
#define DefaultFileName4 "%f"
#define DefaultFileName5 "%k_%h"
#define DefaultFileName6 "%y%M%D_%k%x"

typedef struct LineEdit {
	QLineEdit* lineEdit;
	QString titleKey;
	QString fileNameKey;
} LineEdit;

QStringList CustomizeDialog::courses = QStringList()
		<< QString::fromUtf8( "json" ) << QString::fromUtf8( "xml" );
QStringList CustomizeDialog::titleKeys = QStringList()
		<< "customized_title1" << "customized_title2";
QStringList CustomizeDialog::fileNameKeys = QStringList()
		<< "customized_file_name1" << "customized_file_name2";
QStringList CustomizeDialog::titleDefaults = QStringList()
		<< DefaultTitle1 << DefaultTitle;
QStringList CustomizeDialog::fileNameDefaults = QStringList()
		<< DefaultFileName << DefaultFileName;
				
void CustomizeDialog::formats( QString course, QString& titleFormat, QString& fileNameFormat ) {
	int index = courses.indexOf( course );
	if ( index >= 0 ) {
		QString path = MainWindow::ini_file_path;
		QSettings settings( path + INI_FILE, QSettings::IniFormat );
		settings.beginGroup( SETTING_GROUP );
		titleFormat = settings.value( titleKeys[index], titleDefaults[index] ).toString();
		fileNameFormat = settings.value( fileNameKeys[index], fileNameDefaults[index] ).toString();
		settings.endGroup();
	} else {
		titleFormat = titleDefaults[index]; 
		fileNameFormat = fileNameDefaults[index];
	}
}

CustomizeDialog::CustomizeDialog( Ui::DialogMode mode, QWidget *parent ) :
	QDialog(parent), mode(mode)
{
		ui.setupUi(this);

		this->setWindowTitle( mode == Ui::TitleMode ? QString::fromUtf8( "タイトルタグ設定" ) : QString::fromUtf8( "ファイル名設定" ) );
		settings( false );
		connect( this, SIGNAL( accepted() ), this, SLOT( accepted() ) );
		ui.radioButton_9->setChecked(true);
		ui.radioButton_19->setChecked(true);
}

void CustomizeDialog::settings( bool write ) {
 	if (ui.radioButton->isChecked()) ui.lineEdit->setText( DefaultFileName );
 	if (ui.radioButton_1->isChecked()) ui.lineEdit->setText( DefaultFileName1 );
  	if (ui.radioButton_2->isChecked()) ui.lineEdit->setText( DefaultFileName2 );
  	if (ui.radioButton_3->isChecked()) ui.lineEdit->setText( DefaultFileName3 );
  	if (ui.radioButton_4->isChecked()) ui.lineEdit->setText( DefaultFileName4 );
	if (ui.radioButton_5->isChecked()) ui.lineEdit->setText( DefaultFileName5 );
	if (ui.radioButton_6->isChecked()) ui.lineEdit->setText( DefaultFileName6 );
  	if (ui.radioButton_10->isChecked()) ui.lineEdit_2->setText( DefaultFileName );

	QLineEdit* lineEdits[] = {
		ui.lineEdit, ui.lineEdit_2,
		NULL
	};
	
	QString path =  MainWindow::ini_file_path;
	QSettings settings( path + INI_FILE, QSettings::IniFormat );
	settings.beginGroup( SETTING_GROUP );
	
	if ( !write ) {
		for ( int i = 0; lineEdits[i] != NULL; i++ ) {
			QString format = mode == Ui::TitleMode ?
							 settings.value( titleKeys[i], titleDefaults[i] ).toString() :
							 settings.value( fileNameKeys[i], fileNameDefaults[i] ).toString();
			lineEdits[i]->setText( format );
		}
		if ( mode == Ui::TitleMode ) {
			if( MainWindow::tag_space_flag ) ui.checkBox->setChecked(true); else ui.checkBox->setChecked(false); 
		} else {
			if( MainWindow::name_space_flag ) ui.checkBox->setChecked(true); else ui.checkBox->setChecked(false); 
		}
	} else {
		for ( int i = 0; lineEdits[i] != NULL; i++ ) {
			QString text = lineEdits[i]->text();
			if ( mode == Ui::TitleMode ) 
				settings.setValue( titleKeys[i], text.length() == 0 ? titleDefaults[i] : text );
			else 
				settings.setValue( fileNameKeys[i], text.length() == 0 ? fileNameDefaults[i] : text );
		}
		if ( mode == Ui::TitleMode ) {
			if( ui.checkBox->isChecked()) MainWindow::tag_space_flag = true; else MainWindow::tag_space_flag = false; 
		} else {
			if( ui.checkBox->isChecked()) MainWindow::name_space_flag = true; else MainWindow::name_space_flag = false; 
		}
	}
	settings.endGroup();
}

void CustomizeDialog::accepted() {
	if ( MainWindow::no_write_ini == "yes" )
	settings( true );
}
*/
