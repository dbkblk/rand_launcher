#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T21:47:27
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=static

QMAKE_LFLAGS = -static-libgcc -static-libstdc++ -static -lpthread

TARGET = upd_proc
TEMPLATE = app

SOURCES += main.cpp \
    w_main.cpp \
    f_updater.cpp

HEADERS  += \
    w_main.h \
    f_updater.h

FORMS += \
    w_main.ui

RC_FILE = icon.rc
