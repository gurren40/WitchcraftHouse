import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

ScrollView {
    property string title: qsTr("Login")
    anchors.fill: parent
    width: parent.width
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    Column{
        id: settingColumn
        spacing: 20
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        ItemDelegate{
            id: serverDomainDelegate
            text: "Server Domain"
            icon.name: "chevron_right"
            width: parent.width
            onClicked : serverDialog.open()
        }
        ItemDelegate{
            id: emailDelegate
            text: "Email"
            icon.name: "chevron_right"
            width: parent.width
            onClicked: emailDialog.open()
        }
        ItemDelegate{
            id: passwordDelegate
            text: "Password"
            icon.name: "chevron_right"
            width: parent.width
            onClicked: passwordDialog.open()
        }

        ItemDelegate{
            id:buttonRowDelegate
            width: parent.width
            checkable: false
            anchors.horizontalCenter: parent.horizontalCenter
            contentItem: Row{
                id:buttonRow
                property string passwordInRow: ""
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 10
                Button{
                    id: loginButton
                    text: "Login"
                    onClicked: user.requestLoginToken(user.email,buttonRow.passwordInRow)
                }
                Button{
                    id: createNewUser
                    text: "Create New User"
                    onClicked: createNewUserDialog.open()
                }
            }
        }
    }
    Dialog{
        id: serverDialog
        title: "Server Domain"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: user.serverDomain = serverDomain.text
        onRejected: console.log("Cancel clicked")
        width: parent.width * 0.7
        contentItem: TextField{
            id:serverDomain
            width: parent.width
            text: user.serverDomain
            placeholderText: "Server Domain"
        }
    }

    Dialog{
        id: emailDialog
        title: "Email"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: user.email = email.text
        onRejected: console.log("Cancel clicked")
        width: parent.width * 0.7
        contentItem: TextField{
            id:email
            width: parent.width
            text: user.email
            placeholderText: "Email"
        }
    }

    Dialog{
        id: passwordDialog
        title: "Password"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: buttonRow.passwordInRow = password.text
        onRejected: console.log("Cancel clicked")
        width: parent.width * 0.7
        contentItem: TextField{
            id:password
            text: buttonRow.passwordInRow
            width: parent.width
            placeholderText: "Password"
            echoMode: TextInput.Password
            passwordMaskDelay: 100
        }
    }

    Dialog{
        id: createNewUserDialog
        title: "Create New User"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        //void createNewUser(QVariant email, QVariant name, QVariant password);
        onAccepted: function(){
            if(newPassword.text == newPasswordRepeat.text){
                user.createNewUser(newEmail.text,newName.text,newPassword.text)
            }
            else{
                passwordMismatch.open()
            }
        }

        onRejected: console.log("Cancel clicked")
        width: parent.width * 0.9
        height: parent.height * 0.9
        contentItem:ColumnLayout{
            spacing: 10
            clip: true
            Label{
                text: "Please set your server first"
            }

            TextField{
                id:newName
                width: parent.width
                placeholderText: "Name"
            }
            TextField{
                id:newEmail
                width: parent.width
                placeholderText: "Email"
            }
            TextField{
                id:newPassword
                width: parent.width
                echoMode: TextInput.Password
                passwordMaskDelay: 100
                placeholderText: "Password"
            }
            TextField{
                id:newPasswordRepeat
                width: parent.width
                echoMode: TextInput.Password
                passwordMaskDelay: 100
                placeholderText: "Repeat Password"
            }
        }
    }

    Dialog{
        id: passwordMismatch
        title: "Password Mismatch"
        standardButtons: Dialog.Ok
        modal: true
        anchors.centerIn: parent
    }

    ScrollBar.horizontal: ScrollBar { }
}
