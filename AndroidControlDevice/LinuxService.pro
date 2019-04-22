QT += core
QT += remoteobjects
QT += websockets
QT -= gui

CONFIG += c++11 console

HEADERS += \
    remote.h \
    services/notification.h \
    services/connection.h \
    runtime/server.h \
    services/remoterepheader.h \
    linuxFunctions/externalfunctions.h

SOURCES += linuxservice.cpp \
    remote.cpp \
    services/notification.cpp \
    services/connection.cpp \
    runtime/server.cpp \
    linuxFunctions/externalfunctions.cpp

REPC_SOURCE += remote.rep
REPC_REPLICA += remote.rep
