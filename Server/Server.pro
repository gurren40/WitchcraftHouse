QT += core websockets sql
QT -= gui
CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    Entity/user.cpp \
    Entity/group.cpp \
    Entity/device.cpp \
    Entity/icon.cpp \
    Entity/pintype.cpp \
    Entity/pin.cpp \
    Entity/schedule.cpp \
    Entity/shared.cpp \
    Entity/controlldevice.cpp \
    Control/usercontroller.cpp \
    Control/devicecontroller.cpp \
    Control/schedulecontroller.cpp \
    Control/sharedcontroller.cpp \
    Boundary/websocketserver.cpp \
    Entity/log.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Entity/user.h \
    Entity/group.h \
    Entity/device.h \
    Entity/icon.h \
    Entity/pintype.h \
    Entity/pin.h \
    Entity/schedule.h \
    Entity/shared.h \
    Entity/controlldevice.h \
    Control/usercontroller.h \
    Control/devicecontroller.h \
    Control/schedulecontroller.h \
    Control/sharedcontroller.h \
    Boundary/websocketserver.h \
    Entity/log.h
