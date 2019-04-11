import QtQuick 2.9
import QtQuick.Controls 2.2
import Device 1.0

Page {
    property bool canCreate: true
    property int listID : 1
    padding: 0
    //function create(){createNewDevice.open()}
    function create(){stackView.push("../create/createDevice.qml")}
    //anchors.fill: parent
    title: qsTr("Devices")

    ListView{
        id:listViewElement
        anchors.fill: parent
        width: parent.width
        contentWidth: parent.width
        currentIndex: 0
        model: DeviceModel{
            list: deviceList
        }
        footer: Label{
            height: 90
            width: parent.width
            text: ""
        }

        delegate: ItemDelegate{
            property string deviceName: model.deviceName
            property int deviceID: model.deviceID
            property string deviceUUID: model.deviceUUID
            property string userName : model.userName
            property string deviceToken : model.deviceToken
            property bool isDeviceOnline : model.isDeviceOnline
            property string description : model.description
            width: parent.width
            icon.name: "expand_more"
            icon.color: isDeviceOnline ? "green" : "red"
            text: model.deviceName
            onClicked: {
                if(listViewElement.currentIndex != index){
                    listViewElement.currentIndex = index
                }
                deviceDetails.open()
            }
        }
        ScrollBar.vertical: ScrollBar { }
    }

    Dialog {
        id : deviceDetails
        width: parent.width * 0.9
        height: parent.height * 0.9
        modal: true
        anchors.centerIn: parent
        title: "Device Details"
        standardButtons: Dialog.Close
        contentItem: ScrollView {
            //width: parent.width
            clip: true
            //contentWidth: parent.width
            anchors.centerIn: parent
            Column {
                //width: parent.width
                anchors.centerIn: parent
                spacing: 10
                Label {
                    text: "Device Name\t: " + listViewElement.currentItem.deviceName
                }
                Label {
                    text: "Device UUID\t\t: " + listViewElement.currentItem.deviceUUID
                }
                Label {
                    text: "Device Token\t: " + listViewElement.currentItem.deviceToken
                }
                Label {
                    text: "Owner\t\t: " + listViewElement.currentItem.userName
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
                        //onClicked: editDevice.open()
                        onClicked: {
                            deviceDetails.close()
                            stackView.push("../edit/editDevice.qml",{
                                                  deviceName : listViewElement.currentItem.deviceName,
                                                  deviceID : listViewElement.currentItem.deviceID,
                                                  deviceUUID : listViewElement.currentItem.deviceUUID,
                                                  userName : listViewElement.currentItem.userName,
                                                  deviceToken : listViewElement.currentItem.deviceToken,
                                                  isDeviceOnline : listViewElement.currentItem.isDeviceOnline,
                                                  description : listViewElement.currentItem.description
                                              })
                        }
                    }
                    Button {
                        text: "Delete"
                        onClicked: {
                            deviceDetails.close()
                            deleteDevice.open()
                        }
                    }
                }
            }
        }
    }

    Dialog{
        id: deleteDevice
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Device"
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
                    text: "Device ID : " + listViewElement.currentItem.deviceID
                }
                Label {
                    text: "Device UUID : " + listViewElement.currentItem.deviceUUID
                }
            }
        }
        onAccepted: {
            //void deleteDevice(QVariant deviceID);
            deviceList.deleteDevice(listViewElement.currentItem.deviceID);
            deviceList.getDeviceList()
        }
        onRejected: console.log("Cancel clicked")
    }
}


