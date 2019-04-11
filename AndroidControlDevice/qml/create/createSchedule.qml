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
    property string title: "Create New Schedule"
    property bool canCreate : false
    id : createNewSchedule
    padding: 15
    contentWidth: -1
    Column{
        spacing: 10
        width: parent.width
        Label {
            text: qsTr("Schedule Name :")
        }
        TextField{
            id : newName
            width: parent.width
        }
        Label {
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
                width: parent.width
                icon.name : model.iconName
                text: model.pinName
                onClicked: newPin.displayName = model.pinName
            }
        }
        Label {
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
        Label {
            text: qsTr("Time Zone :")
        }
        TextField{
            id : newTimeZone
            width: parent.width
        }
        Label {
            text: qsTr("Pin Value :")
        }
        TextField{
            id : newValue
            width: parent.width
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
                    //void createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
                    scheduleList.createNewSchedule(newName.text,newPin.currentText,newMinute.text,newHour.text,newDayOfMonth.text,newMonth.text,newDayOfWeek.text,newTimeZone.text,newValue.text,newDescription.text)
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
