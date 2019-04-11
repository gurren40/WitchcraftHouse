import QtQuick 2.9
import QtQuick.Controls 2.2
import Shared 1.0
import Group 1.0
import Pin 1.0

Page {
    property bool canCreate: true
    property int listID : 4
    //function create(){createNewShared.open()}
    function create(){stackView.push("../create/createShared.qml")}
    padding: 0
    //anchors.fill: parent
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
                        onClicked: {
                            sharedDetails.close()
                            stackView.push("../edit/editShared.qml",{
                                               sharedID : listViewElement.currentItem.sharedID,
                                               sharedTo : listViewElement.currentItem.sharedTo,
                                               sharedToName : listViewElement.currentItem.sharedToName,
                                               sharedType : listViewElement.currentItem.sharedType,
                                               groupID : listViewElement.currentItem.groupID,
                                               groupName : listViewElement.currentItem.groupName,
                                               pinUUID : listViewElement.currentItem.pinUUID,
                                               pinName : listViewElement.currentItem.pinName,
                                               sharedName : listViewElement.currentItem.sharedName,
                                               description : listViewElement.currentItem.description
                                           })
                        }
                    }
                    Button {
                        text: "Delete"
                        onClicked: {
                            sharedDetails.close()
                            deleteShared.open()
                        }
                    }
                }
            }
        }
    }

    Dialog{
        id: deleteShared
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Shared Item?"
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
            sharedList.getSharedList()
            sharedList.deleteShared(listViewElement.currentItem.sharedID)
        }
        onRejected: console.log("Cancel clicked")
    }
}


