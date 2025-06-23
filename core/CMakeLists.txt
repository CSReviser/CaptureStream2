add_library(appcore STATIC
    appsettings.h
    settingsmanager.cpp
    settingsmanager.h
)

target_link_libraries(appcore
	Qt6::Core
	Qt6::Network
)
target_include_directories(appcore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
