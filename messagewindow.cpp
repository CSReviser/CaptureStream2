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

#include "messagewindow.h"
#include "ui_messagewindow.h"
#include "mainwindow.h"
#include "utility.h"
#include "settings.h" 

#include <QtGui>
#include <QTextCursor>
#include <QSettings>
#include <QVariant>
#include <QWidget>
#include <QFontDatabase>
#include <QTimer>

namespace {
	const QString SETTING_GROUP( "MessageWindow" );
	const QString SETTING_GEOMETRY( "geometry" );
	const int DEFAULT_WIDTH = 540;
	const int DEFAULT_HEIGHT = 300;
#ifdef Q_OS_WIN
	const int FONT_SIZE = 13;
#else
#ifdef Q_OS_MACOS
	const int FONT_SIZE = 14;
#else
	const int FONT_SIZE = 14;
#endif
#endif
}

MessageWindow::MessageWindow(QWidget *parent)
    : QWidget(parent, Qt::CustomizeWindowHint|Qt::WindowTitleHint|Qt::WindowCloseButtonHint)
{
    setupGui();

    // Settings から geometry を読み込む
    const QByteArray &geo = Settings::instance().messageWindowGeometry;
    if (!geo.isEmpty()) {
        restoreGeometry(geo);
    } else {
        resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }

/*
Settings& s = Settings::instance();

if (s.messageWindowSize.isValid())
    this->resize(s.messageWindowSize);

if (!s.messageWindowPos.isNull())
    this->move(s.messageWindowPos);
else if (!s.messageWindowGeometry.isEmpty())
    this->restoreGeometry(s.messageWindowGeometry);
else {
    QPoint pos = parentWidget()->mapToGlobal(QPoint(width(), 0)) + QPoint(20, 20);
    this->move(pos);
}
*/
}

MessageWindow::~MessageWindow()
{
//     Settings::instance().saveMessageWindow(saveGeometry());
     Settings::instance().saveMessageWindow(
    this->saveGeometry(),
    this->pos(),
    this->size()
);

}

void MessageWindow::changeEvent( QEvent *e ) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
		//ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MessageWindow::setupGui() {
	textEdit = new QPlainTextEdit;
	textEdit->setReadOnly( true );
	textEdit->setWordWrapMode( QTextOption::WrapAnywhere );
	QFont font;
	font.setStyleHint(QFont::Monospace);
//	font.setFamily("monospace");
	font.setPixelSize(FONT_SIZE);
	textEdit->setFont(font);
	textEdit->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

	clearTextButton = new QPushButton( QString::fromUtf8( "クリア" ) );
	connect( clearTextButton, SIGNAL(clicked()), this, SLOT(clearText()) );

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(textEdit);
	mainLayout->addWidget(clearTextButton);

	setLayout(mainLayout);
}

QString MessageWindow::text() {
	return textEdit->toPlainText();
}

// 改行あり
void MessageWindow::appendParagraph( const QString& text ) {
	show();
//	QTimer::singleShot(0, this, [this]{
//	        resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
//	});
	textEdit->appendPlainText( text );
}

// 改行なし
void MessageWindow::append( const QString& text ) {
	show();
	QTextCursor cursor = textEdit->textCursor();
	cursor.movePosition( QTextCursor::End );
	textEdit->setTextCursor( cursor );
	textEdit->insertPlainText( text );
}

void MessageWindow::clearText() {
	textEdit->clear();
}

