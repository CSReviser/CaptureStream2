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
//        fileDialog->accept();               // OK ボタンをクリック
    });

    // ウィンドウがアクティブになるまで待機
    QVERIFY(QTest::qWaitForWindowActive(&mainWindow));

    // スクリーンショットを撮影
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QPixmap screenshot = screen->grabWindow(mainWindow.winId());
        screenshot.save("screenshot.png"); // スクリーンショットを保存
    }

#if defined(Q_OS_MAC)
    // macOSではウィンドウボタンが左上なので、左上の赤い「閉じる」ボタンをクリック
    QPoint closeButton = windowRect.topLeft() + QPoint(10, 10);  // 適宜微調整
#else
    // WindowsやLinuxでは右上
    QPoint closeButton = topRight - QPoint(20, -10);  // ウィンドウの外枠右上から少し左下へオフセット
#endif

    QTest::mouseClick(QApplication::primaryScreen(), Qt::LeftButton, Qt::NoModifier, closeButton);

    // ウィンドウが閉じるのを確認
    QTRY_VERIFY_WITH_TIMEOUT(!mainWindow.isVisible(), 3000);


    // 結果の検証 (必要なら追加)
//    QCOMPARE(mainWindow.customizeSaveFolder(), mockFolder); //　customizeSaveFolder() は MainWindow 側のメソッド
}

QTEST_MAIN(AppStartTest)
#include "appstarttest.moc"