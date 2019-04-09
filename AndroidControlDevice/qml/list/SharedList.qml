import QtQuick 2.9
import QtQuick.Controls 2.2
import Shared 1.0
import Group 1.0
import Pin 1.0

Page {
    property bool canCreate: true
    property int listID : 4
    function create(){createNewShared.open()}
    anchors.fill: parent
    title: qsTr("Shared List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: SharedModel{
            list: sharedList
        }
        footer: Label{
            height: 90
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate {
            width: parent.width
            text: model.sharedName
            property int sharedID : model.sharedID
            property string sharedTo : model.sharedTo
            property string sharedToName : model.sharedToName
            property bool sharedType : model.sharedType
            property int groupID : model.groupID
            property string groupName : model.groupName
            property string pinUUID : model.pinUUID
            property string pinName : model.pinName
            property string sharedName : model.sharedName
            property string description : model.description
            onClicked: {
                if(listViewElement.currentIndex != index){
                    listViewElement.currentIndex = index
                }
                sharedDetails.open()
            }
        }
        ScrollBar.vertical: ScrollBar { }
    }

    Dialog {
        id : sharedDetails
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
                    text: "Shared To\t\t: " + listViewElement.currentItem.sharedToName
                }
                Label {
                    text: "Email\t\t: " + listViewElement.currentItem.sharedTo
                }
                Label {
                    text: listViewElement.currentItem.sharedType ? "Shared Type\t\t: Pin" : "Shared Type\t\t: Group"
                }
                Label {
                    visible: !listViewElement.currentItem.sharedType
                    text: "Shared Group\t\t: " + listViewElement.currentItem.groupName
                }
                Label {
                    visible: listViewElement.currentItem.sharedType
                    text: "Shared Pin\t\t: " + listViewElement.currentItem.pinName
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
                        onClicked: editShared.open()
                    }
                    Button {
                        text: "Delete"
                        onClicked: deleteShared.open()
                    }
                }
            }
        }
    }

    Dialog{
        id:createNewShared
        modal: true
        anchors.centerIn: parent
        title: "Create New Shared"
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
                    text: qsTr("Select Shared Type :")
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 15
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Group")
                    }
                    Switch{
                        anchors.verticalCenter: parent.verticalCenter
                        id : newSharedType
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Pin")
                    }
                }

                Label {
                    text: qsTr("Select Group or Pin :")
                }
                ComboBox{
                    enabled: !newSharedType.checked
                    property string displayName : "Select Group"
                    id : newGroup
                    textRole: "groupID"
                    displayText: displayName
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: newGroup.displayName = model.groupName
                    }
                }
                ComboBox{
                    enabled: newSharedType.checked
                    property string displayName : "Select Pin"
                    id : newPin
                    textRole: "UUID"
                    displayText: displayName
                    width: parent.width
                    model: PinModel{
                        list: pinList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.pinName
                        onClicked: newPin.displayName = model.pinName
                    }
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : newDescription
                    width: parent.width
                }
            }
        }
        onAccepted: {
            //void createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
            sharedList.createNewShared(newName.text,newSharedTo.text,newSharedType.checked,newGroup.currentText,newPin.currentText,newDescription.text)
        }
        onRejected: console.log("Cancel clicked")
    }

    Dialog{
        id:editShared
        modal: true
        anchors.centerIn: parent
        title: "Edit Shared"
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
                    text: "Shared ID : " + listViewElement.currentItem.sharedID
                }
                Label {
                    text: qsTr("Shared Name :")
                }
                TextField{
                    id : editName
                    width: parent.width
                    text: listViewElement.currentItem.sharedName
                }
                Label {
                    text: qsTr("Shared To (Email) :")
                }
                TextField{
                    id : editSharedTo
                    width: parent.width
                    text : listViewElement.currentItem.sharedTo
                }
                Label {
                    text: qsTr("Select Shared Type :")
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 15
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Group")
                    }
                    Switch{
                        anchors.verticalCenter: parent.verticalCenter
                        id : editSharedType
                        checked: listViewElement.currentItem.sharedType
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("Pin")
                    }
                }

                Label {
                    text: qsTr("Select Group or Pin :")
                }
                ComboBox{
                    enabled: !newSharedType.checked
                    property string displayName : "Select Group"
                    id : editGroup
                    textRole: "groupID"
                    displayText: displayName
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: editGroup.displayName = model.groupName
                    }
                }
                ComboBox{
                    enabled: newSharedType.checked
                    property string displayName : "Select Pin"
                    id : editPin
                    textRole: "UUID"
                    displayText: displayName
                    width: parent.width
                    model: PinModel{
                        list: pinList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.pinName
                        onClicked: editPin.displayName = model.pinName
                    }
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : editDescription
                    width: parent.width
                    text : listViewElement.currentItem.description
                }
            }
        }
        onAccepted: {
            //void editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
            sharedList.editShared(listViewElement.currentItem.sharedID,editName.text,editSharedTo.text,editSharedType.checked,editGroup.currentText,editPin.currentText,editDescription.text)
        }
        onRejected: console.log("Cancel clicked")
    }

    Dialog{
        id: deleteShared
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Shared Item?"
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
                    text: "Shared ID\t\t: " + listViewElement.currentItem.sharedID
                }
                Label {
                    text: "Shared To\t\t: " + listViewElement.currentItem.sharedToName
                }
                Label {
                    text: "Email\t\t: " + listViewElement.currentItem.sharedTo
                }
                Label {
                    text: listViewElement.currentItem.sharedType ? "Shared Type\t\t: Pin" : "Shared Type\t\t: Group"
                }
                Label {
                    visible: !listViewElement.currentItem.sharedType
                    text: "Shared Group\t\t: " + listViewElement.currentItem.groupName
                }
                Label {
                    visible: listViewElement.currentItem.sharedType
                    text: "Shared Pin\t\t: " + listViewElement.currentItem.pinName
                }
                Label {
                    text: "Description\t\t: " + listViewElement.currentItem.description
                }
            }
        }
        onAccepted: {
            //void deleteShared(QVariant sharedID);
            sharedList.deleteShared(listViewElement.currentItem.sharedID)
        }
        onRejected: console.log("Cancel clicked")
    }
}


