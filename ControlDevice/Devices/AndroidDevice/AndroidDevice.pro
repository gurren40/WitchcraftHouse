QT += quick quickcontrols2 websockets androidextras remoteobjects
CONFIG += c++11 create_prl link_prl

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = Witchcraft_House

#HEADERS += \
    #service/notificationclient.h

SOURCES += \
        main.cpp \
    backend.cpp
    #service/notificationclient.cpp

RESOURCES += qml.qrc \
    images.qrc

REPC_REPLICA += ../../service/service.rep

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/gradle/wrapper/gradle-wrapper.jar \
    android-sources/gradlew \
    android-sources/gradle/wrapper/gradle-wrapper.properties \
    android-sources/gradlew.bat \
    android-sources/AndroidManifest.xml \
    android-sources/gradle/wrapper/gradle-wrapper.jar \
    android-sources/gradlew \
    android-sources/res/values/libs.xml \
    android-sources/build.gradle \
    android-sources/gradle/wrapper/gradle-wrapper.properties \
    android-sources/gradlew.bat \
    android-sources/src/id/web/witchcraft/house/NotificationClient.java \
    android-sources/src/id/web/witchcraft/house/MyService.java \
    android-sources/src/id/web/witchcraft/house/MyBroadcastReceiver.java

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug/release/ -lserver
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug/debug/ -lserver
#else:unix: LIBS += -L$$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug/ -lserver

#INCLUDEPATH += $$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug
#DEPENDPATH += $$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug
#server.files += $$PWD/build-AndroidDeviceServer-Android_for_arm64_v8a_Clang_Qt_5_12_0_android_arm64_v8a-Debug/android-build/libs/arm64-v8a/*
#server.path += /libs/arm64-v8a/

#INSTALLS += server

HEADERS += \
    backend.h
