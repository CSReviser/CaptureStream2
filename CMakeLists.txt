cmake_minimum_required(VERSION 3.16)
project(CaptureStream2 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui Network Widgets Xml)



qt_add_executable(CaptureStream2 WIN32 MACOSX_BUNDLE TRUE
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

target_compile_definitions(CaptureStream2 PRIVATE
    QT_DISABLE_DEPRECATED_UP_TO=0x050F00
)

target_link_libraries(CaptureStream2 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Widgets
    Qt6::Xml
)


# Resources:
set(stylesheet_resource_files
    "stylesheet-mac.qss"
    "stylesheet-ubu.qss"
    "stylesheet-win.qss"
)

qt_add_resources(CaptureStream2 "stylesheet"
    PREFIX
        "/"
    FILES
        ${stylesheet_resource_files}
)

install(TARGETS CaptureStream2
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
