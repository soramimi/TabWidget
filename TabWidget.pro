
TARGET = Test
QT += core gui widgets
CONFIG += c++11
CONFIG -= app_bundle

DESTDIR = $$PWD/_bin

SOURCES += \
        MainWindow.cpp \
        main.cpp \
    TabWidget.cpp

FORMS += \
	MainWindow.ui

HEADERS += \
	MainWindow.h \
    HorizontalTabWidget.h \
    TabWidget.h
