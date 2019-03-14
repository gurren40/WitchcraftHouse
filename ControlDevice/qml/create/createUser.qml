import QtQuick 2.9
import QtQuick.Controls 2.2

Page {

    property string server: "What Server?"
    Column{
        anchors.centerIn: parent
        spacing: 20

        Label {
            text: server
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle{
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 2
            border.width: 2
            border.color: "black"
        }

        Label {
            text: "Create New User"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField{
            placeholderText: qsTr("Username")
            id: username
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

        TextField{
            id: passwordRepeat
            placeholderText: qsTr("Repeat Password")
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
            ToolTip.text: qsTr("Password did not match")
            ToolTip.visible: false
            ToolTip.timeout: 5000
        }

        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id: createNewUser
                text: qsTr("Create New User")
                onClicked: function(){
                    messageDialog.open()
                    if((username.length < 1) || (email.length < 1) || (password.length < 1) || (passwordRepeat.length < 1)){
                        //ga usah panggil fungsi
                    }
                    else {
                        if(password.text != passwordRepeat.text){
                            passwordRepeat.ToolTip.visible = true
                        }
                        else {
                            //panggil fungsi
                        }
                    }
                }
            }

            Button{
                text: qsTr("Cancel")
                onClicked: function(){
                    stackView.pop()
                }
            }
        }
    }

    Dialog{
        id: messageDialog
        anchors.centerIn: parent
        width: ((username.length < 1) || (email.length < 1) || (password.length < 1) || (passwordRepeat.length < 1)) ? errorLabel.width * 1.2 : busyIndicator.width * 1.5
        height: ((username.length < 1) || (email.length < 1) || (password.length < 1) || (passwordRepeat.length < 1)) ? errorLabel.height * 1.5 : busyIndicator.height * 1.5

        BusyIndicator {
            id : busyIndicator
            //anchors.horizontalCenter: parent.horizontalCenter
            visible: ((username.length < 1) || (email.length < 1) || (password.length < 1) || (passwordRepeat.length < 1)) ? false : true
            anchors.centerIn: parent
        }

        Label {
            id : errorLabel
            visible: ((username.length < 1) || (email.length < 1) || (password.length < 1) || (passwordRepeat.length < 1)) ? true : false
            anchors.centerIn: parent
            text: password.text != passwordRepeat.text ? qsTr("Password did not match") : qsTr("Please fill the blank field")
        }
    }
}
