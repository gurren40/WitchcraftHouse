#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QQuickStyle>
#include <QIcon>


int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("WitchcraftHouse");
    QGuiApplication::setOrganizationName("Witchcraft");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QIcon::setThemeName("WitchcraftHouse");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("availableStyles", QQuickStyle::availableStyles());
    engine.load(QUrl("qrc:/qml/init/init.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
