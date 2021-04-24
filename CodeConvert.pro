#-------------------------------------------------
#
# Project created by QtCreator 2021-02-08T23:57:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeConvert
TEMPLATE = app
DESTDIR = $$PWD/bin
UI_DIR = $$PWD/_temp
RCC_DIR = $$PWD/_temp
OBJECTS_DIR = $$PWD/_temp
MOC_DIR = $$PWD/_temp

SOURCES += main.cpp\
        mainwindow.cpp \
    transcode.cpp

HEADERS  += mainwindow.h \
    transcode.h

FORMS    += mainwindow.ui
