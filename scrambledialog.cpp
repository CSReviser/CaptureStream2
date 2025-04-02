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

#include "scrambledialog.h"
#include "ui_scrambledialog.h"
#include "mainwindow.h"
#include "urldownloader.h"
#include "utility.h"
#include "downloadthread.h"
#include <QSettings>
#include <QCompleter>
#include <QMessageBox>
//#ifdef QT5
//#include <QRegExp>
//#endif
//#ifdef QT6
#include <QRegularExpression>
//#endif
#define SETTING_GROUP "ScrambleDialog"
QString ScrambleDialog::optional1;
QString ScrambleDialog::optional2;
QString ScrambleDialog::optional3;
QString ScrambleDialog::optional4;
QString ScrambleDialog::optional5;
QString ScrambleDialog::optional6;
QString ScrambleDialog::optional7;
QString ScrambleDialog::optional8;

QString ScrambleDialog::opt1[] = {
		"XQ487ZM61K_x1", //まいにちフランス語 入門編
		"XQ487ZM61K_y1", //まいにちフランス語 応用編
		"N8PZRZ9WQY_x1", //まいにちドイツ語 入門編／初級編
		"N8PZRZ9WQY_y1", //まいにちドイツ語 応用編
		"LJWZP7XVMX_x1", //まいにちイタリア語 入門編
		"LJWZP7XVMX_y1", //まいにちイタリア語 応用編
		"NRZWXVGQ19_x1", //まいにちスペイン語 入門編／初級編
		"NRZWXVGQ19_y1"  //まいにちスペイン語 中級編／応用編
};
QString ScrambleDialog::opt2[] = {
		"983PKQPYN7_01", //まいにち中国語
		"GLZQ4M519X_01", //Asian View
		"LR47WW9K14_01", //まいにちハングル講座
		"6LPPKP6W8Q_01", //やさしい日本語
		"YRLK72JZ7Q_x1", //まいにちロシア語 入門編
		"YRLK72JZ7Q_y1", //まいにちロシア語 応用編
		"WKMNWGMN6R_01", //アラビア語講座
		"N13V9K157Y_01"  //ポルトガル語
};
QString ScrambleDialog::opt3[] = {
		"XQ487ZM61K_x1", //まいにちフランス語 入門編
		"N8PZRZ9WQY_x1", //まいにちドイツ語 入門編／初級編
		"LJWZP7XVMX_x1", //まいにちイタリア語 入門編
		"NRZWXVGQ19_x1", //まいにちスペイン語 入門編／初級編
		"YRLK72JZ7Q_x1", //まいにちロシア語 入門編
		"N13V9K157Y_01", //ポルトガル語
		"983PKQPYN7_01", //まいにち中国語
		"LR47WW9K14_01"  //まいにちハングル講座
};
QString ScrambleDialog::opt4[] = {
		"XQ487ZM61K_y1", //まいにちフランス語 応用編
		"N8PZRZ9WQY_y1", //まいにちドイツ語 応用編
		"LJWZP7XVMX_y1", //まいにちイタリア語 応用編
		"NRZWXVGQ19_y1", //まいにちスペイン語 中級編／応用編
		"YRLK72JZ7Q_y1", //まいにちロシア語 応用編
		"N13V9K157Y_01", //ポルトガル語
		"983PKQPYN7_01", //まいにち中国語
		"LR47WW9K14_01"  //まいにちハングル講座
};
QString ScrambleDialog::opt5[] = {
		"XQ487ZM61K_01", //まいにちフランス語
		"N8PZRZ9WQY_01", //まいにちドイツ語
		"LJWZP7XVMX_01", //まいにちイタリア語
		"NRZWXVGQ19_01", //まいにちスペイン語
		"YRLK72JZ7Q_01", //まいにちロシア語
		"N13V9K157Y_01", //ポルトガル語
		"983PKQPYN7_01", //まいにち中国語
		"LR47WW9K14_01"  //まいにちハングル講座
};
QString ScrambleDialog::opt6[] = {
		"4MY6Q8XP88_01", //Living in Japan
		"GLZQ4M519X_01", //Asian View
		"6LPPKP6W8Q_01", //やさしい日本語
		"D6RM27PGVM_01", //Learn Japanese from the News
		"X4X6N1XG8Z_01", //青春アドベンチャー
		"D85RZVGX7W_01", //新日曜名作座
		"LRK2VXPK5X_01", //朗読
		"M65G6QLKMY_01"  //FMシアター
};

QString ScrambleDialog::opt7[] = {
		"R5XR783QK3_01", //おしゃべりな古典教室
		"DK83KZ8848_01", //カルチャーラジオ 文学の世界
		"5L3859P515_01", //古典講読
		"XKR4W8GY15_01", //カルチャーラジオ 科学と人間
		"4K58V66ZGQ_01", //梶裕貴のラジオ劇場
		"X78J5NKWM9_01", //こころをよむ
		"MVYJ6PRZMX_01", //アナウンサー百年百話
		"JWQ88ZVWQK_01"  //宗教の時間
};


ScrambleDialog::ScrambleDialog( QString optional1, QString optional2, QString optional3, QString optional4, QString optional5, QString optional6, QString optional7, QString optional8, QWidget *parent )
//ScrambleDialog::ScrambleDialog( QString scramble, QWidget *parent )
		: QDialog(parent), ui(new Ui::ScrambleDialog) {
    	ui->setupUi(this);
    	setAttribute(Qt::WA_InputMethodEnabled);
 
//	connect(ui->edit1, &ScrambleDialog::imPreeditChanged, [&](QString const &s){
//		ui->edit1->setText(s);
//	});

//	connect(ui->edit1, &ScrambleDialog::imCommitChanged, [&](QString const &s){
//		ui->edit1->setText(s);
//	});   
	if( MainWindow::koza_separation_flag ) ui->checkBox_1->setChecked(true);
	QString optional[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8 };
	QStringList key = MainWindow::name_map.keys();
//	for ( int i = 0 ; i < 8 ; i++ ) QCompleter *comp = new QCompleter(key, Button2[i])
//		Button2[i]->setCompleter(comp);
//	QLineEdit *edit1 = new QLineEdit(this);
//	QCompleter *comp = new QCompleter(key, this);
//	ui->edit1->setCompleter(comp);
//	edit1->show();
	for ( int i = 0 ; i < 8 ; ++i ) Button2[i]->setText( optional[i] );
	ui->radioButton_9->setChecked(true);
	if ( MainWindow::koza_separation_flag ) ui->checkBox_1->setChecked(true);
	if ( ui->checkBox_1->isChecked() ) { MainWindow::koza_separation_flag = true; ui->checkBox_1->setChecked(true);} else { MainWindow::koza_separation_flag = false; ui->checkBox_1->setChecked(false); }
}

ScrambleDialog::~ScrambleDialog() {
    delete ui;
}

QString ScrambleDialog::scramble_set( QString opt, int i ) {
	QString opt_tmp = opt;
	QString optional[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 };
	QString opt_set[] = { opt1[i], opt2[i], opt3[i], opt4[i], opt5[i], opt6[i], opt7[i]  };
	QAbstractButton*  Button[] = { ui->radioButton, ui->radioButton_1, ui->radioButton_2, ui->radioButton_3, ui->radioButton_4, ui->radioButton_5, ui->radioButton_6,NULL };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8, NULL };
	for ( int j = 0 ; Button[j] != NULL ; j++ ) 
		if (Button[j]->isChecked())	opt = opt_set[j];
	if (!(ui->radioButton_9->isChecked())) Button2[i]->setText( opt );
	if ( ui->radioButton_9->isChecked() && (MainWindow::name_map.contains( Button2[i]->text() )) ) { opt = MainWindow::name_map[ Button2[i]->text() ]; Button2[i]->setText( opt ); }
	if ( ui->radioButton_9->isChecked() && Utility::getProgram_name( Button2[i]->text() ) == "" ) { Button2[i]->setText( opt ); }
	if ( ui->checkBox_1->isChecked() ) { MainWindow::koza_separation_flag = true; ui->checkBox_1->setChecked(true);} else { MainWindow::koza_separation_flag = false; ui->checkBox_1->setChecked(false); }
//	if ( ui->checkBox->isChecked() ) { MainWindow::id_flag = true; ui->checkBox->setChecked(true);} else { MainWindow::id_flag = false; ui->checkBox->setChecked(false); }
	return opt;
}
QString ScrambleDialog::scramble1() {
	optional1 = scramble_set( optional1, 0);
	return ui->edit1->text();
}
QString ScrambleDialog::scramble2() {
	optional2 = scramble_set( optional2, 1 );
	return ui->edit2->text();
}
QString ScrambleDialog::scramble3() {
	optional3 = scramble_set( optional3, 2 );
	return ui->edit3->text();
}
QString ScrambleDialog::scramble4() {
	optional4 = scramble_set( optional4, 3 );
	return ui->edit4->text();
}
QString ScrambleDialog::scramble5() {
	optional5 = scramble_set( optional5, 4 );
	return ui->edit5->text();
}
QString ScrambleDialog::scramble6() {
	optional6 = scramble_set( optional6, 5 );
	return ui->edit6->text();
}
QString ScrambleDialog::scramble7() {
	optional7 = scramble_set( optional7, 6 );
	return ui->edit7->text();
}
QString ScrambleDialog::scramble8() {
	optional8 = scramble_set( optional8, 7 );
	return ui->edit8->text();
}

void ScrambleDialog::pushbutton() {
	QString optional[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8, NULL };
	QLabel*  Label[] = { ui->label_2, ui->label_3, ui->label_4, ui->label_5, ui->label_6, ui->label_7, ui->label_8, ui->label_9, NULL };

	ScrambleDialog::settings( false );
	
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

void ScrambleDialog::pushbutton_2() {
	QString optional[] = { optional1, optional2, optional3, optional4, optional5, optional6, optional7, optional8 };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8, NULL };
	QString title[8];
	for ( int i = 0 ; Button2[i] != NULL ; i++ ) {
		optional[i] = Button2[i]->text();
		if ( MainWindow::id_map.contains( optional[i] ) ) title[i] = MainWindow::id_map.value( optional[i] );
	}
	QString message = QString::fromUtf8( "下記内容で上書きします。保存しますか？\n１：" ) 
		+ title[0] + QString::fromUtf8( "\n２：" ) 
		+ title[1] + QString::fromUtf8( "\n３：" ) 
		+ title[2] + QString::fromUtf8( "\n４：" ) 
		+ title[3] + QString::fromUtf8( "\n５：" ) 
		+ title[4] + QString::fromUtf8( "\n６：" ) 
		+ title[5] + QString::fromUtf8( "\n７：" ) 
		+ title[6] + QString::fromUtf8( "\n８：" )
		+ title[7];
		
	int res = QMessageBox::question(this, tr("任意番組設定保存"), message );
	if (res == QMessageBox::Yes) {
		QSettings settings( MainWindow::ini_file_path + INI_FILE, QSettings::IniFormat );
		settings.beginGroup( SETTING_GROUP );
		
		ScrambleDialog::settings( true );
	}
}

void ScrambleDialog::settings( bool write ) {
	QSettings settings( MainWindow::ini_file_path + INI_FILE, QSettings::IniFormat );
	settings.beginGroup( SETTING_GROUP );
	QString optional[] = { "optional1", "optional2", "optional3", "optional4", "optional5", "optional6", "optional7", "optional8" };
	QLineEdit*  Button2[] = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8, NULL };
	
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

void ScrambleDialog::inputMethodEvent(QInputMethodEvent *e) 
{
	QString preedit = e->preeditString();
	QString commit = e->commitString();
	emit imPreeditChanged(preedit);
	emit imCommitChanged(commit);
}
