import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import ControlDevice 1.0

Page {
    property bool canCreate: false
    property int listID : 5
    padding: 0
    //anchors.fill: parent
    title: qsTr("Devices")

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
            model: ControlDeviceModel{
                list: controlDeviceList
            }
            footer: Label{
                height: 90
                width: parent.width
                text: ""
            }

            delegate: ItemDelegate {
                property string controlDeviceID : model.controlDeviceID
                property int userID : model.userID
                property string userName : model.userName
                property string controlDeviceName : model.controlDeviceName
                property string controlDeviceToken : model.controlDeviceToken
                property bool isControlDeviceOnline : model.isControlDeviceOnline
                property date expireDate : model.expireDate
                width: parent.width
                text: model.controlDeviceName
                icon.name: "default"
                icon.color: isControlDeviceOnline ? "green" : "red"
                onClicked: {
                    if(listViewElement.currentIndex != index){
                        listViewElement.currentIndex = index
                    }
                    controlDeviceDetails.open()
                }
            }

            Dialog {
                id : controlDeviceDetails
                width: parent.width * 0.9
                height: parent.height * 0.9
                modal: true
                anchors.centerIn: parent
                title: "Control Device Details"
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
                            text: "Control Device Name\t: " + listViewElement.currentItem.controlDeviceName
                        }
                        Label {
                            text: "Control Device UUID\t: " + listViewElement.currentItem.controlDeviceID
                        }
                        Label {
                            text: "Owner\t\t: " + listViewElement.currentItem.userName
                        }
                        Button {
                            enabled: !listViewElement.currentItem.isControlDeviceOnline
                            text: "Delete"
                            onClicked: {
                                controlDeviceDetails.close()
                                deleteControlDevice.open()
                            }
                        }
                    }
                }
            }

            Dialog{
                id: deleteControlDevice
                modal: true
                anchors.centerIn: parent
                title: "Are you sure want to delete this Control Device?"
                width: parent.width * 0.9
                //height: parent.height * 0.9
                standardButtons: Dialog.Ok | Dialog.Cancel
                contentItem: ScrollView {
                    clip: true
                    Column{
                        spacing: 10
                        width: parent.width
                        Label {
                            text: "Control Device Name\t: " + listViewElement.currentItem.controlDeviceName
                        }
                        Label {
                            text: "Control Device UUID\t: " + listViewElement.currentItem.controlDeviceID
                        }
                        Label {
                            text: "Owner\t\t: " + listViewElement.currentItem.userName
                        }
                    }
                }
                onAccepted: {
                    //void deleteControlDevice(QVariant controlDeviceID);
                    controlDeviceList.deleteControlDevice(listViewElement.currentItem.controlDeviceID);
                    controlDeviceList.getControlDeviceList()
                }
                onRejected: console.log("Cancel clicked")
            }

            ScrollBar.vertical: ScrollBar { }
        }
    }
}


