#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T19:54:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuteterm
TEMPLATE = app


SOURCES += main.cpp\
				mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(qextserialport/src/qextserialport.pri)

