TEMPLATE = lib
TARGET = service
CONFIG +=dll

QT += core
QT += remoteobjects
QT += androidextras
QT += websockets

HEADERS += \
    remote.h \
    services/notification.h \
    services/connection.h \
    runtime/server.h \
    services/remoterepheader.h \
    androidFunctions/externalfunctions.h

SOURCES += service.cpp \
    remote.cpp \
    services/notification.cpp \
    services/connection.cpp \
    runtime/server.cpp \
    androidFunctions/externalfunctions.cpp

REPC_SOURCE += remote.rep
REPC_REPLICA += remote.rep
