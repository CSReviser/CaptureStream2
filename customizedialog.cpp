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
    
    ui.radioButton_9->setChecked(true);
    ui.radioButton_19->setChecked(true);
}

/* ============================================================
 *  formats()
 *  course → settings.ini から titleFormat / fileNameFormat を取得
 * ============================================================ */
void CustomizeDialog::formats(QString course, QString& titleFormat, QString& fileNameFormat)
{
    int index = COURSES.indexOf(course);
    if (index < 0)
        index = 0;

    titleFormat    = Settings::getTitleFormat(index);
    fileNameFormat = Settings::getFileNameFormat(index);
}

/* ============================================================
 *  設定読み込み
 * ============================================================ */
void CustomizeDialog::loadSettings()
{
    ui.lineEdit->setText(
        mode == Ui::TitleMode
            ? Settings::getTitleFormat(0)
            : Settings::getFileNameFormat(0)
    );

    ui.lineEdit_2->setText(
        mode == Ui::TitleMode
            ? Settings::getTitleFormat(1)
            : Settings::getFileNameFormat(1)
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
        Settings::instance().setTitleFormatValue(0, ui.lineEdit->text());
        Settings::instance().setTitleFormatValue(1, ui.lineEdit_2->text());
        Settings::setTagSpaceFlag(ui.checkBox->isChecked());
    } else {
        Settings::instance().setFileNameFormatValue(0, ui.lineEdit->text());
        Settings::instance().setFileNameFormatValue(1, ui.lineEdit_2->text());
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

