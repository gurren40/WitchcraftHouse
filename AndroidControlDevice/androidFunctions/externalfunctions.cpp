#include "externalfunctions.h"

ExternalFunctions::ExternalFunctions(QObject *parent) : QObject(parent)
{

}

void ExternalFunctions::callAndroidService()
{
    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
                                                  "startMyService",
                                                  "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());
}

QString ExternalFunctions::getDeviceModel()
{
    QAndroidJniObject jstringValue = QAndroidJniObject::callStaticObjectMethod<jstring>("id/web/witchcraft/house/MyActivity","getDeviceModel");
    return jstringValue.toString();
}

void ExternalFunctions::sendNotification(int id, QString title, QString body)
{
    jint jNotificationID = id;
    QAndroidJniObject jNotificationTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject jNotificationText = QAndroidJniObject::fromString(body);
    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
                                       "notify",
                                       "(ILjava/lang/String;Ljava/lang/String;)V",
                                       jNotificationID,
                                       jNotificationTitle.object<jstring>(),
                                       jNotificationText.object<jstring>());
}
