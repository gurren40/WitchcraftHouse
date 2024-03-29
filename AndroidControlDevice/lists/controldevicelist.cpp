#include "controldevicelist.h"

ControlDeviceList::ControlDeviceList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    ControlDeviceItem item;
    item.controlDeviceID = "controlDeviceID";
    item.userID = 1;
    item.userName ="userName";
    item.controlDeviceName = "controlDeviceName";
    item.controlDeviceToken = "controlDeviceToken";
    item.isControlDeviceOnline = true;
    item.expireDate = QDate::currentDate();
    ControlDeviceItem item2;
    item2 = item;
    item.isControlDeviceOnline = false;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<ControlDeviceItem> ControlDeviceList::items() const
{
    return mItems;
}

bool ControlDeviceList::setItemAt(int index, const ControlDeviceItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void ControlDeviceList::setControlDeviceList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("controlDeviceList").toArray();
    emit preItemDataChanged();
    //emit preItemsResetRemove(mItems.size());
    mItems.clear();
    //emit postItemResetRemove();
    //emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        ControlDeviceItem item;
        item.controlDeviceID = jsonItem["controlDeviceID"].toString();
        item.userID = jsonItem["userID"].toInt();
        item.userName = jsonItem["userName"].toString();
        item.controlDeviceName = jsonItem["controlDeviceName"].toString();
        item.controlDeviceToken = jsonItem["controlDeviceToken"].toString();
        item.isControlDeviceOnline = jsonItem["isControlDeviceOnline"].toBool();
        item.expireDate = QDate::fromString(jsonItem["expireDate"].toString().toUtf8());
        mItems.append(item);
    }
    //emit postItemResetAppend();
    emit postItemDataChanged();
}

void ControlDeviceList::getControlDeviceList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getControlDeviceList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

RemoteReplica *ControlDeviceList::getRemote() const
{
    return m_remote;
}

void ControlDeviceList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void ControlDeviceList::deleteControlDevice(QVariant controlDeviceID)
{
    QJsonObject jsonObj;
    jsonObj["controlDeviceID"] = controlDeviceID.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteControlDevice"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

QVariant ControlDeviceList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject ControlDeviceList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}
