
TARGET = Test
QT += core gui widgets
CONFIG += c++11
CONFIG -= app_bundle

DESTDIR = $$PWD/_bin

SOURCES += \
        MainWindow.cpp \
	MyFrame.cpp \
        main.cpp \
    TabWidget.cpp

FORMS += \
	MainWindow.ui

HEADERS += \
	MainWindow.h \
    HorizontalTabWidget.h \
	MyFrame.h \
    TabWidget.h
