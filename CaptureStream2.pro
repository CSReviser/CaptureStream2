# -------------------------------------------------
# Project created by QtCreator 2009-04-20T14:05:07
# -------------------------------------------------
QT += network \
	gui \
	core \
	xml \
	widgets

#greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
#equals(QT_MAJOR_VERSION, 6):  QT += core5compat
DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x050F00

TARGET = CaptureStream2
TEMPLATE = app
INCLUDEPATH += $$PWD/core

HEADERS += \
    gui/mainwindow.h \
    core/appsettings.h
SOURCES += main.cpp \
	mainwindow.cpp \
	downloadthread.cpp \
	downloadmanager.cpp \
	customizedialog.cpp \
	messagewindow.cpp \
	scrambledialog.cpp \
	settingsdialog.cpp \
	utility.cpp \
	urldownloader.cpp \
	core/settingsmanager.cpp

HEADERS += mainwindow.h \
	downloadthread.h \
	downloadmanager.h \
	customizedialog.h \
	messagewindow.h \
	scrambledialog.h \
	settingsdialog.h \
	utility.h \
	urldownloader.h \
	qt4qt5.h \
	core/settingsmanager.h \
	core/appsettings.h


equals(QT_MAJOR_VERSION, 5):  HEADERS += mp3.h
FORMS += mainwindow.ui \
	customizedialog.ui \
	messagewindow.ui \
	scrambledialog.ui \
	settingsdialog.ui

windows {
	RC_ICONS = icon.ico
}

linux {
	QMAKE_LFLAGS += -no-pie
}

macx {
	QMAKE_CFLAGS_RELEASE += -fvisibility=hidden
	QMAKE_CXXFLAGS_RELEASE += -fvisibility=hidden
#	QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64
	
	x86 {
		CONFIG += c++11
		QMAKE_CFLAGS_RELEASE += -mmacosx-version-min=10.12
		QMAKE_CXXFLAGS_RELEASE += -mmacosx-version-min=10.12
	}

	release {
		QMAKE_POST_LINK += macdeployqt CaptureStream2.app
	}
}

OTHER_FILES += \
	stylesheet-mac.qss \
	stylesheet-win.qss \
	stylesheet-ubu.qss

RESOURCES += \
    stylesheet.qrc
