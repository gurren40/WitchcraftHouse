import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Page {
    property bool canCreate: false
    title: qsTr("Settings")
    //anchors.fill: parent
    //width: parent.width
    //anchors.horizontalCenter: parent.horizontalCenter
    //anchors.verticalCenter: parent.verticalCenter
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
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
                SwitchDelegate{
                    icon.name: "default"
                    width: parent.width
                    text: qsTr("Fullscreen")
                    checked: user.isFullScreen
                    onClicked: user.isFullScreen = checked
                }
                ItemDelegate{
                    icon.name: logColumn.visible ? "expand_less" : "expand_more"
                    width: parent.width
                    text: qsTr("Delete Log Menu")
                    onClicked: logColumn.visible ? logColumn.visible = false : logColumn.visible = true
                }
                Column{
                    id : logColumn
                    width: parent.width
                    spacing: 15
                    visible: false
                    ItemDelegate{
                        width: parent.width
                        text: "Delete All Activity Log"
                        onClicked: deleteActivityDialog.open()
                    }
                    ItemDelegate{
                        width: parent.width
                        text: "Delete All Pin Log"
                        onClicked: deletePinDialog.open()
                    }
                    ItemDelegate{
                        width: parent.width
                        text: "Delete All Log"
                        onClicked: deleteAllDialog.open()
                    }
                }
            }
            Dialog{
                id: deleteActivityDialog
                title: "WARNING"
                modal: true
                anchors.centerIn: parent
                standardButtons: Dialog.Ok | Dialog.Cancel
                onAccepted: logList.deleteActivityLog()
                onRejected: console.log("Cancel clicked")
                width: parent.width * 0.7
                contentWidth: -1
                contentItem: Label{
                    width: parent.width
                    text: "Are you sure to delete all activity log?"
                }
            }
            Dialog{
                id: deletePinDialog
                title: "WARNING"
                modal: true
                anchors.centerIn: parent
                standardButtons: Dialog.Ok | Dialog.Cancel
                onAccepted: logList.deletePinLog()
                onRejected: console.log("Cancel clicked")
                width: parent.width * 0.7
                contentWidth: -1
                contentItem: Label{
                    width: parent.width
                    text: "Are you sure to delete all pin log?"
                }
            }
            Dialog{
                id: deleteAllDialog
                title: "WARNING"
                modal: true
                anchors.centerIn: parent
                standardButtons: Dialog.Ok | Dialog.Cancel
                onAccepted: logList.deleteAllLog()
                onRejected: console.log("Cancel clicked")
                width: parent.width * 0.7
                contentWidth: -1
                contentItem: Label{
                    width: parent.width
                    text: "Are you sure to delete all log?"
                }
            }
        }
    }
}
