#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T22:43:43
#
#-------------------------------------------------

INCLUDEPATH += .

QT       += core gui network widgets xml

TARGET = and2_checker

TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    civ_functions.cpp \
    optionbox.cpp \
    updatebox.cpp \
    updatemanager.cpp \
    lib/packbinaries.cpp \
    modules.cpp \
    svn_functions.cpp

HEADERS += \
    mainwindow.h \
    civ_functions.h \
    optionbox.h \
    updatebox.h \
    updatemanager.h \
    lib/packbinaries.h \
    modules.h \
    svn_functions.h

FORMS    += mainwindow.ui \
    installBox.ui \
    optionbox.ui \
    updatebox.ui \
    updatemanager.ui \
    modules.ui

RC_FILE = icon.rc

OTHER_FILES += \
    README.md \
    TODO.md \
    installer/installer_script.nsi \
    README.md \
    TODO.md
