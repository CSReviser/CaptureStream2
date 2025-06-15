add_library(appcore STATIC
    FFmpegManager.cpp
    SettingsManager.cpp
    CaptureLogic.cpp
)

target_link_libraries(appcore Qt6::Core)
target_include_directories(appcore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})