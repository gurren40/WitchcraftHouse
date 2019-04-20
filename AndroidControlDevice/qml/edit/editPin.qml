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
    property string title: "Edit Pin"
    property bool canCreate : false
    id : editPin
    padding: 15
    contentWidth: -1
    //[Item properties]
    property int pinID : 0//model.pinID
    property string uuid : "model.UUID"
    property int userID : 0//model.userID
    property string userName : "model.userName"
    property int groupID : 0//model.groupID
    property string groupName : "model.groupName"
    property int deviceID : 0//model.deviceID
    property string deviceName : "model.deviceName"
    property int iconID : 0//model.iconID
    property string iconName : "model.iconName"
    property int pinTypeID : 0//model.pinTypeID
    property string pinTypeName : "model.pinTypeName"
    property string pinName : "model.pinName"
    property string value : "model.value"
    property string option : "model.option"
    property string description : "model.description"
    //[Item properties]
    Column{
        width: parent.width
        anchors.centerIn: parent
        spacing: 5
        Label {
            id:pinID
            text: "Pin ID : " + editPin.pinID
        }
        Label {
            id:uuid
            text: "Pin UUID : " + editPin.uuid
        }
        Label {
            text: qsTr("Pin Name :")
        }
        TextField{
            id : pinName
            width: parent.width
            text: editPin.pinName
        }
        Label {
            text: qsTr("Select Group :")
        }
        ComboBox{
            property string displayName: groupList.getItemName(editPin.groupID)
            id : group
            textRole: "groupID"
            displayText: displayName
            currentIndex: groupList.getItemIndex(editPin.groupID)
            width: parent.width
            model: GroupModel{
                list: groupList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.groupName
                onClicked: group.displayName = model.groupName
            }
        }
        Label {
            text: qsTr("Select Device :")
        }
        ComboBox{
            property string displayName : deviceList.getItemName(editPin.deviceID)
            id : device
            textRole: "deviceID"
            displayText: displayName
            width: parent.width
            currentIndex : deviceList.getItemIndex(editPin.deviceID)
            model: DeviceModel{
                list: deviceList
            }
            delegate: ItemDelegate{
                width: parent.width
                text: model.deviceName
                onClicked: device.displayName = model.deviceName
            }
        }
        Label {
            text: qsTr("Select Icon :")
        }
        ComboBox{
            property string displayName : editPin.iconName
            id : editIcon
            textRole: "iconID"
            displayText: displayName
            currentIndex: editPin.iconID
            width: parent.width
            model: IconModel{
                list: iconList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.iconName
                onClicked: editIcon.displayName = model.iconName
            }
        }
        Label {
            text: qsTr("Select Pin Type :")
        }
        ComboBox{
            property string displayName : editPin.pinTypeName
            id : pinType
            textRole: "pinTypeID"
            displayText: displayName
            currentIndex: editPin.pinTypeID
            width: parent.width
            model: PinTypeModel{
                list: pinTypeList
            }
            delegate: ItemDelegate{
                width: parent.width
                text: model.pinTypeName
                onClicked: pinType.displayName = model.pinTypeName
            }
        }
        Label {
            text: qsTr("New Value :")
        }
        TextField{
            id : value
            width: parent.width
            text: editPin.value
        }
        Label {
            text: qsTr("Options :")
        }
        TextField{
            id : option
            width: parent.width
            text: editPin.option
        }
        Label {
            text: qsTr("Description :")
        }
        TextField{
            id : description
            width: parent.width
            text: editPin.description
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id : createButton
                text: "Edit"
                onClicked: {
                    //void editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
                    pinList.editPin(editPin.pinID,editPin.uuid,pinName.text,group.currentText,device.currentText,editIcon.currentText,pinType.currentText,value.text,option.text,description.text)
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
