import QtQuick 2.9
import QtQuick.Controls 2.2
import Device 1.0

Page {
    anchors.fill: parent
    title: qsTr("Devices")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: DeviceModel{
            list: deviceList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Device %1 : ").arg(index + 1)
                }
                Text {
                    text: model.deviceID
                }
                Text {
                    text: model.deviceName
                }
                Text {
                    text: model.deviceToken
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
    RoundButton {
        id: createNewDeviceButton
        text: qsTr("+")
        highlighted: true
        anchors.margins: 15
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: toolBar.height * 1.5
        width: toolBar.height * 1.5
        font.pointSize: 35
        onClicked: createNewDevice.open()
    }
    Dialog{
        id:createNewDevice
        modal: true
        anchors.centerIn: parent
        title: "Create New Device"
        width: parent.width * 0.9
        height: parent.height * 0.9
        standardButtons: Dialog.Ok | Dialog.Cancel
        contentItem: ScrollView {
            clip: true
            Column{
                spacing: 10
                Text {
                    text: qsTr("Device Name :")
                }
                TextField{
                    id : newName
                    width: parent.width
                }
                Text {
                    text: qsTr("Device Description :")
                }
                TextField{
                    id : newDescription
                    width: parent.width
                }
            }
        }

        onAccepted: {
            //deviceList.createNewDevice(QVariant deviceName, QVariant description);
            deviceList.createNewDevice(newName.text,newDescription.text);
        }
        onRejected: console.log("Cancel clicked")
    }
}


