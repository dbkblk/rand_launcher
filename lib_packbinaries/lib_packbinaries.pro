#-------------------------------------------------
#
# Project created by QtCreator 2014-05-28T16:55:49
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = lib_packbinaries
TEMPLATE = lib

DEFINES += LIB_PACKBINARIES_LIBRARY

SOURCES += packbinaries.cpp

HEADERS += packbinaries.h\
        lib_packbinaries_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
