#include <QtTest/QtTest>
#include <QFileDialog>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include "../mainwindow.h"  // メインウィンドウのヘッダーをインクルード

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

    // QFileDialog のモックを設定
    QString mockFolder = "/Users/runner/work/"; // テスト用フォルダを設定
    QScopedPointer<QFileDialog> fileDialog(new QFileDialog(&mainWindow));
    QMetaObject::invokeMethod(fileDialog.data(), [&]() {
        fileDialog->selectFile(mockFolder); // モックとしてフォルダを選択
        fileDialog->accept();               // OK ボタンをクリック
    });

    // ウィンドウがアクティブになるまで待機
    QVERIFY(QTest::qWaitForWindowActive(&mainWindow));

    // スクリーンショットを撮影
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap screenshot = screen->grabWindow(mainWindow.winId());
        screenshot.save("screenshot.png"); // スクリーンショットを保存
    }

    // 結果の検証 (必要なら追加)
    QCOMPARE(mainWindow.customizeSaveFolder(), mockFolder); //　customizeSaveFolder() は MainWindow 側のメソッド
}

QTEST_MAIN(AppStartTest)
#include "appstarttest.moc"