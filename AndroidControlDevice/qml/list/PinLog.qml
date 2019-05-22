import QtQuick 2.9
import QtQuick.Controls 2.2

Page {

    header: Label {
        text: qsTr("Pin Log")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Pin Log.")
        anchors.centerIn: parent
    }
}
