import QtQuick 2.9
import QtQuick.Controls 2.2
import Pin 1.0

Page {
    property bool canCreate: false
    property int listID : 6
    padding: 0
    //anchors.fill: parent
    title: qsTr("Shared Pin List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: PinModel{
            list: sharedPinList
        }
        footer: Label{
            height: 90
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Label {
                    text: qsTr("Shared Pin %1 : ").arg(index + 1)
                }
                Label {
                    text: model.pinID
                }
                Label {
                    text: model.pinName
                }
                Label {
                    text: model.value
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


