QT += qml
QT += quick
QT += quickcontrols2
QT += androidextras
QT += remoteobjects
QT += websockets
QT += svg
QT += widgets

CONFIG += c++11

HEADERS += \
    runtime/client.h \
#    objects/device.h \
#    objects/group.h \
#    objects/pin.h \
#    objects/schedule.h \
#    objects/shared.h \
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
    lists/pintypelist.h

SOURCES += activity.cpp \
    runtime/client.cpp \
#    objects/device.cpp \
#    objects/group.cpp \
#    objects/pin.cpp \
#    objects/schedule.cpp \
#    objects/shared.cpp \
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
    lists/pintypelist.cpp

RESOURCES += \
    icons.qrc \
    images.qrc \
    qml.qrc

QML_IMPORT_PATH =

REPC_REPLICA += remote.rep

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/id/web/witchcraft/house/MyActivity.java \
    android/src/id/web/witchcraft/house/MyService.java \
    android/src/id/web/witchcraft/house/MyBroadcastReceiver.java \
    android/src/id/web/witchcraft/house/MyJobScheduler.java \
    android/src/id/web/witchcraft/house/MyUtility.java \
    android/res/drawable/splash.xml \
    android/res/values/apptheme.xml \
    android/res/drawable/splashlogo.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png

ANDROID_PACKAGE_SOURCE_DIR = \
    $$PWD/android

include(deployment.pri)
