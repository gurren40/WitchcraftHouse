QT += core websockets androidextras remoteobjects
QT -= gui

TEMPLATE = lib
TARGET = witchserver
CONFIG += dll
SOURCES += \
    androidserver.cpp


#HEADERS +=


REPC_SOURCE += \
    service/service.rep
