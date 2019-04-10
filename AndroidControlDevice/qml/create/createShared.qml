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
    property string title: "Create New Schedule"
    property bool canCreate : false
    id : createNewSchedule
    padding: 15
    contentWidth: -1
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: qsTr("Shared Name :")
        }
        TextField{
            id : newName
            width: parent.width
        }
        Label {
            text: qsTr("Shared To (Email) :")
        }
        TextField{
            id : newSharedTo
            width: parent.width
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
                id : newSharedType
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
            enabled: !newSharedType.checked
            property string displayName : "Select Group"
            id : newGroup
            textRole: "groupID"
            displayText: displayName
            width: parent.width
            model: GroupModel{
                list: groupList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.groupName
                onClicked: newGroup.displayName = model.groupName
            }
        }
        ComboBox{
            enabled: newSharedType.checked
            property string displayName : "Select Pin"
            id : newPin
            textRole: "UUID"
            displayText: displayName
            width: parent.width
            model: PinModel{
                list: pinList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.pinName
                onClicked: newPin.displayName = model.pinName
            }
        }
        Label {
            text: qsTr("Description :")
        }
        TextField{
            id : newDescription
            width: parent.width
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id : createButton
                text: "Create"
                onClicked: {
                    //void createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
                    sharedList.createNewShared(newName.text,newSharedTo.text,newSharedType.checked,newGroup.currentText,newPin.currentText,newDescription.text)
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
