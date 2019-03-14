import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 520
    title: qsTr("Witchcraft House")

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            //listView.currentIndex = -1
        }
    }

    StackView {
        id: stackView
        initialItem: "./login.qml"
        anchors.fill: parent
    }
}
