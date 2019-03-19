#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QQuickStyle>
#include <QIcon>
#include <QRemoteObjectNode>
#include <QAndroidJniObject>
#include <QtAndroid>

//#include <QtAndroid>
#include <QDebug>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidIntent>
#include <QAndroidServiceConnection>
#include <QAndroidBinder>
#include <QAndroidParcel>

#include "backend.h"


int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("WitchcraftHouse");
    QGuiApplication::setOrganizationName("Witchcraft");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QIcon::setThemeName("WitchcraftHouse");

    //now start the fuckin service
    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house",
                                                  "startMyService",
                                                  "(Landroid/content/Context;)V",
                                                  QtAndroid::androidActivity().object());

    QSettings settings;
    QString style = QQuickStyle::name();
    if (!style.isEmpty())
        settings.setValue("style", style);
    else
        QQuickStyle::setStyle(settings.value("style").toString());

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("availableStyles", QQuickStyle::availableStyles());

    if((!settings.contains("isLogged")) || (settings.value("isLogged").toBool())){
        settings.setValue("isLogged",false);
    }
    else if (!settings.value("isLogged").toBool()) {
        settings.setValue("isLogged",true);
    }
    if(!settings.value("isLogged").toBool()){
        engine.load(QUrl("qrc:/qml/init/init.qml"));
    }
    else {
        engine.load(QUrl("qrc:/qml/main.qml"));
    }
    if (engine.rootObjects().isEmpty())
        return -1;

    Backend *backend = new Backend;
    backend->createServer();

    return app.exec();
}
