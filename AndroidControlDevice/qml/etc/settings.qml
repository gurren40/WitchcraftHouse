import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

ScrollView {
    property bool canCreate: false
    property string title: qsTr("Settings")
    //anchors.fill: parent
    //width: parent.width
    //anchors.horizontalCenter: parent.horizontalCenter
    //anchors.verticalCenter: parent.verticalCenter
    Column{
        id: settingColumn
        spacing: 15
        width: parent.width
        ItemDelegate{
            icon.name : "chevron_right"
            width: parent.width
            text: qsTr("Authentication")
            onClicked: stackView.push("./authentication.qml")
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
                id : pingPong
                width: parent.width
                text: "Last Ping Speed : " + user.pong + " ms"
            }
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
                //text: "Token : " + user.jwt
                contentItem: ColumnLayout{
                    Label{
                        text: "Token :"
                    }
                    TextArea{
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: user.jwt
                        //enabled: false
                    }
                }
            }
        }
        SwitchDelegate{
            icon.name: "default"
            width: parent.width
            text: qsTr("Dark Theme")
            checked: user.darkTheme
            onClicked: user.darkTheme = checked
        }
    }
    ScrollBar.horizontal: ScrollBar { }
}
