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

#include "appearancedialog.h"
#include "ui_appearancedialog.h"

#include "settings.h"
#include "constants.h"

#include <QComboBox>

AppearanceDialog::AppearanceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppearanceDialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("外観設定"));

    initializeThemeList();
    loadSettings();

    connect(ui->buttonBox,
            &QDialogButtonBox::accepted,
            this,
            &AppearanceDialog::accept);

    connect(ui->buttonBox,
            &QDialogButtonBox::rejected,
            this,
            &AppearanceDialog::reject);
}

AppearanceDialog::~AppearanceDialog()
{
    delete ui;
}

// ===== テーマ一覧 =====
void AppearanceDialog::initializeThemeList()
{
    ui->comboBoxTheme->clear();

    for (int i = 0; i < Constants::ThemeCount; ++i) {
        const auto &theme = Constants::Themes[i];

        ui->comboBoxTheme->addItem(
            QString::fromUtf8(theme.name),
            QString::fromUtf8(theme.id)
        );
    }
}

// ===== 設定読み込み =====
void AppearanceDialog::loadSettings()
{
    const auto &settings = Settings::instance();

    const int index = ui->comboBoxTheme->findData(
        settings.theme()
    );

    if (index >= 0) {
        ui->comboBoxTheme->setCurrentIndex(index);
    }

    ui->checkBoxExternalStyleSheet->setChecked(
        settings.useExternalStyleSheet()
    );

    ui->checkBoxExternalIcons->setChecked(
        settings.useExternalIcons()
    );
}

// ===== 設定反映 =====
void AppearanceDialog::applySettings()
{
    auto &settings = Settings::instance();

    settings.setTheme(
        ui->comboBoxTheme->currentData().toString()
    );

    settings.setUseExternalStyleSheet(
        ui->checkBoxExternalStyleSheet->isChecked()
    );

    settings.setUseExternalIcons(
        ui->checkBoxExternalIcons->isChecked()
    );
}

// ===== OK =====
void AppearanceDialog::accept()
{
    applySettings();

    Settings::instance().save();

    emit appearanceChanged();

    QDialog::accept();
}

