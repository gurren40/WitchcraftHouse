import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
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

    ColumnLayout {
        id: column
        spacing: 40
        anchors.fill: parent
        ListView{
            id:listViewElement
            //anchors.fill: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
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
                //text : model.scheduleName + " ("+model.minute+" "+model.hour+" "+model.dayOfMonth+" "+model.month+" "+model.dayOfWeek+") : "+model.value
                contentItem: Column{
                    width: parent.width
                    spacing: 2
                    Label{
                        text: model.scheduleName
                        font.bold: true
                    }
                    Label{
                        font.bold: false
                        font.pointSize: 10
                        text : " ("+model.minute+" "+model.hour+" "+model.dayOfMonth+" "+model.month+" "+model.dayOfWeek+")"
                        enabled: false
                    }
                }

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
                                onClicked: {
                                    scheduleDetails.close()
                                    stackView.push("../edit/editSchedule.qml",{
                                                       scheduleID : listViewElement.currentItem.scheduleID,
                                                       scheduleUUID : listViewElement.currentItem.scheduleUUID,
                                                       userID : listViewElement.currentItem.userID,
                                                       userName : listViewElement.currentItem.userName,
                                                       pinID : listViewElement.currentItem.pinID,
                                                       pinUUID : listViewElement.currentItem.pinUUID,
                                                       pinName : listViewElement.currentItem.pinName,
                                                       scheduleName : listViewElement.currentItem.scheduleName,
                                                       minute : listViewElement.currentItem.minute,
                                                       hour : listViewElement.currentItem.hour,
                                                       dayOfMonth : listViewElement.currentItem.dayOfMonth,
                                                       month : listViewElement.currentItem.month,
                                                       dayOfWeek : listViewElement.currentItem.dayOfWeek,
                                                       timeZone : listViewElement.currentItem.timeZone,
                                                       value : listViewElement.currentItem.value,
                                                       description : listViewElement.currentItem.description
                                                   })
                                }
                            }
                            Button {
                                text: "Delete"
                                onClicked: {
                                    scheduleDetails.close()
                                    deleteSchedule.open()
                                }
                            }
                        }
                    }
                }
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
                    scheduleList.getScheduleList()
                }
                onRejected: console.log("Cancel clicked")
            }

            ScrollBar.vertical: ScrollBar { }
        }
    }
}


