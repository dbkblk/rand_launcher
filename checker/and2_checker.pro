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
    updatemanager.cpp

HEADERS += \
    mainwindow.h \
    civ_functions.h \
    optionbox.h \
    updatebox.h \
    updatemanager.h

FORMS    += mainwindow.ui \
    installBox.ui \
    optionbox.ui \
    updatebox.ui \
    updatemanager.ui

RC_FILE = icon.rc

OTHER_FILES += \
    README.md \
    TODO.md \
    installer/installer_script.nsi \
    README.md \
    TODO.md

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib_packbinaries/release/ -llib_packbinaries
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib_packbinaries/debug/ -llib_packbinaries

INCLUDEPATH += $$PWD/../lib_packbinaries
DEPENDPATH += $$PWD/../lib_packbinaries

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib_packbinaries/release/lib_packbinaries
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib_packbinaries/debug/lib_packbinaries
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib_packbinaries/release/lib_packbinaries.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib_packbinaries/debug/lib_packbinaries.lib
