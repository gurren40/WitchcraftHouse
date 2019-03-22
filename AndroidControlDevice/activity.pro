QT += qml
QT += quick
QT += quickcontrols2
QT += androidextras
QT += remoteobjects
QT += websockets

CONFIG += c++11

HEADERS +=
SOURCES += activity.cpp

RESOURCES += qml.qrc

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
    android/src/id/web/witchcraft/house/MyBroadcastReceiver.java

ANDROID_PACKAGE_SOURCE_DIR = \
    $$PWD/android

include(deployment.pri)
