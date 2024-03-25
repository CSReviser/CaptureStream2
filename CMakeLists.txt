cmake_minimum_required(VERSION 3.16)
project(CaptureStream2 VERSION 1.0 LANGUAGES C CXX)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14")
set(MACOSX_BUNDLE_ICON_FILE icon.icns)
set(app_icon_macos "${CMAKE_SOURCE_DIR}/icon.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui Network Widgets Xml)

qt_add_executable(${CMAKE_PROJECT_NAME} WIN32 MACOSX_BUNDLE ${app_icon_macos}
    customizedialog.cpp customizedialog.h customizedialog.ui
    downloadmanager.cpp downloadmanager.h
    downloadthread.cpp downloadthread.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    messagewindow.cpp messagewindow.h messagewindow.ui
    qt4qt5.h
    scrambledialog.cpp scrambledialog.h scrambledialog.ui
    urldownloader.cpp urldownloader.h
    utility.cpp utility.h
)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    QT_DISABLE_DEPRECATED_UP_TO=0x050F00
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Widgets
    Qt6::Xml
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

# Resources:
set(stylesheet_resource_files
    "stylesheet-mac.qss"
    "stylesheet-ubu.qss"
    "stylesheet-win.qss"
)

qt_add_resources(${CMAKE_PROJECT_NAME} "stylesheet"
    PREFIX
        "/"
    FILES
        ${stylesheet_resource_files}
)

if(APPLE)
get_target_property(_qmake_executable "Qt6::qmake" IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${_qt_bin_dir}")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/qss_files/stylesheet-mac.qss"
        "$<TARGET_FILE_DIR:CaptureStream2>/../MacOS/"
        COMMENT "Copy stylesheet-mac.qss to MacOS/"
        &&
        COMMAND "${MACDEPLOYQT_EXECUTABLE}"
        ARGS "${CMAKE_PROJECT_NAME}.app"
        COMMENT "Execute macdeployqt to create macOS bundle")
        
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET ${CMAKE_PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
endif()

if(!APPLE)
install(TARGETS ${CMAKE_PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
endif()

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
