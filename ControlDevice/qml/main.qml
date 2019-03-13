import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Witchcraft House")

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            //listView.currentIndex = -1
        }
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
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
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Device")
                width: parent.width
                onClicked: {
                    stackView.push("./list/DeviceList.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Group")
                width: parent.width
                onClicked: {
                    stackView.push("./list/GroupList.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Schedule")
                width: parent.width
                onClicked: {
                    stackView.push("./list/ScheduleList.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Shared List")
                width: parent.width
                onClicked: {
                    stackView.push("./list/SharedList.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Control Device")
                width: parent.width
                onClicked: {
                    stackView.push("./list/ControlDeviceList.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "./list/PinList.qml"
        anchors.fill: parent
    }
}
