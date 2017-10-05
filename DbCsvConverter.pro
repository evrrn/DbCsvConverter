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


SOURCES += main.cpp\
        mainwindow.cpp \
        dbtocsv.cpp \

HEADERS  += mainwindow.h \
        dbtocsv.h \

FORMS    += mainwindow.ui
