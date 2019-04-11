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
    property string title: "Create New Pin"
    property bool canCreate : false
    id : createNewPin
    padding: 15
    //width: parent.width
    //clip: true
    contentWidth: -1
    Column{
        width: parent.width
        anchors.centerIn: parent
        spacing: 5
        //padding: 15
        Label {
            text: qsTr("Pin Name :")
        }
        TextField{
            id : newPinName
            width: parent.width
        }
        Label {
            text: qsTr("Select Group :")
        }
        ComboBox{
            property string displayName: "Select Group"
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
        Label {
            text: qsTr("Select Device :")
        }
        ComboBox{
            property string displayName : "Select Device"
            id : newDevice
            textRole: "deviceID"
            displayText: displayName
            width: parent.width
            model: DeviceModel{
                list: deviceList
            }
            delegate: ItemDelegate{
                width: parent.width
                text: model.deviceName
                onClicked: newDevice.displayName = model.deviceName
            }
        }
        Label {
            text: qsTr("Select Icon :")
        }
        ComboBox{
            property string displayName : "Select Icon"
            id : newIcon
            textRole: "iconID"
            displayText: displayName
            width: parent.width
            model: IconModel{
                list: iconList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.iconName
                onClicked: newIcon.displayName = model.iconName
            }
        }
        Label {
            text: qsTr("Select Pin Type :")
        }
        ComboBox{
            property string displayName : "Select Pin Type"
            id : newPinType
            textRole: "pinTypeID"
            displayText: displayName
            width: parent.width
            model: PinTypeModel{
                list: pinTypeList
            }
            delegate: ItemDelegate{
                width: parent.width
                text: model.pinTypeName
                onClicked: newPinType.displayName = model.pinTypeName
            }
        }
        Label {
            text: qsTr("Initial Value :")
        }
        TextField{
            id : newValue
            width: parent.width
        }
        Label {
            text: qsTr("Options :")
        }
        TextField{
            id : newOption
            width: parent.width
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
                    //void createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
                    pinList.createNewPin(newPinName.text,newGroup.currentText,newDevice.currentText,newIcon.currentText,newPinType.currentText,newValue.text,newOption.text,newDescription.text)
                    pinList.getPinList()
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
