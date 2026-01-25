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

#pragma once
#include <array>
#include <QDialog>
#include "settings.h"
#include "constants.h"

class Settings;

namespace Ui {
    class Settingsdialog;
}

class Settingsdialog : public QDialog {
    Q_OBJECT

public:
    explicit Settingsdialog( Settings& settings, QString opt1, QString opt2, QString opt3, QString opt4, QWidget *parent = nullptr);
    ~Settingsdialog();
	QString scramble1();
	QString scramble2();
	QString scramble3();
	QString scramble4();


signals: 
	void imPreeditChanged(QString const &s);
	void imCommitChanged(QString const &s);
	
public slots:
	void pushbutton();
private slots:
	void pushbutton_2();

private:
    Ui::Settingsdialog *ui;
    
    Settings& settings;
    QString scramble_set(QString opt, int index);
    QString updateSpecial(int index, const QString &currentText);
    void applyFlags();
    void updateLabels();

};


