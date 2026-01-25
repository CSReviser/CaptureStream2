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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "settings.h"
#include "utility.h"
#include <QSettings>
#include <QMessageBox>

Settingsdialog::Settingsdialog( Settings& ini, QString o1, QString o2, QString o3, QString o4, QWidget *parent)
    : QDialog(parent), ui(new Ui::Settingsdialog),settings(ini)
{

    ui->setupUi(this);

    std::array<QLineEdit*, 4> edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };
    QStringList opts = { o1, o2, o3, o4 };
    for (int i = 0; i < Constants::SpecialCount; i++) {
	const auto &p = Constants::SpecPrograms[i];
	opts[i] = settings.specId[p.keyId];
	edits[i]->setText(opts[i]);
    }

//    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
//        edits[i]->setText(opts[i]);

    ui->radioButton_9->setChecked(true);

    ui->checkBox->setChecked(settings.checkBoxEnabled[Constants::KEY_MULTI_GUI]);
    ui->checkBox_1->setChecked(settings.checkBoxEnabled[Constants::KEY_KOZA_SEPARATION]);
    applyFlags();

}

Settingsdialog::~Settingsdialog()
{
    delete ui;
}

void Settingsdialog::applyFlags()
{
    settings.checkBoxEnabled[Constants::KEY_KOZA_SEPARATION] =  ui->checkBox_1->isChecked();
    settings.checkBoxEnabled[Constants::KEY_MULTI_GUI] = ui->checkBox->isChecked();
}

QString Settingsdialog::scramble_set(QString opt, int index)
{
    using namespace Constants;

    // ラジオボタン群
    std::array<QAbstractButton*, 7> radios = {
        ui->radioButton, ui->radioButton_1, ui->radioButton_2,
        ui->radioButton_3, ui->radioButton_4, ui->radioButton_5,
        ui->radioButton_6
    };

    // チェックされているプリセットを適用
    for (int j = 0; j < PRESETS.size() && j < radios.size(); ++j) {
        if (radios[j]->isChecked()) {
            opt = PRESETS[j][index];
        }
    }

    if (ui->radioButton_6->isChecked()) {
        QStringList opt1 = settings.specials;
        if ( !(opt1[index].isNull()  || opt1[index].isEmpty()))
        opt = opt1[index];
    }

    QLineEdit* edit = nullptr;
    switch (index) {
    case 0: edit = ui->edit1; break;
    case 1: edit = ui->edit2; break;
    case 2: edit = ui->edit3; break;
    case 3: edit = ui->edit4; break;
    }

    if (!ui->radioButton_9->isChecked())
        edit->setText(opt);
    else {
        // name_map → id_map の変換
        if (MainWindow::name_map.contains(edit->text()))
            opt = MainWindow::name_map[edit->text()];

        if (Utility::getProgram_name(edit->text()).isEmpty())
            edit->setText(opt);
    }

    applyFlags();
    return opt;
}

//QString Settingsdialog::scramble1() { return scramble_set(ui->edit1->text(), 0); }
//QString Settingsdialog::scramble2() { return scramble_set(ui->edit2->text(), 1); }
//QString Settingsdialog::scramble3() { return scramble_set(ui->edit3->text(), 2); }
//QString Settingsdialog::scramble4() { return scramble_set(ui->edit4->text(), 3); }

QString Settingsdialog::scramble1()
{
    return updateSpecial(0, ui->edit1->text());
}

QString Settingsdialog::scramble2()
{
    return updateSpecial(1, ui->edit2->text());
}

QString Settingsdialog::scramble3()
{
    return updateSpecial(2, ui->edit3->text());
}

QString Settingsdialog::scramble4()
{
    return updateSpecial(3, ui->edit4->text());
}


void Settingsdialog::updateLabels()
{
    std::array<QLineEdit*, Constants::PRESET_SIZE > edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };
    std::array<QLabel*, Constants::PRESET_SIZE > labels = { ui->label_2, ui->label_3, ui->label_4, ui->label_5 };

    for (int i = 0; i < 4; ++i)
        labels[i]->setText(Utility::getProgram_name(edits[i]->text()));
}

void Settingsdialog::pushbutton()
{
    std::array<QLineEdit*, Constants::PRESET_SIZE > edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };

    for (int i = 0; i < Constants::PRESET_SIZE; ++i) {
        QString opt = edits[i]->text();

	QStringList title = MainWindow::name_map.keys();
	QStringList id = MainWindow::name_map.values();	

        // name_map → id_map の変換
//        if (MainWindow::name_map.contains(opt))
//            opt = MainWindow::name_map[opt];
//        else if (MainWindow::id_map.contains(opt))
//            opt = MainWindow::id_map[opt];

		if( !(MainWindow::id_map.contains(opt))){
			for (int j = 0; j < title.count(); ++j){
				if( title[j].contains(opt, Qt::CaseInsensitive)) {
					opt = id[j];
					break;
				}
			}
		}
		if( !(MainWindow::id_map.contains(opt))){
			for (int j = 0; j < id.count(); ++j){
				if( id[j].contains(opt, Qt::CaseInsensitive )) {
					opt = id[j];
					break;
				}
			}
		}

        opt = scramble_set(opt, i);
        edits[i]->setText(opt);
    }

    ui->radioButton_9->setChecked(true);
    updateLabels();
}


void Settingsdialog::pushbutton_2()
{
    std::array<QLineEdit*, Constants::PRESET_SIZE > edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };
    QStringList titles;

    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        titles << MainWindow::id_map.value(edits[i]->text());

    QString msg =
        QString::fromUtf8("下記内容で上書きします。保存しますか？\n")
        + "１：" + titles[0] + "\n"
        + "２：" + titles[1] + "\n"
        + "３：" + titles[2] + "\n"
        + "４：" + titles[3];

    if (QMessageBox::question(this, tr("特別番組設定保存"), msg) == QMessageBox::Yes) {
        for (int i = 0; i < Constants::PRESET_SIZE; ++i)
            settings.specials[i] = edits[i]->text();
    }
}

QString Settingsdialog::updateSpecial(int index, const QString &currentText)
{
    using namespace Constants;

    // scramble_set により最終的な ID を決定
    QString newValue = scramble_set(currentText, index);

    // 対応する keyId を取得
    const auto &p = SpecPrograms[index];
    QString oldValue = settings.specId[p.keyId];

    // 変更なし → 何もせず返す
    if (oldValue == newValue)
        return newValue;

    // 変更あり → Settings に書き戻し
    settings.specId[p.keyId] = newValue;

    // bool をクリア（例：特別番組変更時は無効化）
    settings.checkBoxEnabled[KEY_KOZA_SEPARATION] = false;
    settings.checkBoxEnabled[KEY_MULTI_GUI] = false;

    // title の更新（id_map → 番組名）
    settings.specTitle[p.keyId] = Utility::getProgram_name(newValue);

    return newValue;
}


QString Settingsdialog::scramble1() { return updateSpecial(0, ui->edit1->text()); }
QString Settingsdialog::scramble2() { return updateSpecial(1, ui->edit2->text()); }
QString Settingsdialog::scramble3() { return updateSpecial(2, ui->edit3->text()); }
QString Settingsdialog::scramble4() { return updateSpecial(3, ui->edit4->text()); }


QString Settingsdialog::updateSpecial(int index, const QString &currentText)
{
    using namespace Constants;

    // scramble_set により最終的な ID を決定
    QString newValue = scramble_set(currentText, index);

    // 対応する keyId を取得
    const auto &p = SpecPrograms[index];
    QString oldValue = settings.specId[p.keyId];

    // 変更なし → 何もせず返す
    if (oldValue == newValue)
        return newValue;

    // 変更あり → Settings に書き戻し
    settings.specId[p.keyId] = newValue;

    // bool をクリア（特別番組変更時は無効化）
    settings.checkBoxEnabled[KEY_KOZA_SEPARATION] = false;
    settings.checkBoxEnabled[KEY_MULTI_GUI] = false;

    // title の更新（id_map → 番組名）
    settings.specTitle[p.keyId] = Utility::getProgram_name(newValue);

    return newValue;
}

