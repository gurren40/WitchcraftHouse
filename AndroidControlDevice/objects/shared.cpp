#include "shared.h"

Shared::Shared(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Shared::remote() const
{
    return m_remote;
}

void Shared::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void Shared::getSharedList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getSharedList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Shared::createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description)
{
//    int sharedBy = userID;
//    int sharedTo = getSharedToID(jsonObject["sharedTo"].toString());
//    if (sharedTo > 0){
//        bool sharedType = jsonObject["sharedType"].toBool();
//        int groupID = jsonObject["groupID"].toInt(0);
//        QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
//        int pinID = getPinIDbyUUID(UUID);
//        if(pinID > 0){
//            QString sharedName = jsonObject["sharedName"].toString();
//            QString description = jsonObject["description"].toString(" ");
//            error = shared.create(sharedBy,sharedTo,sharedType,groupID,pinID,sharedName,description);
    QJsonObject jsonObj;
    jsonObj["sharedName"] = sharedName.toString();
    jsonObj["sharedTo"] = sharedTo.toString();
    jsonObj["sharedType"] = sharedType.toBool();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["pinUUID"] = pinUUID.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewShared"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Shared::editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description)
{
//    int sharedID = jsonObject["sharedID"].toInt();
//    shared.read("sharedID='"+QString::number(sharedID)+"'");
//    if(shared.mShareds.size() != 1){
//        error["error"] = "sharedID "+json["sharedID"].toString()+" is not valid";
//        error["errorCode"] = "9";
//        notification["title"]="Error";
//        notification["description"] = error["error"].toString();
//    }
//    else {
//        int sharedBy = userID;
//        int sharedTo = getSharedToID(jsonObject["sharedTo"].toString());
//        if (sharedTo > 0){
//            bool sharedType = jsonObject["sharedType"].toBool();
//            int groupID = jsonObject["groupID"].toInt(0);
//            QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
//            int pinID = getPinIDbyUUID(UUID);
//            if(pinID > 0){
//                QString sharedName = jsonObject["sharedName"].toString();
//                QString description = jsonObject["description"].toString(" ");
//                error = shared.update(sharedID,sharedBy,sharedTo,sharedType,groupID,pinID,sharedName,description);
    QJsonObject jsonObj;
    jsonObj["sharedID"] = sharedID.toInt();
    jsonObj["sharedName"] = sharedName.toString();
    jsonObj["sharedTo"] = sharedTo.toString();
    jsonObj["sharedType"] = sharedType.toBool();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["pinUUID"] = pinUUID.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editShared"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Shared::deleteShared(QVariant sharedID)
{
    QJsonObject jsonObj;
    jsonObj["sharedID"] = sharedID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteShared"] = jsonArray;
    m_remote->sendToServer(toSend);
}
