import QtQuick 2.9
import QtQuick.Controls 2.2
import Pin 1.0

Page {
    property int listID : 6
    anchors.fill: parent
    title: qsTr("Shared Pin List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: PinModel{
            list: sharedPinList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Shared Pin %1 : ").arg(index + 1)
                }
                Text {
                    text: model.pinID
                }
                Text {
                    text: model.pinName
                }
                Text {
                    text: model.value
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


