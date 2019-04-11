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

ScrollView{
    property string title: "Create New Group"
    property bool canCreate : false
    id : createNewGroup
    padding: 15
    contentWidth: -1
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: qsTr("Group Name :")
        }
        TextField{
            id : newName
            width: parent.width
        }
        Label {
            text: qsTr("Group Description :")
        }
        TextField{
            id : newDescription
            width: parent.width
        }
        Label {
            text: qsTr("Select Icon :")
        }
        ComboBox{
            property string displayName : "Select Icon"
            id : newIcon
            textRole: "iconID"
            displayText: displayName
            width: parent.width
            model: IconModel{
                list: iconList
            }
            delegate: ItemDelegate{
                width: parent.width
                icon.name : model.iconName
                text: model.iconName
                onClicked: newIcon.displayName = model.iconName
            }
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id : createButton
                text: "Create"
                onClicked: {
                    //void createNewGroup(QVariant groupName, QVariant iconID, QVariant description);
                    groupList.createNewGroup(newName.text,newIcon.currentText,newDescription.text)
                    groupList.getGroupList()
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
