import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtWebView 1.1
import Pin 1.0
import Icon 1.0
import Group 1.0
import PinType 1.0
import Device 1.0
import QtQuick.Controls.Material 2.12

Pane {
    padding: 0
    property bool isShared: false
    property string title: isShared ? "Shared Pin" : "Witchcraft House"
    function create(){
        if(!isShared){
            createNewPin.open()
        }
    }
    property bool canCreate: !isShared
    property var delegateComponentMap: {
        "default": defaultDelegateComponent,
        "switch": switchDelegateComponent,
        "webview" : webviewDelegateComponent
//        "textout": textoutDelegateComponent,
//        "tempc": tempcDelegateComponent,
//        "tempf": tempfDelegateComponent,
//        "textfield": textfieldDelegateComponent,

//        mItems.append({ 0, QStringLiteral("default") });
//        mItems.append({ 1, QStringLiteral("switch") });
//        mItems.append({ 2, QStringLiteral("textout") });
//        mItems.append({ 3, QStringLiteral("tempc") });
//        mItems.append({ 4, QStringLiteral("tempf") });
//        mItems.append({ 5, QStringLiteral("textfield") });
//        mItems.append({ 6, QStringLiteral("spinbox") });
//        mItems.append({ 7, QStringLiteral("textarea") });
//        mItems.append({ 8, QStringLiteral("tubler") });
//        mItems.append({ 9, QStringLiteral("combobox") });
    }

    Component{
        id: defaultDelegateComponent

        ItemDelegate{
            icon.name : iconName
            text : pinName
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
        }
    }

    Component{
        id: switchDelegateComponent
        ItemDelegate{
            contentItem : Label{
                width: parent.width
                color: transparent
                ItemDelegate{
                    id:switchIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Label{
                    id:switchLabel
                    leftPadding: 15
                    anchors.left: switchIcon.right
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                Switch{
                    id:actualSwitch
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    checked: function(){
                        if(value === "0"){
                            return false
                        }
                        else if(value === "1"){
                            return true
                        }
                    }
                    onClicked: function(){
                        if(checked){
                            //void setPinValue(QVariant UUID, QVariant value);
                            pinList.setPinValue(uuid,"1")
                        }
                        else if(!checked){
                            pinList.setPinValue(uuid,"0")
                        }
                    }
                }
            }
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
        }
    }

    Component{
        id: webviewDelegateComponent
        ItemDelegate{
            text: pinName
            icon.name: iconName
            contentItem: Label{
                width: parent.width
                color: transparent
                ItemDelegate{
                    id:webviewIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Label{
                    id:webviewLabel
                    leftPadding: 15
                    anchors.left: webviewIcon.right
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                Button{
                    text: "View"
                    anchors.verticalCenter : parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: {
                        webviewDialog.title = pinName
                        webviewDialog.url = value
                        webviewDialog.open()
                    }
                }
            }
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
        }
    }

    Dialog{
        property string url: ""
        title: ""
        id : webviewDialog
        width: parent.width * 0.9
        height: parent.height * 0.9
        standardButtons: Dialog.Close
        anchors.centerIn: parent
        modal: true
        contentItem: WebView{
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            url : webviewDialog.url
        }
    }

    ColumnLayout {
        id: column
        spacing: 40
        anchors.fill: parent

        ListView {
            id: listViewElement
            currentIndex: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            footer: Label{
                height: 90
                width: parent.width
                text: ""
            }

            model: PinModel{
                list: isShared ? sharedPinList : pinList
            }

            section.property: "groupName"
            section.delegate: ItemDelegate {
                icon.name : "expand_more"
                text: section + " group"
                width: parent.width
                font.pointSize: 18
                font.bold: true
                font.italic: true
            }

            delegate: Loader {
                id: delegateLoader
                width: listViewElement.width
                sourceComponent: delegateComponentMap[model.pinTypeName]

                property ListView view: listView
                property int thisIndex: index

                property int pinID : model.pinID
                property string uuid : model.UUID
                property int userID : model.userID
                property string userName : model.userName
                property int groupID : model.groupID
                property string groupName : model.groupName
                property int deviceID : model.deviceID
                property string deviceName : model.deviceName
                property int iconID : model.iconID
                property string iconName : model.iconName
                property int pinTypeID : model.pinTypeID
                property string pinTypeName : model.pinTypeName
                property string pinName : model.pinName
                property string value : model.value
                property string option : model.option
                property string description : model.description
            }
        }
    }

    Dialog {
        id : pinDetails
        width: parent.width * 0.9
        height: parent.height * 0.9
        modal: true
        anchors.centerIn: parent
        title: "Pin Details"
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
                    focus: true
                    text: "Pin Name\t\t: " + listViewElement.currentItem.pinName
                }
                Label {
                    text: "Pin UUID\t\t: " + listViewElement.currentItem.uuid
                }
                Label {
                    text: "User Email\t\t: " + listViewElement.currentItem.userName
                }
                Label {
                    text: "Group Name\t\t: " + listViewElement.currentItem.groupName
                }
                Label {
                    text: "Device Name\t: " + listViewElement.currentItem.deviceName
                }
                Label {
                    text: "Icon\t\t: " + listViewElement.currentItem.iconName
                }
                Label {
                    text: "Pin Type\t\t: " + listViewElement.currentItem.pinTypeName
                }
                Label {
                    text: "Current value\t: " + listViewElement.currentItem.value
                }
                Label {
                    text: "Option\t\t: " + listViewElement.currentItem.option
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
                        onClicked: editPin.open()
                        enabled: !isShared
                    }
                    Button {
                        text: "Delete"
                        onClicked: deletePin.open()
                        enabled: !isShared
                    }
                }
            }
        }
    }

    Dialog{
        id : createNewPin
        width: parent.width * 0.9
        height: parent.height * 0.9
        modal: true
        anchors.centerIn: parent
        title: "Create New Pin"
        standardButtons: Dialog.Ok | Dialog.Cancel
        contentItem: ScrollView{
            width: parent.width
            clip: true
            contentWidth: parent.width
            anchors.centerIn: parent
            Column{
                width: parent.width
                anchors.centerIn: parent
                spacing: 5
                Label {
                    text: qsTr("Pin Name :")
                }
                TextField{
                    id : newPinName
                    width: parent.width
                }
                Label {
                    text: qsTr("Select Group :")
                }
                ComboBox{
                    property string displayName: "Select Group"
                    id : newGroup
                    textRole: "groupID"
                    displayText: displayName
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: newGroup.displayName = model.groupName
                    }
                }
                Label {
                    text: qsTr("Select Device :")
                }
                ComboBox{
                    property string displayName : "Select Device"
                    id : newDevice
                    textRole: "deviceID"
                    displayText: displayName
                    width: parent.width
                    model: DeviceModel{
                        list: deviceList
                    }
                    delegate: ItemDelegate{
                        text: model.deviceName
                        onClicked: newDevice.displayName = model.deviceName
                    }
                }
                Label {
                    text: qsTr("Select Icon :")
                }
                ComboBox{
                    property string displayName : "Select Icon"
                    id : newIcon
                    textRole: "iconID"
                    displayText: displayName
                    width: parent.width
                    model: IconModel{
                        list: iconList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.iconName
                        onClicked: newIcon.displayName = model.iconName
                    }
                }
                Label {
                    text: qsTr("Select Pin Type :")
                }
                ComboBox{
                    property string displayName : "Select Pin Type"
                    id : newPinType
                    textRole: "pinTypeID"
                    displayText: displayName
                    width: parent.width
                    model: PinTypeModel{
                        list: pinTypeList
                    }
                    delegate: ItemDelegate{
                        text: model.pinTypeName
                        onClicked: newPinType.displayName = model.pinTypeName
                    }
                }
                Label {
                    text: qsTr("Initial Value :")
                }
                TextField{
                    id : newValue
                    width: parent.width
                }
                Label {
                    text: qsTr("Options :")
                }
                TextField{
                    id : newOption
                    width: parent.width
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : newDescription
                    width: parent.width
                }
            }
        }

        onAccepted: {
            //void createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
            pinList.createNewPin(newPinName.text,newGroup.currentText,newDevice.currentText,newIcon.currentText,newPinType.currentText,newValue.text,newOption.text,newDescription.text)
        }
    }

    Dialog{
        id : editPin
        width: parent.width * 0.9
        height: parent.height * 0.9
        modal: true
        anchors.centerIn: parent
        title: "Edit Pin"
        standardButtons: Dialog.Ok | Dialog.Cancel
        contentItem: ScrollView{
            width: parent.width
            clip: true
            contentWidth: parent.width
            anchors.centerIn: parent
            Column{
                width: parent.width
                anchors.centerIn: parent
                spacing: 5
                Label {
                    id:pinID
                    text: "Pin ID : " + listViewElement.currentItem.pinID
                }
                Label {
                    id:uuid
                    text: "Pin UUID : " + listViewElement.currentItem.uuid
                }
                Label {
                    text: qsTr("Pin Name :")
                }
                TextField{
                    id : pinName
                    width: parent.width
                    text: listViewElement.currentItem.pinName
                }
                Label {
                    text: qsTr("Select Group :")
                }
                ComboBox{
                    property string displayName: "Select Icon (MUST)"
                    id : group
                    textRole: "groupID"
                    displayText: displayName
                    width: parent.width
                    model: GroupModel{
                        list: groupList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.groupName
                        onClicked: group.displayName = model.groupName
                    }
                }
                Label {
                    text: qsTr("Select Device :")
                }
                ComboBox{
                    property string displayName : "Select Device (MUST)"
                    id : device
                    textRole: "deviceID"
                    displayText: displayName
                    width: parent.width
                    model: DeviceModel{
                        list: deviceList
                    }
                    delegate: ItemDelegate{
                        text: model.deviceName
                        onClicked: device.displayName = model.deviceName
                    }
                }
                Label {
                    text: qsTr("Select Icon :")
                }
                ComboBox{
                    property string displayName : "Select Icon (MUST)"
                    id : editIcon
                    textRole: "iconID"
                    displayText: displayName
                    width: parent.width
                    model: IconModel{
                        list: iconList
                    }
                    delegate: ItemDelegate{
                        icon.name : model.iconName
                        text: model.iconName
                        onClicked: editIcon.displayName = model.iconName
                    }
                }
                Label {
                    text: qsTr("Select Pin Type :")
                }
                ComboBox{
                    property string displayName : "Select Pin Type (MUST)"
                    id : pinType
                    textRole: "pinTypeID"
                    displayText: displayName
                    width: parent.width
                    model: PinTypeModel{
                        list: pinTypeList
                    }
                    delegate: ItemDelegate{
                        text: model.pinTypeName
                        onClicked: pinType.displayName = model.pinTypeName
                    }
                }
                Label {
                    text: qsTr("New Value :")
                }
                TextField{
                    id : value
                    width: parent.width
                    text: listViewElement.currentItem.value
                }
                Label {
                    text: qsTr("Options :")
                }
                TextField{
                    id : option
                    width: parent.width
                    text: listViewElement.currentItem.option
                }
                Label {
                    text: qsTr("Description :")
                }
                TextField{
                    id : description
                    width: parent.width
                    text: listViewElement.currentItem.description
                }
            }
        }

        onAccepted: {
            //void editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
            pinList.editPin(listViewElement.currentItem.pinID,listViewElement.currentItem.uuid,pinName.text,group.currentText,device.currentText,editIcon.currentText,pinType.currentText,value.text,option.text,description.text)
        }
    }

    Dialog{
        id: deletePin
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Pin?"
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
                    text: "Pin ID : " + listViewElement.currentItem.pinID
                }
                Label {
                    text: "Pin UUID : " + listViewElement.currentItem.uuid
                }
                Label {
                    text: "Pin Name : " + listViewElement.currentItem.pinName
                }
            }
        }
        onAccepted: {
            //void deletePin(QVariant UUID);
            pinList.deletePin(listViewElement.currentItem.uuid);
        }
        onRejected: console.log("Cancel clicked")
    }
}
