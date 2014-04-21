#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T22:43:43
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = and2_checker

TEMPLATE = app

SOURCES += \
    lib/tinyxml2.cpp \
    main.cpp \
    mainwindow.cpp \
    civ_functions.cpp \
    optionbox.cpp

HEADERS += \
    tinyxml2.h \
    lib/tinyxml2.h \
    mainwindow.h \
    civ_functions.h \
    optionbox.h

FORMS    += mainwindow.ui \
    installBox.ui \
    optionbox.ui

RC_FILE = icon.rc

OTHER_FILES += \
    checker/and2_background.jpg \
    README.md \
    TODO.md
