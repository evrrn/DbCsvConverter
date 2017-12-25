#-------------------------------------------------
#
# Project created by QtCreator 2017-12-17T17:17:57
#
#-------------------------------------------------

QT       += sql testlib
QT       -= gui

TARGET   = testdbcsv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG+=c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        ../converter.cpp \
        ../dbtocsv.cpp \
        ../csvtodb.cpp \
        testmain.cpp \
    testcsvtodb.cpp \
    testdbtocsv.cpp

HEADERS += ../converter.h \
        testmain.h


DEFINES += SRCDIR=\\\"$$PWD/\\\"
