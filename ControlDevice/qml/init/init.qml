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
        }
    }

    Shortcut {
        sequence: "Menu"
        onActivated: optionsMenu.open()
    }

    StackView {
        id: stackView
        initialItem: serverPage
        anchors.fill: parent
    }

    Flickable{
        id: serverPage
        anchors.fill: parent
        contentHeight: (theColumn.height > parent.height) ? theColumn.height : parent.height
        width: parent.width
        ScrollBar.vertical: ScrollBar { }

        Column{
            id : theColumn
            anchors.centerIn: parent
            width: parent.width
            spacing: 20
            Label{
                anchors.horizontalCenter: parent.horizontalCenter
                id: titleLabel
                text : "Witchcraft House"
            }
            TextField{
                width: parent.width * 0.8
                anchors.horizontalCenter: parent.horizontalCenter
                id: serverUrl
                placeholderText: "Site Address"
                ToolTip.text: "Please fill this field"
                ToolTip.timeout: 500
                ToolTip.visible: false
            }
            Button{
                anchors.horizontalCenter: parent.horizontalCenter
                id: okButton
                text: "OK"
                onClicked: {
                    if(serverUrl.length < 1){
                        serverUrl.ToolTip.visible = true
                    }
                    else{
                        stackView.push("./login.qml",{serverUrl : serverUrl.text})
                    }
                }
            }
        }
    }
}
