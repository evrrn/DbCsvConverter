#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T17:17:57
#
#-------------------------------------------------

QT       += sql testlib
QT       -= gui

TARGET   = tst_dbcsv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG+=c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += tst_dbcsv.cpp \
        ../converter.cpp \
        ../dbtocsv.cpp \
        ../csvtodb.cpp

HEADERS += ../converter.h


DEFINES += SRCDIR=\\\"$$PWD/\\\"
