QT += qml
QT += quick
QT += quickcontrols2
QT += remoteobjects
QT += websockets
QT += svg
QT += widgets

CONFIG += c++11

HEADERS += \
    lists/loglist.h \
    lists/loglistview.h \
    lists/logstructs.h \
    models/logviewmodel.h \
    runtime/client.h \
    models/pinmodel.h \
    lists/pinlist.h \
    models/devicemodel.h \
    lists/devicelist.h \
    lists/grouplist.h \
    models/groupmodel.h \
    models/schedulemodel.h \
    lists/schedulelist.h \
    models/sharedmodel.h \
    lists/sharedlist.h \
    models/controldevicemodel.h \
    lists/controldevicelist.h \
    objects/user.h \
    models/iconmodel.h \
    lists/iconlist.h \
    models/pintypemodel.h \
    lists/pintypelist.h \
    linuxFunctions/externalfunctions.h

SOURCES += runtime/client.cpp \
    lists/loglist.cpp \
    lists/loglistview.cpp \
    models/logviewmodel.cpp \
    models/pinmodel.cpp \
    lists/pinlist.cpp \
    models/devicemodel.cpp \
    lists/devicelist.cpp \
    lists/grouplist.cpp \
    models/groupmodel.cpp \
    models/schedulemodel.cpp \
    lists/schedulelist.cpp \
    models/sharedmodel.cpp \
    lists/sharedlist.cpp \
    models/controldevicemodel.cpp \
    lists/controldevicelist.cpp \
    objects/user.cpp \
    models/iconmodel.cpp \
    lists/iconlist.cpp \
    models/pintypemodel.cpp \
    lists/pintypelist.cpp \
    linuxactivity.cpp \
    linuxFunctions/externalfunctions.cpp

RESOURCES += \
    icons.qrc \
    images.qrc \
    qml.qrc

QML_IMPORT_PATH =

#INCLUDEPATH += /usr/include/libnotifymm-1.0
LIBS += -L/lib -lgiomm-2.4

REPC_REPLICA += remote.rep
