# 必要なCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# テストプロジェクト名
project(CaptureStream2Tests LANGUAGES CXX)

# Qt6のモジュールを検索
find_package(Qt6 REQUIRED COMPONENTS Test Core Gui Network Widgets Xml)

# 自動MOCを有効化
set(CMAKE_AUTOMOC ON)

# テスト用のターゲットを作成
add_executable(AppStartTest
    appstarttest.cpp
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