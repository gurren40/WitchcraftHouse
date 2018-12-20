import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

Page {
    anchors.fill: parent
    title: qsTr("Set Connection")

    Label {
        anchors.centerIn: parent
    }

    ColumnLayout {
        anchors.fill: parent
        topPadding: 15
        ItemDelegate {
            height: parent.height
            TextField {
                id : urlValue
                placeholderText: qsTr("Enter url")
                text: qsTr("default value")
            }
        }
        ItemDelegate {
            Button {
                text : qsTr("Luncurkan")
                onClicked: {
                    backend.setWebSocket(qsTr(urlValue.text.toString()))
                }
            }
        }
    }
}
