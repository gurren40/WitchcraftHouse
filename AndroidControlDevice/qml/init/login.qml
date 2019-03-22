import QtQuick 2.9
import QtQuick.Controls 2.2




Flickable{
    id : login
    property string title: qsTr("Login")
    property string serverUrl: qsTr("")
    width: parent.width
    contentHeight: (theColumn.height > parent.height) ? theColumn.height : parent.height
    ScrollBar.vertical: ScrollBar { }

    Dialog {
        anchors.centerIn: parent
        width: ((email.length < 1) || (password.length < 1)) ? errorLabel.width * 1.2 : busyIndicator.width * 1.5
        height: ((email.length < 1) || (password.length < 1)) ? errorLabel.height * 1.5 : busyIndicator.height * 1.5
        parent: Overlay.overlay
        id: messageDialog

        BusyIndicator {
            id : busyIndicator
            //anchors.horizontalCenter: parent.horizontalCenter
            visible: ((email.length < 1) || (password.length < 1)) ? false : true
            anchors.centerIn: parent
        }

        Label {
            id : errorLabel
            visible: ((email.length < 1) || (password.length < 1)) ? true : false
            anchors.centerIn: parent
            text: qsTr("Please fill the blank field")
        }
    }

    Column {
        id : theColumn
        anchors.centerIn: parent
        width: parent.width
        spacing: 20

        Label {
            text: qsTr("WITCHCRAFT HOUSE")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label{
            //placeholderText: qsTr("Server")
            anchors.horizontalCenter: parent.horizontalCenter
            text: serverUrl
        }

        Label {
            text: qsTr("Please Login or create new Account to continue")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField{
            width: parent.width * 0.8
            placeholderText: qsTr("Email")
            id: email
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField{
            id: password
            width: parent.width * 0.8
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
                    if((email.length < 1) || (password.length < 1)){
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
                    stackView.push("./../create/createUser.qml",{serverUrl:serverUrl})
                }
            }
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


