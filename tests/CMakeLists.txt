# 必要なCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# テストプロジェクト名
project(CaptureStream2Tests LANGUAGES CXX)

# Qt6のモジュールを検索
find_package(Qt6 REQUIRED COMPONENTS Test Core Gui Network Widgets Xml)

# 自動MOC, AUTOUIC, AUTORCCを有効化
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# アプリケーションのソースファイルを明示的に追加
set(APP_SOURCES
    ../mainwindow.cpp
    ../customizedialog.cpp
    ../downloadmanager.cpp
    ../downloadthread.cpp
    ../messagewindow.cpp
    ../scrambledialog.cpp
    ../settingsdialog.cpp
    ../urldownloader.cpp
    ../utility.cpp
    ../mainwindow.ui
    ../customizedialog.ui
    ../messagewindow.ui
    ../scrambledialog.ui
    ../settingsdialog.ui
)

# テスト用のターゲットを作成
add_executable(AppStartTest
    appstarttest.cpp
    ${APP_SOURCES}  # アプリケーションのソースファイルとUIファイルをリンク
)

# アプリのヘッダーやソースを利用するためのインクルードパスを追加
target_include_directories(AppStartTest PRIVATE ../)

# 必要なQtモジュールをリンク
target_link_libraries(AppStartTest PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Widgets
    Qt6::Xml
)

# テストを登録
enable_testing()
add_test(NAME AppStartTest COMMAND AppStartTest)