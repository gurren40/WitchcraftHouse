import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Pin 1.0
import Icon 1.0
import Group 1.0
import PinType 1.0
import Device 1.0
import QtQuick.Controls.Material 2.12

Page{
    title: "Create New User"
    property bool canCreate : false
    id : createNewSchedule
    padding: 20

    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
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
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id : createButton
                        text: "Create"
                        onClicked: function(){
                            if(newPassword.text == newPasswordRepeat.text){
                                //void createNewUser(QVariant email, QVariant name, QVariant password);
                                user.createNewUser(newEmail.text,newName.text,newPassword.text)
                                stackView.pop()
                            }
                            else{
                                passwordMismatch.open()
                            }
                        }
                        enabled: user.isOnline
                    }
                    Button{
                        id : cancelButton
                        text: "Cancel"
                        onClicked: stackView.pop()
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
        }
    }
}

