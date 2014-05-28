#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T22:43:43
#
#-------------------------------------------------

INCLUDEPATH += .

QT       += core gui network widgets

TARGET = and2_checker

TEMPLATE = app

SOURCES += \
    lib/tinyxml2.cpp \
    main.cpp \
    mainwindow.cpp \
    civ_functions.cpp \
    optionbox.cpp \
    updatebox.cpp \
    updatemanager.cpp

HEADERS += \
    tinyxml2.h \
    lib/tinyxml2.h \
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../PackBinaries/release/ -lPackBinaries
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../PackBinaries/debug/ -lPackBinaries

INCLUDEPATH += $$PWD/../PackBinaries
DEPENDPATH += $$PWD/../PackBinaries

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PackBinaries/release/libPackBinaries.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PackBinaries/debug/libPackBinaries.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PackBinaries/release/PackBinaries.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../PackBinaries/debug/PackBinaries.lib
