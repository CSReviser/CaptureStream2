/*
	Copyright (C) 2009–2014 jakago
	Copyright (C) 2018–2025 CSReviser Team

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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
    class Settingsdialog;
}

class Settingsdialog : public QDialog {
    Q_OBJECT

public:
	explicit Settingsdialog( QString optional1, QString optional2, QString optional3, QString optional4, QWidget *parent = 0 );
    ~Settingsdialog();
//	explicit Settingsdialog( QString scramble, QWidget *parent = 0 );
//    ~Settingsdialog();
//	QString scramble();
	QString scramble1();
	QString scramble2();
	QString scramble3();
	QString scramble4();
	QString scramble_set( QString opt, int i );

	static QString optional1;
	static QString optional2;
	static QString optional3;
	static QString optional4;

	static QString opt1[];
	static QString opt2[];
	static QString opt3[];
	static QString opt4[];
	static QString opt5[];
	static QString opt6[];
	static QString opt7[];
	
	void inputMethodEvent(QInputMethodEvent *e);

	
signals: 
	void imPreeditChanged(QString const &s);
	void imCommitChanged(QString const &s);
	
public slots:
	void pushbutton();
private slots:
	void pushbutton_2();

private:
    Ui::Settingsdialog *ui;
    
	void settings( bool write );
};

#endif // SETTINGSDIALOG_H
