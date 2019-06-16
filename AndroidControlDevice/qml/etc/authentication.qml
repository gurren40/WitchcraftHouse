import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Page {
    property bool canCreate: false
    title: qsTr("Authentication")
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
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
                    id: localDomainDelegate
                    text: "Local Domain"
                    icon.name: "chevron_right"
                    width: parent.width
                    onClicked : localDialog.open()
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
                    //onClicked: createNewUserDialog.open()
                    onClicked : stackView.push("../create/createUser.qml")
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
                id: localDialog
                title: "Local Domain"
                modal: true
                anchors.centerIn: parent
                standardButtons: Dialog.Ok | Dialog.Cancel
                onAccepted: user.localDomain = localDomain.text
                onRejected: console.log("Cancel clicked")
                width: parent.width * 0.7
                contentWidth: -1
                contentItem: TextField{
                    id:localDomain
                    width: parent.width
                    text: user.localDomain
                    placeholderText: "Local Domain"
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
        }
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
}
