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

#include "scrambledialog.h"
#include "ui_scrambledialog.h"
#include "settings.h"
#include "utility.h"
#include "programrepository.h"
#include <QMessageBox>

ScrambleDialog::ScrambleDialog(Settings& ini, QWidget *parent)
    : QDialog(parent), ui(new Ui::ScrambleDialog), settings(ini)
{
    ui->setupUi(this);

    edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4,
              ui->edit5, ui->edit6, ui->edit7, ui->edit8 };

    // ===== OptionalPrograms の ID を Settings から復元 =====
    for (int i = 0; i < Constants::getOptionalCount(); i++) {
        const auto &p = Constants::OptionalPrograms[i];
        edits[i]->setText(settings.ids[p.keyId]);
    }

    ui->radioButton_9->setChecked(true);

    // ===== フラグ復元 =====
    ui->checkBox_koza_separation->setChecked(settings.checked[Constants::KEY_KOZA_SEPARATION]);
}

ScrambleDialog::~ScrambleDialog()
{
    delete ui;
}

void ScrambleDialog::applyFlags()
{
    settings.checked[Constants::KEY_KOZA_SEPARATION] = ui->checkBox_koza_separation->isChecked();
}

QString ScrambleDialog::scramble_set(QString opt, int index)
{
    using namespace Constants;
        
    const auto& OPT_PRESETS = Constants::getOptPresets();

    std::array<QAbstractButton*, 7> radios = {
        ui->radioButton, ui->radioButton_1, ui->radioButton_2,
        ui->radioButton_3, ui->radioButton_4, ui->radioButton_5,
        ui->radioButton_6
    };

    // プリセット適用
    for (int j = 0; j < OPT_PRESETS.size() && j < radios.size(); ++j) {
        if (radios[j]->isChecked()) {
            opt = OPT_PRESETS[j][index];
        }
    }

    // ユーザープリセット
    if (ui->radioButton_6->isChecked()) {
        auto opt1 = settings.optionals;
        if (!opt1[index].isEmpty())
            opt = opt1[index];
    }

    QLineEdit *edit = edits[index];
    auto &repo = ProgramRepository::instance();
    if (!ui->radioButton_9->isChecked()) {
        edit->setText(opt);
    } else {
        // name_map → id_map
        if (repo.name_map.contains(edit->text()))
            opt = repo.name_map[edit->text()];

        if (Utility::getProgram_name(edit->text()).isEmpty())
            edit->setText(opt);
    }

    return opt;
}

void ScrambleDialog::accept()
{
    for (int i = 0; i < Constants::getOptionalCount(); i++)
        updateOptional(i, edits[i]->text());

    applyFlags();
    QDialog::accept();
}

void ScrambleDialog::updateLabels()
{
    QVector<QLabel*> labels = {
        ui->label_2, ui->label_3, ui->label_4, ui->label_5,
        ui->label_6, ui->label_7, ui->label_8, ui->label_9
    };

    for (int i = 0; i < Constants::getOptionalCount(); ++i)
        labels[i]->setText(Utility::getProgram_name(edits[i]->text()));
}

void ScrambleDialog::pushbutton()
{
    auto &repo = ProgramRepository::instance();
    const QStringList labels = repo.name_map.keys();
    const QStringList ids    = repo.name_map.values();

    for (int i = 0; i < Constants::getOptionalCount(); ++i) {

        QString opt = edits[i]->text();

        if (!repo.id_map.contains(opt)) {

            // タイトル部分一致
            for (int j = 0; j < labels.count(); ++j) {
                if (labels[j].contains(opt, Qt::CaseInsensitive)) {
                    opt = ids[j];
                    break;
                }
            }

            // ID 部分一致
            if (!repo.id_map.contains(opt)) {
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

void ScrambleDialog::pushbutton_2()
{
    QStringList labels;
    auto &repo = ProgramRepository::instance();
    for (int i = 0; i < Constants::getOptionalCount(); ++i)
        labels << repo.id_map.value(edits[i]->text());

    QString msg =
        QStringLiteral("下記内容で上書きします。保存しますか？\n") +
        "１：" + labels[0] + "\n" +
        "２：" + labels[1] + "\n" +
        "３：" + labels[2] + "\n" +
        "４：" + labels[3] + "\n" +
        "５：" + labels[4] + "\n" +
        "６：" + labels[5] + "\n" +
        "７：" + labels[6] + "\n" +
        "８：" + labels[7];

    if (QMessageBox::question(this, tr("任意番組設定保存"), msg) == QMessageBox::Yes) {
        for (int i = 0; i < Constants::getOptionalCount(); ++i)
            settings.optionals[i] = edits[i]->text();
    }
}

QString ScrambleDialog::updateOptional(int index, const QString &currentText)
{
    using namespace Constants;

    QString newValue = scramble_set(currentText, index);
    const auto &p = OptionalPrograms[index];

    QString oldValue = settings.ids[p.keyId];

    if (oldValue == newValue)
        return newValue;

    // ID 更新
    settings.ids[p.keyId] = newValue;

    // checked を false にする
    settings.checked[p.keyChecked] = false;

    // タイトル更新
    auto &repo = ProgramRepository::instance();
    if (!repo.id_map.contains(newValue))
        settings.labels[p.keyLabel] = Utility::getProgram_name(newValue);
    else
        settings.labels[p.keyLabel] = repo.id_map[newValue];

    settings.save();
    return newValue;
}




/*
#include "scrambledialog.h"
#include "ui_scrambledialog.h"
#include "mainwindow.h"
#include "settings.h"
#include "utility.h"
#include <QSettings>
#include <QMessageBox>

//ScrambleDialog::ScrambleDialog( Settings& ini, RuntimeConfig* r, QString o1, QString o2, QString o3, QString o4, QString o5, QString o6, QString o7, QString o8, QWidget *parent)
ScrambleDialog::ScrambleDialog( Settings& ini, RuntimeConfig* r, QWidget *parent)
    : QDialog(parent), ui(new Ui::ScrambleDialog),settings(ini), runtime(r)
{

    ui->setupUi(this);

    edits = { ui->edit1, ui->edit2, ui->edit3, ui->edit4, ui->edit5, ui->edit6, ui->edit7, ui->edit8 };
    QStringList opts = { "", "", "", "", "", "", "", "" };
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; i++) {
	const auto &p = Constants::OptionalPrograms[i];
	opts[i] = settings.optionalId[p.keyId];
	edits[i]->setText(opts[i]);
    }

    ui->radioButton_9->setChecked(true);

    ui->checkBox_1->setChecked(settings.checkBoxEnabled[Constants::KEY_KOZA_SEPARATION]);
//    applyFlags();

}

ScrambleDialog::~ScrambleDialog()
{
    delete ui;
}

void ScrambleDialog::applyFlags()
{
    settings.checkBoxEnabled[Constants::KEY_KOZA_SEPARATION] =  ui->checkBox_1->isChecked();
}

QString ScrambleDialog::scramble_set(QString opt, int index)
{

    using namespace Constants;

    // ラジオボタン群
    std::array<QAbstractButton*, 7> radios = {
        ui->radioButton, ui->radioButton_1, ui->radioButton_2,
        ui->radioButton_3, ui->radioButton_4, ui->radioButton_5,
        ui->radioButton_6
    };

    // チェックされているプリセットを適用
    for (int j = 0; j < OPT_PRESETS.size() && j < radios.size(); ++j) {
        if (radios[j]->isChecked()) {
            opt = OPT_PRESETS[j][index];
        }
    }

    if (ui->radioButton_6->isChecked()) {
        auto opt1 = settings.optionals;
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

void ScrambleDialog::accept()
{
    // OK ボタンで確定した内容を Settings に保存する
    for (int i = 0; i < Constants::OPT_PRESET_SIZE; i++) {
	updateOptional(i, edits[i]->text());
    }
    applyFlags();
    // ★ 最後に必ず親クラスの accept() を呼ぶ
    QDialog::accept();
}

QString ScrambleDialog::scramble1() { return updateOptional(0, ui->edit1->text()); }
QString ScrambleDialog::scramble2() { return updateOptional(1, ui->edit2->text()); }
QString ScrambleDialog::scramble3() { return updateOptional(2, ui->edit3->text()); }
QString ScrambleDialog::scramble4() { return updateOptional(3, ui->edit4->text()); }
QString ScrambleDialog::scramble5() { return updateOptional(4, ui->edit5->text()); }
QString ScrambleDialog::scramble6() { return updateOptional(5, ui->edit6->text()); }
QString ScrambleDialog::scramble7() { return updateOptional(6, ui->edit7->text()); }
QString ScrambleDialog::scramble8() { return updateOptional(7, ui->edit8->text()); }

void ScrambleDialog::updateLabels()
{
    std::array<QLabel*, Constants::OPT_PRESET_SIZE> labels = { ui->label_2, ui->label_3, ui->label_4, ui->label_5, ui->label_6, ui->label_7, ui->label_8, ui->label_9 };

    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i)
        labels[i]->setText(Utility::getProgram_name(edits[i]->text()));
}

void ScrambleDialog::pushbutton()
{

    const QStringList titles = runtime->name_map.keys();
    const QStringList ids    = runtime->name_map.values();

    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i) {

        QString opt = edits[i]->text();

        // すでに id_map にある → 正規化不要
        if (!runtime->id_map.contains(opt)) {

            // ① title（番組名）で部分一致検索
            for (int j = 0; j < titles.count(); ++j) {
                if (titles[j].contains(opt, Qt::CaseInsensitive)) {
                    opt = ids[j];
                    break;
                }
            }

            // ② id（ID文字列）で部分一致検索
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

void ScrambleDialog::pushbutton_2()
{
    QStringList titles;

    for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i)
        titles << runtime->id_map.value(edits[i]->text());

    QString msg =
        QString::fromUtf8("下記内容で上書きします。保存しますか？\n")
        + "１：" + titles[0] + "\n"
        + "２：" + titles[1] + "\n"
        + "３：" + titles[2] + "\n"
        + "４：" + titles[3] + "\n"
        + "５：" + titles[4] + "\n"
        + "６：" + titles[5] + "\n"
        + "７：" + titles[6] + "\n"
        + "８：" + titles[7];

    if (QMessageBox::question(this, tr("任意番組設定保存"), msg) == QMessageBox::Yes) {
        for (int i = 0; i < Constants::OPT_PRESET_SIZE; ++i)
            settings.optionals[i] = edits[i]->text();
    }
}

QString ScrambleDialog::updateOptional(int index, const QString &currentText)
{
    using namespace Constants;

    // scramble_set により最終的な ID を決定
    QString newValue = scramble_set(currentText, index);

    // 対応する keyId を取得
    const auto &p = OptionalPrograms[index];
    QString oldValue = settings.optionalId[p.keyId];

    // 変更なし → 何もせず返す
    if (oldValue == newValue)
        return newValue;

    // 変更あり → Settings に書き戻し
    settings.optionalId[p.keyId] = newValue;

    // bool をクリア（特別番組変更時は無効化）
    settings.optionalEnabled[p.keyEnabled] = false;

    // title の更新（id_map → 番組名）
    if( !(runtime->id_map.contains(newValue)))
    	settings.optionalTitle[p.keyTitle] = Utility::getProgram_name(newValue);
    else	
    	settings.optionalTitle[p.keyTitle] = runtime->id_map[newValue];

    settings.save();   // INI に書き込み
    return newValue;
}
*/
