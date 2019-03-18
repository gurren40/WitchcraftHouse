QT += core websockets remoteobjects
TEMPLATE = lib
TARGET = server
CONFIG += dll
HEADERS += \
    service.h
SOURCES += \
    server.cpp \
    service.cpp

REPC_SOURCE += /home/aditiya/QtProjects/Witchcraft/witchcrafthouse/ControlDeviceService/service.rep
