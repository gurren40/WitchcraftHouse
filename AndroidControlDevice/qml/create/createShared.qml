import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import QtWebView 1.1
import Pin 1.0
import Icon 1.0
import Group 1.0
import PinType 1.0
import Device 1.0
import QtQuick.Controls.Material 2.12

Page{
    title: "Create New Shared"
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
                spacing: 10
                width: parent.width
                Label {
                    text: qsTr("Shared Name :")
                }
                TextField{
                    id : newName
                    width: parent.width
                }
                Label {
                    text: qsTr("Shared To (Email) :")
                }
                TextField{
                    id : newSharedTo
                    width: parent.width
                }
                Label {
                    text: qsTr("Select Group :")
                }
                ComboBox{
                    property string displayName : "Select Group"
                    id : newGroup
                    textRole: "groupID"
                    displayText: displayName
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        width: parent.width
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: newGroup.displayName = model.groupName
                    }
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : newDescription
                    width: parent.width
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id : createButton
                        text: "Create"
                        onClicked: {
                            //void createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
                            sharedList.createNewShared(newName.text,newSharedTo.text,newGroup.currentText,newDescription.text)
                            sharedList.getSharedList()
                            stackView.pop()
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
        }
    }
}
