import QtQuick 2.9
import QtQuick.Controls 2.2
import ControlDevice 1.0

Page {
    property int listID : 5
    anchors.fill: parent
    title: qsTr("Devices")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: ControlDeviceModel{
            list: controlDeviceList
        }
        footer: Text{
            height: 105
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate {
            property int controlDeviceID : model.controlDeviceID
            property int userID : model.userID
            property string userName : model.userName
            property string controlDeviceName : model.controlDeviceName
            property string controlDeviceToken : model.controlDeviceToken
            property bool isControlDeviceOnline : model.isControlDeviceOnline
            property date expireDate : model.expireDate
            width: parent.width
            text: model.controlDeviceName
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
                    Text {
                        text: "Control Device Name\t: " + listViewElement.currentItem.controlDeviceName
                    }
                    Text {
                        text: "Control Device Token\t: " + listViewElement.currentItem.controlDeviceToken
                    }
                    Text {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                    Button {
                        enabled: !listViewElement.currentItem.isControlDeviceOnline
                        text: "Delete"
                        onClicked: deleteControlDevice.open()
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
            height: parent.height * 0.9
            standardButtons: Dialog.Ok | Dialog.Cancel
            contentItem: ScrollView {
                clip: true
                Column{
                    spacing: 10
                    width: parent.width
                    Text {
                        text: "Control Device Name\t: " + listViewElement.currentItem.controlDeviceName
                    }
                    Text {
                        text: "Control Device Token\t: " + listViewElement.currentItem.controlDeviceToken
                    }
                    Text {
                        text: "Owner\t\t: " + listViewElement.currentItem.userName
                    }
                }
            }
            onAccepted: {
                //void deleteControlDevice(QVariant controlDeviceID);
                controlDeviceList.deleteControlDevice(listViewElement.currentItem.controlDeviceID);
            }
            onRejected: console.log("Cancel clicked")
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


