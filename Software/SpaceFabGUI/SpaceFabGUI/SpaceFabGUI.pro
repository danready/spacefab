#-------------------------------------------------
#
# Project created by QtCreator 2016-10-14T10:15:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceFabGUI
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    clickablelabel.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    clickablelabel.h \
    DefineGeneral.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    Resource.qrc
