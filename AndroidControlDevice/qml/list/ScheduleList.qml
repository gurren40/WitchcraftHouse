import QtQuick 2.9
import QtQuick.Controls 2.2
import Schedule 1.0
import Pin 1.0

Page {
    property bool canCreate: true
    property int listID : 3
    //function create(){createNewSchedule.open()}
    function create(){stackView.push("../create/createSchedule.qml")}
    padding: 0
    //anchors.fill: parent
    title: qsTr("Schedule")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: ScheduleModel{
            list: scheduleList
        }
        footer: Label{
            height: 90
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate {
            property int scheduleID : model.scheduleID
            property string scheduleUUID : model.scheduleUUID
            property int userID : model.userID
            property string userName : model.userName
            property int pinID : model.pinID
            property string pinUUID : model.pinUUID
            property string pinName : model.pinName
            property string scheduleName : model.scheduleName
            property string minute : model.minute
            property string hour : model.hour
            property string dayOfMonth : model.dayOfMonth
            property string month : model.month
            property string dayOfWeek : model.dayOfWeek
            property string timeZone : model.timeZone
            property string value : model.value
            property string description : model.description

            width: parent.width
            text : model.scheduleName + " ("+model.minute+" "+model.hour+" "+model.dayOfMonth+" "+model.month+" "+model.dayOfWeek+") : "+model.value
            onClicked: {
                if(listViewElement.currentIndex != index){
                    listViewElement.currentIndex = index
                }
                scheduleDetails.open()
            }
        }

        Dialog {
            id : scheduleDetails
            width: parent.width * 0.9
            height: parent.height * 0.9
            modal: true
            anchors.centerIn: parent
            title: "Schedule Details"
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
                        text: "Schedule Name\t: " + listViewElement.currentItem.scheduleName
                    }
                    Label {
                        text: "Schedule UUID\t: " + listViewElement.currentItem.scheduleUUID
                    }
                    Label {
                        text: "Pin Name\t\t: " + listViewElement.currentItem.pinName
                    }
                    Label {
                        text: "Pin UUID\t\t: " + listViewElement.currentItem.pinUUID
                    }
                    Label {
                        text: "Pin Value\t\t: " + listViewElement.currentItem.value
                    }
                    Label {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                    Label {
                        text: "CRON Syntax\t: " + listViewElement.currentItem.minute+" "+listViewElement.currentItem.hour+" "+listViewElement.currentItem.dayOfMonth+" "+listViewElement.currentItem.month+" "+listViewElement.currentItem.dayOfWeek
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
                            onClicked: editSchedule.open()
                        }
                        Button {
                            text: "Delete"
                            onClicked: deleteSchedule.open()
                        }
                    }
                }
            }
        }

        Dialog{
            id:editSchedule
            modal: true
            anchors.centerIn: parent
            title: "Edit Schedule"
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
                        text: "Schedule ID : " + listViewElement.currentItem.scheduleID
                    }
                    Label {
                        text: "Schedule UUID : " + listViewElement.currentItem.scheduleUUID
                    }
                    Label {
                        text: qsTr("Schedule Name :")
                    }
                    TextField{
                        id : editName
                        width: parent.width
                        text: listViewElement.currentItem.scheduleName
                    }
                    Label {
                        text: qsTr("Select Pin :")
                    }
                    ComboBox{
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
                        text: qsTr("Cron Syntax :")
                    }
                    Row{
                        spacing: 15
                        TextField{
                            id : editMinute
                            width: 40
                            text: listViewElement.currentItem.minute
                        }
                        TextField{
                            id : editHour
                            width: 40
                            text: listViewElement.currentItem.hour
                        }
                        TextField{
                            id : editDayOfMonth
                            width: 40
                            text: listViewElement.currentItem.dayOfMonth
                        }
                        TextField{
                            id : editMonth
                            width: 40
                            text: listViewElement.currentItem.month
                        }
                        TextField{
                            id : editDayOfWeek
                            width: 40
                            text: listViewElement.currentItem.dayOfWeek
                        }
                    }
                    Label {
                        text: qsTr("Time Zone :")
                    }
                    TextField{
                        id : editTimeZone
                        width: parent.width
                        text: listViewElement.currentItem.timeZone
                    }
                    Label {
                        text: qsTr("Pin Value :")
                    }
                    TextField{
                        id : editValue
                        width: parent.width
                        text: listViewElement.currentItem.value
                    }
                    Label {
                        text: qsTr("Group Description :")
                    }
                    TextField{
                        id : editDescription
                        width: parent.width
                        text: listViewElement.currentItem.description
                    }
                }
            }
            onAccepted: {
                //void editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
                scheduleList.editSchedule(listViewElement.currentItem.scheduleID,editName.text,editPin.currentText,editMinute.text,editHour.text,editDayOfMonth.text,editMonth.text,editDayOfWeek.text,editTimeZone.text,editValue.text,editDescription.text)
            }
            onRejected: console.log("Cancel clicked")
        }

        Dialog{
            id: deleteSchedule
            modal: true
            anchors.centerIn: parent
            title: "Are you sure want to delete this Schedule?"
            width: parent.width * 0.9
            //height: parent.height * 0.9
            standardButtons: Dialog.Ok | Dialog.Cancel
            contentItem: ScrollView {
                clip: true
                //contentWidth: -1
                Column{
                    spacing: 10
                    //width: parent.width
                    Label {
                        text: "Schedule Name\t: " + listViewElement.currentItem.scheduleName
                    }
                    Label {
                        text: "Schedule UUID\t: " + listViewElement.currentItem.scheduleUUID
                    }
                    Label {
                        text: "Pin Name\t\t: " + listViewElement.currentItem.pinName
                    }
                    Label {
                        text: "Pin UUID\t\t: " + listViewElement.currentItem.pinUUID
                    }
                    Label {
                        text: "Pin Value\t\t: " + listViewElement.currentItem.value
                    }
                    Label {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                    Label {
                        text: "CRON Syntax\t: " + listViewElement.currentItem.minute+" "+listViewElement.currentItem.hour+" "+listViewElement.currentItem.dayOfMonth+" "+listViewElement.currentItem.month+" "+listViewElement.currentItem.dayOfWeek
                    }
                }
            }
            onAccepted: {
                //void deleteSchedule(QVariant scheduleID);
                scheduleList.deleteSchedule(listViewElement.currentItem.scheduleID);
            }
            onRejected: console.log("Cancel clicked")
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


