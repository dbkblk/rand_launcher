#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T21:47:27
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = upd_proc
TEMPLATE = app


SOURCES += main.cpp\
        updater.cpp \
    task_updater.cpp

HEADERS  += updater.h \
    task_updater.h

FORMS += \
    form.ui \
    task_updater.ui

RC_FILE = icon.rc
