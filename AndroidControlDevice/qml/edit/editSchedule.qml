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
    property string title: "Edit Schedule"
    property bool canCreate : false
    id : editSchedule
    padding: 15
    contentWidth: -1
    //[Item properties]
    property int scheduleID : 0//model.scheduleID
    property string scheduleUUID : "model.scheduleUUID"
    property int userID : 0//model.userID
    property string userName : "model.userName"
    property int pinID : 0//model.pinID
    property string pinUUID : "model.pinUUID"
    property string pinName : "model.pinName"
    property string scheduleName : "model.scheduleName"
    property string minute : "model.minute"
    property string hour : "model.hour"
    property string dayOfMonth : "model.dayOfMonth"
    property string month : "model.month"
    property string dayOfWeek : "model.dayOfWeek"
    property string timeZone : "model.timeZone"
    property string value : "model.value"
    property string description : "model.description"
    //[Item properties]
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: "Schedule ID : " + editSchedule.scheduleID
        }
        Label {
            text: "Schedule UUID : " + editSchedule.scheduleUUID
        }
        Label {
            text: qsTr("Schedule Name :")
        }
        TextField{
            id : editName
            width: parent.width
            text: editSchedule.scheduleName
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
                text: editSchedule.minute
            }
            TextField{
                id : editHour
                width: 40
                text: editSchedule.hour
            }
            TextField{
                id : editDayOfMonth
                width: 40
                text: editSchedule.dayOfMonth
            }
            TextField{
                id : editMonth
                width: 40
                text: editSchedule.month
            }
            TextField{
                id : editDayOfWeek
                width: 40
                text: editSchedule.dayOfWeek
            }
        }
        Label {
            text: qsTr("Time Zone :")
        }
        TextField{
            id : editTimeZone
            width: parent.width
            text: editSchedule.timeZone
        }
        Label {
            text: qsTr("Pin Value :")
        }
        TextField{
            id : editValue
            width: parent.width
            text: editSchedule.value
        }
        Label {
            text: qsTr("Group Description :")
        }
        TextField{
            id : editDescription
            width: parent.width
            text: editSchedule.description
        }
        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            Button{
                id : createButton
                text: "Edit"
                onClicked: {
                    //void editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
                    scheduleList.editSchedule(editSchedule.scheduleID,editName.text,editPin.currentText,editMinute.text,editHour.text,editDayOfMonth.text,editMonth.text,editDayOfWeek.text,editTimeZone.text,editValue.text,editDescription.text)
                    scheduleList.getScheduleList()
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
