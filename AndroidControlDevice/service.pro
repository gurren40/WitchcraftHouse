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
    services/connection.h

SOURCES += service.cpp \
    remote.cpp \
    services/notification.cpp \
    services/connection.cpp

REPC_SOURCE += remote.rep
REPC_REPLICA += remote.rep
