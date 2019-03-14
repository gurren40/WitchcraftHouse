import QtQuick 2.9
import QtQuick.Controls 2.2


Page{
    id:loginPage

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
                width: ((serverUrl.length < 1) || (email.length < 1) || (password.length < 1)) ? errorLabel.width * 1.2 : busyIndicator.width * 1.5
                height: ((serverUrl.length < 1) || (email.length < 1) || (password.length < 1)) ? errorLabel.height * 1.5 : busyIndicator.height * 1.5
                parent: Overlay.overlay
                id: messageDialog

                BusyIndicator {
                    id : busyIndicator
                    //anchors.horizontalCenter: parent.horizontalCenter
                    visible: ((serverUrl.length < 1) || (email.length < 1) || (password.length < 1)) ? false : true
                    anchors.centerIn: parent
                }

                Label {
                    id : errorLabel
                    visible: ((serverUrl.length < 1) || (email.length < 1) || (password.length < 1)) ? true : false
                    anchors.centerIn: parent
                    text: qsTr("Please fill the blank field")
                }
            }

            Column {
                anchors.centerIn: parent
                spacing: 20

                Label {
                    text: qsTr("WITCHCRAFT HOUSE")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField{
                    placeholderText: qsTr("Server")
                    id: serverUrl
                    anchors.horizontalCenter: parent.horizontalCenter
                    ToolTip.timeout: 5000
                    ToolTip.visible: false
                    ToolTip.text: "Please fill this server field"
                }

                Label {
                    text: qsTr("Please Login or create new Account to continue")
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                TextField{
                    placeholderText: qsTr("Email")
                    id: email
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
                        id: loginButton
                        text: qsTr("Login")
                        onClicked: function(){
                            messageDialog.open()
                            if((serverUrl.length < 1) || (email.length < 1) || (password.length < 1)){
                                //lol
                            }
                            else{
                                //lol
                            }
                        }
                    }

                    Button{
                        text: qsTr("Create New Account")
                        onClicked: function(){
                            if(serverUrl.length < 1){
                                serverUrl.ToolTip.visible = true
                            }
                            else {
                                stackView.push("./../create/createUser.qml",{server:serverUrl.text})
                            }
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
        }
    }
    Shortcut {
        sequence: "Return"
        //enabled: stackView.depth > 1
        onActivated: {
            messageDialog.open()
        }
    }
}

