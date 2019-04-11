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

ScrollView{
    property string title: "Edit Shared"
    property bool canCreate : false
    id : editShared
    padding: 15
    contentWidth: -1
    //[Item properties]
    property int sharedID : 0//model.sharedID
    property string sharedTo : "model.sharedTo"
    property string sharedToName : "model.sharedToName"
    property bool sharedType : false//model.sharedType
    property int groupID : 0//model.groupID
    property string groupName : "model.groupName"
    property string pinUUID : "model.pinUUID"
    property string pinName : "model.pinName"
    property string sharedName : "model.sharedName"
    property string description : "model.description"
    //[Item properties]
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
            text: qsTr("Select Shared Type :")
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 15
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Group")
            }
            Switch{
                anchors.verticalCenter: parent.verticalCenter
                id : editSharedType
                checked: editShared.sharedType
            }
            Label {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Pin")
            }
        }

        Label {
            text: qsTr("Select Group or Pin :")
        }
        ComboBox{
            enabled: !editSharedType.checked
            property string displayName : "Select Group"
            id : editGroup
            textRole: "groupID"
            displayText: displayName
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
        ComboBox{
            enabled: editSharedType.checked
            property string displayName : "Select Pin"
            id : editPin
            textRole: "UUID"
            displayText: displayName
            width: parent.width
            model: PinModel{
                list: pinList
            }
            delegate: ItemDelegate{
                icon.name : model.iconName
                text: model.pinName
                onClicked: editPin.displayName = model.pinName
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
                    sharedList.editShared(editShared.sharedID,editName.text,editSharedTo.text,editSharedType.checked,editGroup.currentText,editPin.currentText,editDescription.text)
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
