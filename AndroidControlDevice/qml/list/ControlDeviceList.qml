import QtQuick 2.9
import QtQuick.Controls 2.2
import ControlDevice 1.0

Page {
    property int listID : 5
    anchors.fill: parent
    title: qsTr("Devices")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: ControlDeviceModel{
            list: controlDeviceList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("ControlDevice %1 : ").arg(index + 1)
                }
                Text {
                    text: model.controlDeviceID
                }
                Text {
                    text: model.controlDeviceName
                }
                Text {
                    text: model.expireDate
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


