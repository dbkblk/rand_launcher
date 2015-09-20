#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T22:43:43
#
#-------------------------------------------------

INCLUDEPATH += .

QT       += core gui network widgets xml

TARGET = and2_checker

QMAKE_LFLAGS = -static -lpthread

TEMPLATE = app

SOURCES += \
    main.cpp \
    f_check.cpp \
    f_civ.cpp \
    w_main.cpp \
    w_modules.cpp \
    w_options.cpp \
    w_install.cpp \
    w_exclusion.cpp \
    f_lang.cpp \
    f_mods.cpp

HEADERS += \
    f_check.h \
    f_civ.h \
    w_main.h \
    w_modules.h \
    w_options.h \
    w_install.h \
    w_exclusion.h \
    f_lang.h \
    f_mods.h

FORMS    += \
    w_main.ui \
    w_modules.ui \
    w_options.ui \
    w_install.ui \
    w_exclusion.ui

RC_FILE = icon.rc

OTHER_FILES += \
    README.md \
    installer/installer_script.nsi \
    README.md

DISTFILES +=
