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
    property string title: "Create New Device"
    property bool canCreate : false
    id : createNewDevice
    padding: 15
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: qsTr("Device Name :")
        }
        TextField{
            id : newName
            width: parent.width
        }
        Label {
            text: qsTr("Device Description :")
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
                    //deviceList.createNewDevice(QVariant deviceName, QVariant description);
                    deviceList.createNewDevice(newName.text,newDescription.text);
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
