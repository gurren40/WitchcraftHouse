import QtQuick 2.9
import QtQuick.Controls 2.2


Page{

    property bool toolBarVisibility: false
    header: ToolBar {
        id: toolBar
        contentHeight: toolButton.implicitHeight
        visible: toolBarVisibility

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : ""
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                    toolBarVisibility = false
                }
                else {
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: login

        Pane{

            id : login
            property string title: qsTr("Login")
            //title: qsTr("Login")
            anchors.fill: parent

            Dialog {
                anchors.centerIn: parent
                id: messageDialog

                BusyIndicator {
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Column {
                anchors.centerIn: parent
                spacing: 20

                Label {
                    text: qsTr("Please login to continue")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField{
                    placeholderText: qsTr("Server")
                    id: serverUrl
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField{
                    placeholderText: qsTr("Email")
                    id: username
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField{
                    id: password
                    placeholderText: qsTr("Password")
                    echoMode: TextInput.Password
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        text: qsTr("Login")
                        onClicked: messageDialog.open()
                    }

                    Button{
                        text: qsTr("Create New Account")
                        onClicked: function(){
                            stackView.push("./../create/createUser.qml")
                            toolBarVisibility = true
                        }
                    }
                }
            }
        }
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            toolBarVisibility = false
        }
    }
}

