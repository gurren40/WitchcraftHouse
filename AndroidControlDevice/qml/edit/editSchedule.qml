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
    title: "Edit Schedule"
    property bool canCreate : false
    id : editSchedule
    padding: 20
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

    Timer{
        interval: 100
        onTriggered: editSchedule.loadDayOfWeek(editSchedule.dayOfWeek)
        repeat: false
        running: true
    }

    function loadDayOfWeek(thestring){
        var res = thestring.split(",")
        res.forEach(function(res){
            if(res == "1"){
                monday.checked = true;
            }
            if(res == "2"){
                tuesday.checked = true;
            }
            if(res == "3"){
                wednesday.checked = true;
            }
            if(res == "4"){
                thursday.checked = true;
            }
            if(res == "5"){
                friday.checked = true;
            }
            if(res == "6"){
                saturday.checked = true;
            }
            if(res == "7"){
                sunday.checked = true;
            }
            if(res == "*"){
                loadDayOfWeek("1,2,3,4,5,6,7");
            }
        });
    }

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
                    property string displayName : pinList.getItemName(editSchedule.pinID)
                    id : editPin
                    textRole: "UUID"
                    displayText: displayName
                    currentIndex: pinList.getItemIndex(editSchedule.pinID)
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
                        enabled : false
                    }
                    TextField{
                        id : editHour
                        width: 40
                        text: editSchedule.hour
                        enabled : false
                    }
                    TextField{
                        id : editDayOfMonth
                        width: 40
                        text: editSchedule.dayOfMonth
                        enabled : false
                    }
                    TextField{
                        id : editMonth
                        width: 40
                        text: editSchedule.month
                        enabled : false
                    }
                    TextField{
                        id : editDayOfWeek
                        width: 40
                        text: editSchedule.dayOfWeek
                        enabled : false
                        function setDayOfWeek(){
                            var theDayOfWeek = ""
                            var first = true
                            if(monday.checked){
                                theDayOfWeek = theDayOfWeek + "1"
                                first = false
                            }
                            if(tuesday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "2"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",2"
                                }
                            }
                            if(wednesday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "3"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",3"
                                }
                            }
                            if(thursday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "4"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",4"
                                }
                            }
                            if(friday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "5"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",5"
                                }
                            }
                            if(saturday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "6"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",6"
                                }
                            }
                            if(sunday.checked){
                                if(first){
                                    theDayOfWeek = theDayOfWeek + "7"
                                    first = false
                                }
                                else{
                                    theDayOfWeek = theDayOfWeek + ",7"
                                }
                            }
                            editDayOfWeek.text = theDayOfWeek
                        }
                    }
                }
                Frame{
                    padding: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    Row{
                        Column{
                            Tumbler {
                                id: hoursTumbler
                                model: 24
                                currentIndex: editHour.text
                                onCurrentIndexChanged: editHour.text = currentIndex
                            }
                        }
                        Label{
                            text: qsTr(":")
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Column{
                            Tumbler {
                                id: minutesTumbler
                                model: 60
                                currentIndex: editMinute.text
                                onCurrentIndexChanged: editMinute.text = currentIndex
                            }
                        }

                        Column{
                            CheckBox{
                                id : sunday
                                text: qsTr("Sunday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                            CheckBox{
                                id : monday
                                text: qsTr("Monday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                            CheckBox{
                                id : tuesday
                                text: qsTr("Tuesday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                            CheckBox{
                                id : wednesday
                                text: qsTr("Wednesday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                        }
                        Column{
                            CheckBox{
                                id : thursday
                                text: qsTr("Thursday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                            CheckBox{
                                id : friday
                                text: qsTr("Friday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                            CheckBox{
                                id : saturday
                                text: qsTr("Saturday")
                                onClicked: editDayOfWeek.setDayOfWeek()
                            }
                        }
                    }
                }
                Label {
                    text: qsTr("Time Zone :")
                }
                TextField{
                    id : editTimeZone
                    width: parent.width
                    text: editSchedule.timeZone
                    enabled: false
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
    }
}
