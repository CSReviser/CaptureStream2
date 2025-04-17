#include <QtTest/QtTest>
#include "../mainwindow.h"  // アプリケーションのヘッダーをインクルード

class AppStartTest : public QObject
{
    Q_OBJECT

private slots:
    void testMainWindowStartup();
};

void AppStartTest::testMainWindowStartup()
{
    // アプリのメインウィンドウを作成
    MainWindow mainWindow;
    mainWindow.show();

    // ウィンドウがアクティブになるまで待機
    QVERIFY(QTest::qWaitForWindowActive(&mainWindow));
}

QTEST_MAIN(AppStartTest)
#include "appstarttest.moc"
