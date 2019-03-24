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
}


