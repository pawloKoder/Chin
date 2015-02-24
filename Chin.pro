#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T12:42:19
#
#-------------------------------------------------


CONFIG += c++11 qt
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chin
TEMPLATE = app


SOURCES += src/main.cpp\
    src/mainwindow.cpp \
    src/characterset.cpp \
    src/charactermatcher.cpp \
    src/imageutils.cpp

INCLUDEPATH += include
HEADERS  += include/mainwindow.h \
    include/characterset.h \
    include/charactermatcher.h \
    include/imageutils.h

FORMS    += ui/mainwindow.ui

RESOURCES += \
    qrc/fonts/fonts.qrc
