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
    title: "Edit Group"
    property bool canCreate : false
    id : editGroup
    padding: 20
    //[Item Properties]
    property int groupID : 0//model.groupID
    property int userID : 0//model.userID
    property string userName : "model.userName"
    property int iconID : 0//model.iconID
    property string iconName : "model.iconName"
    property string groupName : "model.groupName"
    property string description : "model.description"
    //[Item Properties]
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
                    text: "Group ID : " + editGroup.groupID
                }
                Label {
                    text: qsTr("Group Name :")
                }
                TextField{
                    id : groupName
                    width: parent.width
                    text: editGroup.groupName
                }
                Label {
                    text: qsTr("Group Description :")
                }
                TextField{
                    id : description
                    width: parent.width
                    text: editGroup.description
                }
                Label {
                    text: qsTr("Select Icon :")
                }
                ComboBox{
                    property string displayName : editGroup.iconName
                    id : groupIcon
                    textRole: "iconID"
                    displayText: displayName
                    width: parent.width
                    currentIndex : editGroup.iconID

                    model: IconModel{
                        id : iconModel
                        list: iconList
                    }
                    delegate: ItemDelegate{
                        width: parent.width
                        icon.name : model.iconName
                        text: model.iconName
                        onClicked: groupIcon.displayName = model.iconName
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id : createButton
                        text: "Edit"
                        onClicked: {
                            //void editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description);
                            groupList.editGroup(editGroup.groupID,groupName.text,groupIcon.currentText,description.text)
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
    }
}
