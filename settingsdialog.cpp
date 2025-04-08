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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "urldownloader.h"
#include "utility.h"
#include <QSettings>
#include "downloadthread.h"
#include <QCompleter>
#include <QMessageBox>
//#ifdef QT5
//#include <QRegExp>
//#endif
//#ifdef QT6
#include <QRegularExpression>
//#endif
#define SETTING_GROUP "Settingsdialog"
QString Settingsdialog::optional1;
QString Settingsdialog::optional2;
QString Settingsdialog::optional3;
QString Settingsdialog::optional4;

QString Settingsdialog::opt1[] = {
		"6LPPKP6W8Q_01", //やさしい日本語
		"WKMNWGMN6R_01", //アラビア語講座
		"GLZQ4M519X_01", //Asian View
		"4MY6Q8XP88_01"  //Living in Japan
};
QString Settingsdialog::opt2[] = {
		"YRLK72JZ7Q_x1", //まいにちロシア語 入門編
		"YRLK72JZ7Q_y1", //まいにちロシア語 応用編
		"983PKQPYN7_01", //まいにち中国語
		"LR47WW9K14_01"  //まいにちハングル講座
};
QString Settingsdialog::opt3[] = {
		"YRLK72JZ7Q_x1", //まいにちロシア語 入門編
		"YRLK72JZ7Q_y1", //まいにちロシア語 応用編
		"WKMNWGMN6R_01", //アラビア語講座
		"N13V9K157Y_01"  //ポルトガル語ステップアップ
};
QString Settingsdialog::opt4[] = {
		"983PKQPYN7_01", //まいにち中国語
		"LR47WW9K14_01", //まいにちハングル講座
		"WKMNWGMN6R_01", //アラビア語講座
		"N13V9K157Y_01"  //ポルトガル語ステップアップ
};
QString Settingsdialog::opt5[] = {
		"GLZQ4M519X_01", //Asian View
		"X7R2P2PW5P_02", //ニュース解説
		"L6ZQ2NX1NL_01", //NHKジャーナル
		"34PY344RPJ_01"  //NHKやさしいことばニュース
};
QString Settingsdialog::opt6[] = {
		"X4X6N1XG8Z_01", //青春アドベンチャー
		"D85RZVGX7W_01", //新日曜名作座
		"YR96XR51MZ_01", //朗読の世界
		"M65G6QLKMY_01"  //FMシアター
};

QString Settingsdialog::opt7[] = {
		"R5XR783QK3_01", //おしゃべりな古典教室
		"X78J5NKWM9_01", //こころをよむ
		"5L3859P515_01", //古典講読
		"JWQ88ZVWQK_01"  //宗教の時間
};


Settingsdialog::Settingsdialog( QString optional1, QString optional2, QString optional3, QString optional4, QWidget *parent )
		: QDialog(parent), ui(new Ui::Settingsdialog) {
    	ui->setupUi(this);
    	setAttribute(Qt::WA_InputMethodEnabled);
 
	if( MainWindow::koza_separation_flag ) ui->checkBox_1->setChecked(true);
	if( MainWindow::multi_gui_flag ) ui->checkBox->setChecked(true);
	QString optional[] = { optional1, optional2, optional3, optional4 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };
	QStringList key = MainWindow::name_map.keys();
	for ( int i = 0 ; i < 4 ; ++i ) Button2[i]->setText( optional[i] );
	ui->radioButton_9->setChecked(true);
	if ( MainWindow::koza_separation_flag ) ui->checkBox_1->setChecked(true);
	if ( ui->checkBox_1->isChecked() ) { MainWindow::koza_separation_flag = true; ui->checkBox_1->setChecked(true);} else { MainWindow::koza_separation_flag = false; ui->checkBox_1->setChecked(false); }
	if ( MainWindow::multi_gui_flag ) ui->checkBox->setChecked(true);
	if ( ui->checkBox->isChecked() ) { MainWindow::multi_gui_flag = true; ui->checkBox->setChecked(true);} else { MainWindow::multi_gui_flag = false; ui->checkBox->setChecked(false); }
}

Settingsdialog::~Settingsdialog() {
    delete ui;
}

QString Settingsdialog::scramble_set( QString opt, int i ) {
	QString opt_tmp = opt;
	QString optional[] = { optional1, optional2, optional3, optional4 };
	QString opt_set[] = { opt1[i], opt2[i], opt3[i], opt4[i], opt5[i], opt6[i], opt7[i]  };
	QAbstractButton*  Button[] = { ui->radioButton, ui->radioButton_1, ui->radioButton_2, ui->radioButton_3, ui->radioButton_4, ui->radioButton_5, ui->radioButton_6,NULL };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, NULL };
	for ( int j = 0 ; Button[j] != NULL ; j++ ) 
		if (Button[j]->isChecked())	opt = opt_set[j];
	if (!(ui->radioButton_9->isChecked())) Button2[i]->setText( opt );
	if ( ui->radioButton_9->isChecked() && (MainWindow::name_map.contains( Button2[i]->text() )) ) { opt = MainWindow::name_map[ Button2[i]->text() ]; Button2[i]->setText( opt ); }
	if ( ui->radioButton_9->isChecked() && Utility::getProgram_name( Button2[i]->text() ) == "" ) { Button2[i]->setText( opt ); }
	if ( ui->checkBox_1->isChecked() ) { MainWindow::koza_separation_flag = true; ui->checkBox_1->setChecked(true);} else { MainWindow::koza_separation_flag = false; ui->checkBox_1->setChecked(false); }
	if ( ui->checkBox->isChecked() ) { MainWindow::multi_gui_flag = true; ui->checkBox->setChecked(true);} else { MainWindow::multi_gui_flag = false; ui->checkBox->setChecked(false); }
	return opt;
}
QString Settingsdialog::scramble1() {
	optional1 = scramble_set( optional1, 0);
	return ui->edit1->text();
}
QString Settingsdialog::scramble2() {
	optional2 = scramble_set( optional2, 1 );
	return ui->edit2->text();
}
QString Settingsdialog::scramble3() {
	optional3 = scramble_set( optional3, 2 );
	return ui->edit3->text();
}
QString Settingsdialog::scramble4() {
	optional4 = scramble_set( optional4, 3 );
	return ui->edit4->text();
}

void Settingsdialog::pushbutton() {
	QString optional[] = { optional1, optional2, optional3, optional4 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, NULL };
	QLabel*  Label[] = { ui->label_2, ui->label_3, ui->label_4, ui->label_5, NULL };

	Settingsdialog::settings( false );

	QStringList title = MainWindow::name_map.keys();
	QStringList id = MainWindow::name_map.values();	
	for ( int i = 0 ; Button2[i] != NULL ; i++ ) {
		optional[i] = Button2[i]->text();

		if( !(MainWindow::id_map.contains(optional[i]))){
			for (int j = 0; j < title.count(); ++j){
				if( title[j].contains(optional[i], Qt::CaseInsensitive)) {
					optional[i] = id[j];
					break;
				}
			}
		}
		if( !(MainWindow::id_map.contains(optional[i]))){
			for (int j = 0; j < id.count(); ++j){
				if( id[j].contains(optional[i], Qt::CaseInsensitive )) {
					optional[i] = id[j];
					break;
				}
			}
		}
	
		optional[i]  = scramble_set( optional[i], i );
		Button2[i]->setText( optional[i]  );
		Label[i]->setText( Utility::getProgram_name( optional[i] ));
	}
	ui->radioButton_9->setChecked(true);
	title.clear();
	id.clear();
}

void Settingsdialog::pushbutton_2() {
	QString optional[] = { optional1, optional2, optional3, optional4 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, NULL };
	QString title[4];
	for ( int i = 0 ; Button2[i] != NULL ; i++ ) {
		optional[i] = Button2[i]->text();
		if ( MainWindow::id_map.contains( optional[i] ) ) title[i] = MainWindow::id_map.value( optional[i] );
	}
	QString message = QString::fromUtf8( "下記内容で上書きします。保存しますか？\n１：" ) + title[0] + QString::fromUtf8( "\n２：" ) + title[1] + QString::fromUtf8( "\n３：" ) + title[2] + QString::fromUtf8( "\n４：" ) + title[3];
	int res = QMessageBox::question(this, tr("特別番組設定保存"), message );
	if (res == QMessageBox::Yes) {
		QSettings settings( MainWindow::ini_file_path + INI_FILE, QSettings::IniFormat );
		settings.beginGroup( SETTING_GROUP );
		
		Settingsdialog::settings( true );
	}
}

void Settingsdialog::settings( bool write ) {
	QSettings settings( MainWindow::ini_file_path + INI_FILE, QSettings::IniFormat );
	settings.beginGroup( SETTING_GROUP );
	QString optional[] = { "special1", "special2", "special3", "special4" };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, NULL };
	
	if ( !write ) {
		for ( int i = 0 ; Button2[i] != NULL ; i++ ) {
			opt7[i] = settings.value( optional[i], opt7[i] ).toString();
		}
	} else {
		for ( int i = 0 ; Button2[i] != NULL ; i++ ) {
			settings.setValue( optional[i], Button2[i]->text() );
			opt7[i] = Button2[i]->text();
		}

	}
	settings.endGroup();
}

void Settingsdialog::inputMethodEvent(QInputMethodEvent *e) 
{
	QString preedit = e->preeditString();
	QString commit = e->commitString();
	emit imPreeditChanged(preedit);
	emit imCommitChanged(commit);
}

