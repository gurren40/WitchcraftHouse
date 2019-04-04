import QtQuick 2.9
import QtQuick.Controls 2.2
import Device 1.0

Page {
    property int listID : 1
    function create(){createNewDevice.open()}
    anchors.fill: parent
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
            width: parent.width
            clip: true
            contentWidth: parent.width
            anchors.centerIn: parent
            Column {
                width: parent.width
                anchors.centerIn: parent
                spacing: 10
                Text {
                    text: "Device Name\t: " + listViewElement.currentItem.deviceName
                }
                Text {
                    text: "Device UUID\t\t: " + listViewElement.currentItem.deviceUUID
                }
                Text {
                    text: "Device Token\t: " + listViewElement.currentItem.deviceToken
                }
                Text {
                    text: "Owner\t\t: " + listViewElement.currentItem.userName
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
                        onClicked: editDevice.open()
                    }
                    Button {
                        text: "Delete"
                        onClicked: deleteDevice.open()
                    }
                }
            }
        }
    }

    Dialog{
        id:createNewDevice
        modal: true
        anchors.centerIn: parent
        title: "Create New Device"
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
                    text: qsTr("Device Name :")
                }
                TextField{
                    id : newName
                    width: parent.width
                }
                Text {
                    text: qsTr("Device Description :")
                }
                TextField{
                    id : newDescription
                    width: parent.width
                }
            }
        }

        onAccepted: {
            //deviceList.createNewDevice(QVariant deviceName, QVariant description);
            deviceList.createNewDevice(newName.text,newDescription.text);
        }
        onRejected: console.log("Cancel clicked")
    }

    Dialog{
        id: editDevice
        modal: true
        anchors.centerIn: parent
        title: "Edit Device"
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
                    text: "Device ID : " + listViewElement.currentItem.deviceID
                }
                Text {
                    text: "Device UUID : " + listViewElement.currentItem.deviceUUID
                }
                Text {
                    text: qsTr("Device Name :")
                }
                TextField{
                    id : deviceName
                    width: parent.width
                    text: listViewElement.currentItem.deviceName
                }
                Text {
                    text: qsTr("Device Description :")
                }
                TextField{
                    id : deviceDescription
                    width: parent.width
                    text: listViewElement.currentItem.description
                }
            }
        }
        onAccepted: {
            //void editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description);
            deviceList.editDevice(listViewElement.currentItem.deviceID,listViewElement.currentItem.deviceUUID,deviceName.text,deviceDescription.text);
        }
        onRejected: console.log("Cancel clicked")
    }
    Dialog{
        id: deleteDevice
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Device"
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
                    text: "Device ID : " + listViewElement.currentItem.deviceID
                }
                Text {
                    text: "Device UUID : " + listViewElement.currentItem.deviceUUID
                }
            }
        }
        onAccepted: {
            //void deleteDevice(QVariant deviceID);
            deviceList.deleteDevice(listViewElement.currentItem.deviceID);
        }
        onRejected: console.log("Cancel clicked")
    }
}


