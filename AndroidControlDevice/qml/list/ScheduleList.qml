import QtQuick 2.9
import QtQuick.Controls 2.2
import Schedule 1.0
import Pin 1.0

Page {
    property int listID : 3
    function create(){createNewSchedule.open()}
    anchors.fill: parent
    title: qsTr("Schedule")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: ScheduleModel{
            list: scheduleList
        }
        footer: Text{
            height: 105
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
                    Text {
                        text: "Schedule Name\t: " + listViewElement.currentItem.scheduleName
                    }
                    Text {
                        text: "Schedule UUID\t: " + listViewElement.currentItem.scheduleUUID
                    }
                    Text {
                        text: "Pin Name\t\t: " + listViewElement.currentItem.pinName
                    }
                    Text {
                        text: "Pin UUID\t\t: " + listViewElement.currentItem.pinUUID
                    }
                    Text {
                        text: "Pin Value\t\t: " + listViewElement.currentItem.value
                    }
                    Text {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                    Text {
                        text: "CRON Syntax\t: " + listViewElement.currentItem.minute+" "+listViewElement.currentItem.hour+" "+listViewElement.currentItem.dayOfMonth+" "+listViewElement.currentItem.month+" "+listViewElement.currentItem.dayOfWeek
                    }
                    Text {
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
            id:createNewSchedule
            modal: true
            anchors.centerIn: parent
            title: "Create New Schedule"
            width: parent.width * 0.9
            height: parent.height * 0.9
            standardButtons: Dialog.Ok | Dialog.Cancel
            contentItem: ScrollView {
                clip: true
                contentWidth: -1
                Column{
                    spacing: 10
                    width: parent.width
                    Text {
                        text: qsTr("Schedule Name :")
                    }
                    TextField{
                        id : newName
                        width: parent.width
                    }
                    Text {
                        text: qsTr("Select Pin :")
                    }
                    ComboBox{
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
                    Text {
                        text: qsTr("Cron Syntax :")
                    }
                    Row{
                        spacing: 15
                        TextField{
                            id : newMinute
                            width: 40
                        }
                        TextField{
                            id : newHour
                            width: 40
                        }
                        TextField{
                            id : newDayOfMonth
                            width: 40
                        }
                        TextField{
                            id : newMonth
                            width: 40
                        }
                        TextField{
                            id : newDayOfWeek
                            width: 40
                        }
                    }
                    Text {
                        text: qsTr("Time Zone :")
                    }
                    TextField{
                        id : newTimeZone
                        width: parent.width
                    }
                    Text {
                        text: qsTr("Pin Value :")
                    }
                    TextField{
                        id : newValue
                        width: parent.width
                    }
                    Text {
                        text: qsTr("Group Description :")
                    }
                    TextField{
                        id : newDescription
                        width: parent.width
                    }
                }
            }
            onAccepted: {
                //void createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
                scheduleList.createNewSchedule(newName.text,newPin.currentText,newMinute.text,newHour.text,newDayOfMonth.text,newMonth.text,newDayOfWeek.text,newTimeZone.text,newValue.text,newDescription.text)
            }
            onRejected: console.log("Cancel clicked")
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
                    Text {
                        text: "Schedule ID : " + listViewElement.currentItem.scheduleID
                    }
                    Text {
                        text: "Schedule UUID : " + listViewElement.currentItem.scheduleUUID
                    }
                    Text {
                        text: qsTr("Schedule Name :")
                    }
                    TextField{
                        id : editName
                        width: parent.width
                        text: listViewElement.currentItem.scheduleName
                    }
                    Text {
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
                    Text {
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
                    Text {
                        text: qsTr("Time Zone :")
                    }
                    TextField{
                        id : editTimeZone
                        width: parent.width
                        text: listViewElement.currentItem.timeZone
                    }
                    Text {
                        text: qsTr("Pin Value :")
                    }
                    TextField{
                        id : editValue
                        width: parent.width
                        text: listViewElement.currentItem.value
                    }
                    Text {
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
            height: parent.height * 0.9
            standardButtons: Dialog.Ok | Dialog.Cancel
            contentItem: ScrollView {
                clip: true
                //contentWidth: -1
                Column{
                    spacing: 10
                    //width: parent.width
                    Text {
                        text: "Schedule Name\t: " + listViewElement.currentItem.scheduleName
                    }
                    Text {
                        text: "Schedule UUID\t: " + listViewElement.currentItem.scheduleUUID
                    }
                    Text {
                        text: "Pin Name\t\t: " + listViewElement.currentItem.pinName
                    }
                    Text {
                        text: "Pin UUID\t\t: " + listViewElement.currentItem.pinUUID
                    }
                    Text {
                        text: "Pin Value\t\t: " + listViewElement.currentItem.value
                    }
                    Text {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                    Text {
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


