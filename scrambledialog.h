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

#pragma once
#include <QVector>
#include <QDialog>
#include <QLineEdit>
#include "settings.h"
#include "constants.h"
#include "runtimeconfig.h"

namespace Ui {
class ScrambleDialog;
}

class ScrambleDialog : public QDialog {
    Q_OBJECT

public:
    explicit ScrambleDialog(Settings& settings, QWidget *parent = nullptr);
    ~ScrambleDialog();

private slots:
    void pushbutton();
    void pushbutton_2();

private:
    Ui::ScrambleDialog *ui;

    Settings& settings;
    RuntimeConfig* runtime;

    QVector<QLineEdit*> edits;

    QString scramble_set(QString opt, int index);
    QString updateOptional(int index, const QString &currentText);
    void updateLabels();
    void applyFlags();
    void accept() override;
    void applyOptionPresetLabels();
};

