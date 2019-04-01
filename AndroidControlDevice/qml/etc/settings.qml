import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

ScrollView {
    property string title: qsTr("Settings")
    anchors.fill: parent
    width: parent.width
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    Column{
        id: settingColumn
        spacing: 15
        width: parent.width
        ItemDelegate{
            icon.name : "chevron_right"
            width: parent.width
            text: qsTr("Login")
            onClicked: stackView.push("./login.qml")
        }
        ItemDelegate{
            icon.name: statusColumn.visible ? "expand_less" : "expand_more"
            width: parent.width
            text: qsTr("Show Device Status")
            onClicked: statusColumn.visible ? statusColumn.visible = false : statusColumn.visible = true
        }
        Column{
            id : statusColumn
            width: parent.width
            spacing: 15
            visible: false
            ItemDelegate{
                id : deviceModel
                width: parent.width
                text: "Device Model : " + user.thisDeviceModel
            }
            ItemDelegate{
                width: parent.width
                text: user.isOnline ? qsTr("Status : Online") : qsTr("Status : Offline")
            }
            ItemDelegate{
                width: parent.width
                text: user.isLoggedIn ? qsTr("Login : Logged In") : qsTr("Login : Logged Out")
            }
            ItemDelegate{
                width: parent.width
                text: "Token : " + user.jwt
            }
        }
        ItemDelegate{
            icon.name: "chevron_right"
            width: parent.width
            text: qsTr("Log Out")
            onClicked: logOutDialog.open()
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

    ScrollBar.horizontal: ScrollBar { }
}
