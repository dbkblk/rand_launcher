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

Release:DESTDIR = ../build/updater_release
Release:OBJECTS_DIR = ../build/updater_release/.obj
Release:MOC_DIR = ../build/updater_release/.moc
Release:RCC_DIR = ../build/updater_release/.rcc
Release:UI_DIR = ../build/updater_release/.ui

Debug:DESTDIR = ../build/updater_debug
Debug:OBJECTS_DIR = ../build/updater_debug/.obj
Debug:MOC_DIR = ../build/updater_debug/.moc
Debug:RCC_DIR = ../build/updater_debug/.rcc
Debug:UI_DIR = ../build/updater_debug/.ui