import QtQuick 2.9
import QtQuick.Controls 2.2
import Shared 1.0

Page {
    property int listID : 4
    anchors.fill: parent
    title: qsTr("Shared List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: SharedModel{
            list: sharedList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Shared %1 : ").arg(index + 1)
                }
                Text {
                    text: model.sharedID
                }
                Text {
                    text: model.sharedName
                }
                Text {
                    text: model.sharedTo
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


