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
    property string title: "Edit Device"
    property bool canCreate : false
    id : editDevice
    padding: 15
    contentWidth: -1

    //[Item properties]
    property string deviceName: "model.deviceName"
    property int deviceID: 0//model.deviceID
    property string deviceUUID: "model.deviceUUID"
    property string userName : "model.userName"
    property string deviceToken : "model.deviceToken"
    property bool isDeviceOnline : false//model.isDeviceOnline
    property string description : "model.description"
    //[Item properties]
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: "Device ID : " + editDevice.deviceID
        }
        Label {
            text: "Device UUID : " + editDevice.deviceUUID
        }
        Label {
            text: qsTr("Device Name :")
        }
        TextField{
            id : deviceName
            width: parent.width
            text: editDevice.deviceName
        }
        Label {
            text: qsTr("Device Description :")
        }
        TextField{
            id : deviceDescription
            width: parent.width
            text: editDevice.description
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id : createButton
                text: "Edit"
                onClicked: {
                    //void editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description);
                    deviceList.editDevice(editDevice.deviceID,editDevice.deviceUUID,deviceName.text,deviceDescription.text);
                    deviceList.getDeviceList()
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
