import QtQuick 2.9
import QtQuick.Controls 2.2
import Group 1.0
import Icon 1.0

Page {
    property bool canCreate: true
    property int listID : 2
    padding: 0
    //function create(){createNewGroup.open()}
    function create(){stackView.push("../create/createGroup.qml")}
    //anchors.fill: parent
    title: qsTr("Group List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: GroupModel{
            list: groupList
        }
        footer: Label{
            height: 90
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate {
            property int groupID : model.groupID
            property int userID : model.userID
            property string userName : model.userName
            property int iconID : model.iconID
            property string iconName : model.iconName
            property string groupName : model.groupName
            property string description : model.description
            width: parent.width
            icon.name : iconName
            text: groupName
            onClicked: {
                if(listViewElement.currentIndex != index){
                    listViewElement.currentIndex = index
                }
                groupDetails.open()
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }

    Dialog {
        id : groupDetails
        width: parent.width * 0.9
        height: parent.height * 0.9
        modal: true
        anchors.centerIn: parent
        title: "Group Details"
        standardButtons: Dialog.Close
        contentItem: ScrollView {
            width: parent.width
            clip: true
            //contentWidth: parent.width
            anchors.centerIn: parent
            Column {
                //width: parent.width
                anchors.centerIn: parent
                spacing: 10
                Label {
                    text: "Group Name\t\t: " + listViewElement.currentItem.groupName
                }
                Label {
                    text: "Group Icon\t\t: " + listViewElement.currentItem.iconName
                }
                Label {
                    text: "Description\t\t: " + listViewElement.currentItem.description
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    spacing: 10
                    Button {
                        text: "Edit"
                        onClicked: editGroup.open()
                    }
                    Button {
                        text: "Delete"
                        onClicked: deleteGroup.open()
                    }
                }
            }
        }
    }

    Dialog{
        id: editGroup
        modal: true
        anchors.centerIn: parent
        title: "Edit Group"
        width: parent.width * 0.9
        height: parent.height * 0.9
        standardButtons: Dialog.Ok | Dialog.Cancel
        contentItem: ScrollView {
            clip: true
            contentWidth: -1
            Column{
                spacing: 10
                width: parent.width
                Label {
                    text: "Group ID : " + listViewElement.currentItem.groupID
                }
                Label {
                    text: qsTr("Group Name :")
                }
                TextField{
                    id : groupName
                    width: parent.width
                    text: listViewElement.currentItem.groupName
                }
                Label {
                    text: qsTr("Group Description :")
                }
                TextField{
                    id : description
                    width: parent.width
                    text: listViewElement.currentItem.description
                }
                Label {
                    text: qsTr("Select Icon :")
                }
                ComboBox{
                    property string displayName : "Must Select New Icon"
                    id : groupIcon
                    textRole: "iconID"
                    displayText: displayName
                    width: parent.width
                    model: IconModel{
                        list: iconList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.iconName
                        onClicked: groupIcon.displayName = model.iconName
                    }
                }
            }
        }
        onAccepted: {
            //void editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description);
            groupList.editGroup(listViewElement.currentItem.groupID,groupName.text,groupIcon.currentText,description.text)
            console.log(listViewElement.currentItem.groupID+" "+groupName.text+" "+groupIcon.currentText+" "+description.text)
        }
        onRejected: console.log("Cancel clicked")
    }

    Dialog{
        id: deleteGroup
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Group?"
        width: parent.width * 0.9
        //height: parent.height * 0.9
        standardButtons: Dialog.Ok | Dialog.Cancel
        contentItem: ScrollView {
            clip: true
            contentWidth: -1
            Column{
                spacing: 10
                width: parent.width
                Label {
                    text: "Group ID : " + listViewElement.currentItem.groupID
                }
                Label {
                    text: "Group Name : " + listViewElement.currentItem.groupName
                }
            }
        }
        onAccepted: {
            //void deleteGroup(QVariant groupID);
            groupList.deleteGroup(listViewElement.currentItem.groupID);
        }
        onRejected: console.log("Cancel clicked")
    }
}


