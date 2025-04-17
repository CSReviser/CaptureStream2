# 必要なCMakeのバージョン
cmake_minimum_required(VERSION 3.16)

# プロジェクト名をテスト用に設定
project(CaptureStream2Tests LANGUAGES CXX)

# Qt6を検索
find_package(Qt6 REQUIRED COMPONENTS Test Widgets Core Network)

# テスト用のターゲットを作成
add_executable(AppStartTest
    appstarttest.cpp
)

# アプリケーションの既存ヘッダーやソースを利用する（相対パスを指定）
target_include_directories(AppStartTest PRIVATE ../  Qt6::Core Qt6::Network)  # アプリのルートディレクトリを含める

# 必要なライブラリをリンク
target_link_libraries(AppStartTest PRIVATE Qt6::Test Qt6::Widgets)

# テストの登録
enable_testing()
add_test(NAME AppStartTest COMMAND AppStartTest)
