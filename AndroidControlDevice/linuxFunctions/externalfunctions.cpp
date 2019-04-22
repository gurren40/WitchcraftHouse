#include "externalfunctions.h"

ExternalFunctions::ExternalFunctions(QObject *parent) : QObject(parent)
{

}

void ExternalFunctions::callAndroidService()
{
//    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
//                                                  "startMyService",
//                                                  "(Landroid/content/Context;)V",
//                                              QtAndroid::androidActivity().object());
    //this is a dummy
}

QString ExternalFunctions::getDeviceModel()
{
    QString model;
    QFile osRelease("/etc/os-release");
    if (!osRelease.open(QIODevice::ReadOnly)) {
        model = "Unknown";
    }
    else{
        QString osdetail = osRelease.readAll();
        QStringList theList = osdetail.split("\n");
        QStringList osname = theList[0].split("=");
        model = osname[1].remove("\"",Qt::CaseInsensitive);
    }
    return  model;
}

void ExternalFunctions::sendNotification(int id, QString title, QString body)
{
//    Notify::init(QString::number(id).toUtf8());
//    Notify::Notification Hello(title.toUtf8(), body.toUtf8(), "dialog-information");
//    Hello.show();
    QTextStream(stdout) << "id : " << id << ", title : " << title << ", body :\n" << body << "\n";
}
