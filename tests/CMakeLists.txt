# テストターゲットを作成
add_executable(AppStartTest
    appstarttest.cpp
)

# Qt6ライブラリをリンク（WidgetsとTestを使用）
target_link_libraries(AppStartTest PRIVATE Qt6::Widgets Qt6::Test)