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
#include "programresolver.h"
#include <QMessageBox>

ScrambleDialog::ScrambleDialog(Settings& ini, QWidget *parent)
    : QDialog(parent), ui(new Ui::ScrambleDialog), settings(ini)
{
    ui->setupUi(this);
    
    applyOptionPresetLabels();

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
    for (int i = 0; i < Constants::getOptionalCount(); i++){
        QString opt = edits[i]->text();
        QString resolved = ProgramResolver::resolveUnique(opt);
        if (!resolved.isEmpty())
            updateOptional(i, edits[i]->text());
    }
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
    for (int i = 0; i < Constants::getOptionalCount(); ++i) {

        QString opt = edits[i]->text();

        QString resolved = ProgramResolver::resolveUnique(opt);
        if (!resolved.isEmpty())
            opt = resolved;

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


void ScrambleDialog::applyOptionPresetLabels()
{
    for (int i = 0; i < Constants::getOptionLabelCount(); ++i) {
        const auto& item = Constants::OPTION_LABEL[i];

        QObject* obj = this->findChild<QObject*>(item.objectName);
        if (!obj)
            continue;

        QRadioButton* rb = qobject_cast<QRadioButton*>(obj);
        if (!rb)
            continue;

        rb->setText(QString::fromUtf8(item.label));
    }
}

