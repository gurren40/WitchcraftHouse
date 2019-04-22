import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import QtWebView 1.1
import Pin 1.0
import Icon 1.0
import Group 1.0
import PinType 1.0
import Device 1.0
import QtQuick.Controls.Material 2.12

Page{
    title: "Edit Shared"
    property bool canCreate : false
    id : editShared
    padding: 20
    //[Item properties]
    property int sharedID : 0//model.sharedID
    property string sharedTo : "model.sharedTo"
    property string sharedToName : "model.sharedToName"
    property bool sharedType : false//model.sharedType
    property int groupID : 0//model.groupID
    property string groupName : "model.groupName"
    property string sharedName : "model.sharedName"
    property string description : "model.description"
    //[Item properties]
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
            Column{
                spacing: 10
                width: parent.width
                Label {
                    text: "Shared ID : " + editShared.sharedID
                }
                Label {
                    text: qsTr("Shared Name :")
                }
                TextField{
                    id : editName
                    width: parent.width
                    text: editShared.sharedName
                }
                Label {
                    text: qsTr("Shared To (Email) :")
                }
                TextField{
                    id : editSharedTo
                    width: parent.width
                    text : editShared.sharedTo
                }
                Label {
                    text: qsTr("Select Group :")
                }
                ComboBox{
                    property string displayName : groupList.getItemName(editShared.groupID)
                    id : editGroup
                    textRole: "groupID"
                    displayText: displayName
                    currentIndex: groupList.getItemIndex(editShared.groupID)
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: editGroup.displayName = model.groupName
                    }
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : editDescription
                    width: parent.width
                    text : editShared.description
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id : createButton
                        text: "Edit"
                        onClicked: {
                            //void editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
                            sharedList.editShared(editShared.sharedID,editName.text,editSharedTo.text,editGroup.currentText,editDescription.text)
                            sharedList.getSharedList()
                            stackView.pop()
                        }
                        enabled: user.isOnline
                    }
                    Button{
                        id : cancelButton
                        text: "Cancel"
                        onClicked: stackView.pop()
                    }
                }
            }
        }
    }
}
