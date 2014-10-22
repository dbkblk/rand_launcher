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
    f_check.cpp \
    f_civ.cpp \
    w_main.cpp \
    w_modules.cpp \
    w_options.cpp \
    f_svn.cpp \
    w_install.cpp

HEADERS += \
    f_check.h \
    f_civ.h \
    f_svn.h \
    w_main.h \
    w_modules.h \
    w_options.h \
    w_install.h

FORMS    += \
    updatebox.ui \
    w_main.ui \
    w_modules.ui \
    w_options.ui \
    w_install.ui

RC_FILE = icon.rc

OTHER_FILES += \
    README.md \
    TODO.md \
    installer/installer_script.nsi \
    README.md \
    TODO.md
