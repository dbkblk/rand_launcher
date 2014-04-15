#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T22:43:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = and2_checker


QMAKE_LFLAGS += -static

TEMPLATE = app


SOURCES += \
    lib/tinyxml2.cpp \
    main.cpp \
    mainwindow.cpp \
    civ_functions.cpp

HEADERS += \
    tinyxml2.h \
    lib/tinyxml2.h \
    mainwindow.h \
    civ_functions.h

FORMS    += mainwindow.ui
