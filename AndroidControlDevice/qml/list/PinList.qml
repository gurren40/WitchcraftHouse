import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    anchors.fill: parent
    title: qsTr("Witchcraft House")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: 20

        delegate: ItemDelegate {
            text: qsTr("Pin %1").arg(index + 1)
            width: parent.width
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


