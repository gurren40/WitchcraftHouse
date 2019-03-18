QT += core websockets remoteobjects
TEMPLATE = lib
TARGET = server
CONFIG += dll
SOURCES += \
    server.cpp \
    ../../../service/service.cpp \
    ../../../service/connection.cpp

HEADERS += \
    ../../../service/service.h \
    ../../../service/connection.h

REPC_SOURCE += \
    ../../../service/service.rep
