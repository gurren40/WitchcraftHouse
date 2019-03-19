TEMPLATE = lib
TARGET = server
CONFIG += dll
QT += core
QT += remoteobjects
QT += androidextras

SOURCES += \
    server.cpp \
    coba.cpp
#DISTFILES += \
#    android/src/com/kdab/training/NotificationClient.java

#ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

REPC_SOURCE += pingpong.rep
REPC_REPLICA += pingpong.rep

HEADERS += \
    coba.h
