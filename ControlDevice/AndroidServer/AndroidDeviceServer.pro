QT += core websockets androidextras remoteobjects

TEMPLATE = lib
TARGET = server
CONFIG += dll
SOURCES += \
    ../../../service/connection.cpp \
    server.cpp
#    ../../../service/service.cpp \


HEADERS += \
        ../../../service/connection.h
#    ../../../service/service.h \


REPC_SOURCE += \
    ../../../service/service.rep
