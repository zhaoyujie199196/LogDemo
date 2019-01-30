#-------------------------------------------------
#
# Project created by QtCreator 2019-01-30T15:03:54
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SGMPLoger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comlogqueue.cpp \
    comlogprinter.cpp \
    comlogmanager.cpp

HEADERS  += mainwindow.h \
    comlogqueue.h \
    comlogprinter.h \
    comlogmanager.h

FORMS    += mainwindow.ui
