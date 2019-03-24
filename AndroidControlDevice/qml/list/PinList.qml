import QtQuick 2.9
import QtQuick.Controls 2.2
import Pin 1.0

Page {
    anchors.fill: parent
    title: qsTr("Witchcraft House")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: PinModel{
            list: pinList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Pin %1 : ").arg(index + 1)
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


