import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.3
import Device 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Witchcraft House")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u268C"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
        ToolButton{
            text: "\u27f3"
            anchors.right : parent.right
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                backend.initDevicesValue()
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent
            topPadding: 15

            ItemDelegate {
                text:qsTr("Reload")
                onClicked: {
                    backend.initDevicesValue()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "Devices.qml"
        anchors.fill: parent
    }
}
