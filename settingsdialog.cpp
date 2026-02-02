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
#include "settings.h"
#include "utility.h"
#include <QMessageBox>

Settingsdialog::Settingsdialog(Settings& ini, RuntimeConfig* r, QWidget *parent)
    : QDialog(parent), ui(new Ui::Settingsdialog), settings(ini), runtime(r)
{
    ui->setupUi(this);

    edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };

    // ===== 特番（SpecPrograms）を Settings から復元 =====
    for (int i = 0; i < Constants::PRESET_SIZE; i++) {
        const auto &p = Constants::SpecPrograms[i];
        edits[i]->setText(settings.ids[p.keyId]);
    }

    ui->radioButton_9->setChecked(true);

    // ===== チェックボックスフラグ =====
//    ui->checkBox->setChecked(settings.enabled[Constants::KEY_MULTI_GUI]);
//    ui->checkBox_1->setChecked(settings.enabled[Constants::KEY_KOZA_SEPARATION]);
}

Settingsdialog::~Settingsdialog()
{
    delete ui;
}

void Settingsdialog::applyFlags()
{
//    settings.enabled[Constants::KEY_KOZA_SEPARATION] = ui->checkBox_1->isChecked();
//    settings.enabled[Constants::KEY_MULTI_GUI] = ui->checkBox->isChecked();
}

QString Settingsdialog::scramble_set(QString opt, int index)
{
    using namespace Constants;

    std::array<QAbstractButton*, 7> radios = {
        ui->radioButton, ui->radioButton_1, ui->radioButton_2,
        ui->radioButton_3, ui->radioButton_4, ui->radioButton_5,
        ui->radioButton_6
    };

    // プリセット適用
    for (int j = 0; j < PRESETS.size() && j < radios.size(); ++j) {
        if (radios[j]->isChecked()) {
            opt = PRESETS[j][index];
        }
    }

    // ユーザープリセット
    if (ui->radioButton_6->isChecked()) {
        auto opt1 = settings.specials;
        if (!opt1[index].isEmpty())
            opt = opt1[index];
    }

    QLineEdit* edit = edits[index];

    if (!ui->radioButton_9->isChecked()) {
        edit->setText(opt);
    } else {
        // name_map → id_map
        if (runtime->name_map.contains(edit->text()))
            opt = runtime->name_map[edit->text()];

        if (Utility::getProgram_name(edit->text()).isEmpty())
            edit->setText(opt);
    }

    return opt;
}

void Settingsdialog::accept()
{
    for (int i = 0; i < Constants::PRESET_SIZE; i++)
        updateSpecial(i, edits[i]->text());

    applyFlags();
    QDialog::accept();
}

void Settingsdialog::updateLabels()
{
    std::array<QLabel*, Constants::PRESET_SIZE> labels =
        { ui->label_2, ui->label_3, ui->label_4, ui->label_5 };

    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        labels[i]->setText(Utility::getProgram_name(edits[i]->text()));
}

void Settingsdialog::pushbutton()
{
    const QStringList titles = runtime->name_map.keys();
    const QStringList ids    = runtime->name_map.values();

    for (int i = 0; i < Constants::PRESET_SIZE; ++i) {

        QString opt = edits[i]->text();

        if (!runtime->id_map.contains(opt)) {
            // タイトル部分一致
            for (int j = 0; j < titles.count(); ++j) {
                if (titles[j].contains(opt, Qt::CaseInsensitive)) {
                    opt = ids[j];
                    break;
                }
            }

            // ID 部分一致
            if (!runtime->id_map.contains(opt)) {
                for (int j = 0; j < ids.count(); ++j) {
                    if (ids[j].contains(opt, Qt::CaseInsensitive)) {
                        opt = ids[j];
                        break;
                    }
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
    QStringList titles;

    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        titles << runtime->id_map.value(edits[i]->text());

    QString msg =
        QStringLiteral("下記内容で上書きします。保存しますか？\n") +
        "１：" + titles[0] + "\n" +
        "２：" + titles[1] + "\n" +
        "３：" + titles[2] + "\n" +
        "４：" + titles[3];

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
    QString oldValue = settings.ids[p.keyId];

    // 変更なし → 何もせず返す
    if (oldValue == newValue)
        return newValue;

    // ID 更新
    settings.ids[p.keyId] = newValue;

    // enabled を false にする
    settings.enabled[p.keyEnabled] = false;

    // タイトル更新（id_map → 番組名）
    if (!runtime->id_map.contains(newValue))
        settings.titles[p.keyTitle] = Utility::getProgram_name(newValue);
    else
        settings.titles[p.keyTitle] = runtime->id_map[newValue];

    settings.save();   // INI に書き込み
    return newValue;
}


/*

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "mainwindow.h"
#include "settings.h"
#include "utility.h"
#include <QSettings>
#include <QMessageBox>

//Settingsdialog::Settingsdialog( Settings& ini, RuntimeConfig* r, QString o1, QString o2, QString o3, QString o4, QWidget *parent)
Settingsdialog::Settingsdialog( Settings& ini, RuntimeConfig* r, QWidget *parent)
    : QDialog(parent), ui(new Ui::Settingsdialog),settings(ini), runtime(r)
{

    ui->setupUi(this);

    edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4 };
//    QStringList opts = { o1, o2, o3, o4 };
    QStringList opts = { "", "", "", "" };
    for (int i = 0; i < Constants::PRESET_SIZE; i++) {
	const auto &p = Constants::SpecPrograms[i];
	opts[i] = settings.specId[p.keyId];
	edits[i]->setText(opts[i]);
    }

    ui->radioButton_9->setChecked(true);

    ui->checkBox->setChecked(settings.checkBoxEnabled[Constants::KEY_MULTI_GUI]);
    ui->checkBox_1->setChecked(settings.checkBoxEnabled[Constants::KEY_KOZA_SEPARATION]);
//    applyFlags();

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
        auto opt1 = settings.specials;
        if ( !(opt1[index].isNull()  || opt1[index].isEmpty()))
        opt = opt1[index];
    }

    QLineEdit* edit = edits[index];

    if (!ui->radioButton_9->isChecked())
        edit->setText(opt);
    else {
        // name_map → id_map の変換
        if (runtime->name_map.contains(edit->text()))
            opt = runtime->name_map[edit->text()];

        if (Utility::getProgram_name(edit->text()).isEmpty())
            edit->setText(opt);
    }

//    applyFlags();
    return opt;
}

void Settingsdialog::accept()
{
    // OK ボタンで確定した内容を Settings に保存する
    for (int i = 0; i < Constants::PRESET_SIZE; i++) {
	updateSpecial(i, edits[i]->text());
    }
    applyFlags();
    // ★ 最後に必ず親クラスの accept() を呼ぶ
    QDialog::accept();
}

QString Settingsdialog::scramble1() { return updateSpecial(0, ui->edit1->text()); }
QString Settingsdialog::scramble2() { return updateSpecial(1, ui->edit2->text()); }
QString Settingsdialog::scramble3() { return updateSpecial(2, ui->edit3->text()); }
QString Settingsdialog::scramble4() { return updateSpecial(3, ui->edit4->text()); }

void Settingsdialog::updateLabels()
{
    std::array<QLabel*, Constants::PRESET_SIZE > labels = { ui->label_2, ui->label_3, ui->label_4, ui->label_5 };

    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        labels[i]->setText(Utility::getProgram_name(edits[i]->text()));
}

void Settingsdialog::pushbutton()
{
    const QStringList titles = runtime->name_map.keys();
    const QStringList ids    = runtime->name_map.values();

    for (int i = 0; i < Constants::PRESET_SIZE; ++i) {

        QString opt = edits[i]->text();

        // すでに id_map にある → 正規化不要
//        if (!MainWindow::id_map.contains(opt)) {

        if (!runtime->id_map.contains(opt)) {
            // ① title（番組名）で部分一致検索
            for (int j = 0; j < titles.count(); ++j) {
                if (titles[j].contains(opt, Qt::CaseInsensitive)) {
                    opt = ids[j];
                    break;
                }
            }

            // ② id（ID文字列）で部分一致検索
//            if (!MainWindow::id_map.contains(opt)) {
           if (!runtime->id_map.contains(opt)) {         
                for (int j = 0; j < ids.count(); ++j) {
                    if (ids[j].contains(opt, Qt::CaseInsensitive)) {
                        opt = ids[j];
                        break;
                    }
                }
            }
        }

        // scramble_set による最終決定
        opt = scramble_set(opt, i);
        edits[i]->setText(opt);
    }

    ui->radioButton_9->setChecked(true);
    updateLabels();
}

void Settingsdialog::pushbutton_2()
{
    QStringList titles;

    for (int i = 0; i < Constants::PRESET_SIZE; ++i)
        titles << runtime->id_map.value(edits[i]->text());

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

    // bool をクリア（特別番組変更時は無効化）
    settings.specEnabled[p.keyEnabled] = false;

    // title の更新（id_map → 番組名）
    if( !(runtime->id_map.contains(newValue)))
    	settings.specTitle[p.keyTitle] = Utility::getProgram_name(newValue);
    else	
    	settings.specTitle[p.keyTitle] = runtime->id_map[newValue];

    settings.save();   // INI に書き込み
    return newValue;
}


*/
