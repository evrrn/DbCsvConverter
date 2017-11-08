#-------------------------------------------------
#
# Project created by QtCreator 2017-09-14T10:57:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DbCsvConverter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG+=c++11
QMAKE_CXXFLAGS += -std=c++11
SOURCES += main.cpp\
        mainwindow.cpp \
        converter.cpp

HEADERS += mainwindow.h \
        converter.h \

FORMS   += mainwindow.ui

