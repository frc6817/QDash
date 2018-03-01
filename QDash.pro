#-------------------------------------------------
#
# Project created by QtCreator 2018-02-04T10:21:04
#
#-------------------------------------------------

QT       += core gui
QT       += webenginewidgets
QT       += network

CONFIG += c++11

DESTDIR = bin

INCLUDEPATH += include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDash
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
    src/client.cpp \
    src/indicator.cpp \
    src/riomessage.cpp \
    src/scheduler.cpp

HEADERS += \
        include/mainwindow.h \
    include/client.h \
    include/indicator.h \
    include/riomessage.h \
    include/scheduler.h

FORMS += \
        forms/mainwindow.ui
