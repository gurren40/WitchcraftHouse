import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

ScrollView {
    property bool canCreate: false
    property string title: qsTr("Authentication")
    anchors.fill: parent
    width: parent.width
    contentWidth: -1
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
            enabled: !user.isLoggedIn
            id: loginDelegate
            text: "Login"
            icon.name: "chevron_right"
            width: parent.width
            onClicked: loginDialog.open()
        }
        ItemDelegate{
            enabled: !user.isLoggedIn
            id: createNewUserDelegate
            text: "Create New User"
            icon.name: "chevron_right"
            width: parent.width
            onClicked: createNewUserDialog.open()
        }
        ItemDelegate{
            enabled: user.isLoggedIn
            icon.name: "chevron_right"
            width: parent.width
            text: qsTr("Log Out")
            onClicked: logOutDialog.open()
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
        contentWidth: -1
        contentItem: TextField{
            id:serverDomain
            width: parent.width
            text: user.serverDomain
            placeholderText: "Server Domain"
        }
    }

    Dialog{
        id: loginDialog
        title: "Login"
        modal: true
        anchors.centerIn: parent
        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            user.email = email.text
            user.requestLoginToken(email.text,password.text)
        }
        onRejected: console.log("Cancel clicked")
        width: parent.width * 0.7
        height: parent.width * 0.7
        contentItem: ScrollView{
            anchors.centerIn: parent
            width: parent.width
            clip: true
            contentWidth: -1
            Column{
                anchors.centerIn: parent
                width: parent.width
                clip: true
                spacing: 10
                TextField{
                    id:email
                    width: parent.width
                    text: user.email
                    placeholderText: "Email"
                }
                TextField{
                    id:password
                    width: parent.width
                    placeholderText: "Password"
                    echoMode: TextInput.Password
                    passwordMaskDelay: 100
                }
            }
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
        contentItem: ScrollView {
            anchors.centerIn: parent
            width: parent.width
            clip: true
            contentWidth: -1
            Column{
                spacing: 15
                clip: true
                width: parent.width
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
    }

    Dialog{
        id: passwordMismatch
        title: "Password Mismatch"
        standardButtons: Dialog.Ok
        modal: true
        anchors.centerIn: parent
    }
    Dialog{
        id: logOutDialog
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to Log Out?"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            user.logOut()
        }
        onRejected: console.log("Cancel clicked")
    }

    ScrollBar.horizontal: ScrollBar { }
}
