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

Page {
    padding: 0
    property bool isShared: false
    //property string title: isShared ? "Shared Pin" : "Witchcraft House"
    title: isShared ? "Shared Pin" : "Witchcraft House"
    function create(){
        if(!isShared){
            //createNewPin.open()
            stackView.push("../create/createPin.qml")
        }
    }
    property bool canCreate: !isShared
    property var delegateComponentMap: {
        "default": defaultDelegateComponent,
        "switch": switchDelegateComponent,
        "textout": textoutDelegateComponent,
        "tempc": tempcDelegateComponent,
        "textfield": textfieldDelegateComponent,
        "webview" : webviewDelegateComponent
//        "tempf": tempfDelegateComponent,

//        mItems.append({ 0, QStringLiteral("default") });
//        mItems.append({ 1, QStringLiteral("switch") });
//        mItems.append({ 2, QStringLiteral("textout") });
//        mItems.append({ 3, QStringLiteral("tempc") });
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
                //color: transparent
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
                    function thefunc(){
                        if(value == "1"){
                            actualSwitch.checked = true
                        }
                        else{
                            actualSwitch.checked = false
                        }
                    }

                    checked: thefunc()

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
        id : textoutDelegateComponent
        ItemDelegate{
            contentItem: Label{
                width: parent.width
                color: transparent
                ItemDelegate{
                    id:textIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Label{
                    id:textLabel
                    leftPadding: 15
                    anchors.left: textIcon.right
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                Label{
                    id:actualLabel
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    text: value
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
        id : tempcDelegateComponent
        ItemDelegate{
            contentItem: Label{
                width: parent.width
                color: transparent
                ItemDelegate{
                    id:tempIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Label{
                    id:tempLabel
                    leftPadding: 15
                    anchors.left: tempIcon.right
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                Label{
                    id:actualTempLabel
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    text: value + " " +"\u2103"
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
        id : textfieldDelegateComponent
        ItemDelegate{
            contentItem: Label{
                width: parent.width
                color: transparent
                ItemDelegate{
                    id:textFieldIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Label{
                    id:textFieldLabel
                    leftPadding: 15
                    anchors.left: textFieldIcon.right
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                TextField {
                    id:actualTextfield
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    text: value
                    width: parent.width * 0.4
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
                //color: transparent
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
                        enabled: !isShared
                        visible: !isShared
                        onClicked: {
                            pinDetails.close()
                            stackView.push("../edit/editPin.qml",{
                                               pinID : listViewElement.currentItem.pinID,
                                               uuid : listViewElement.currentItem.uuid,
                                               userID : listViewElement.currentItem.userID,
                                               userName : listViewElement.currentItem.userName,
                                               groupID : listViewElement.currentItem.groupID,
                                               groupName : listViewElement.currentItem.groupName,
                                               deviceID : listViewElement.currentItem.deviceID,
                                               deviceName : listViewElement.currentItem.deviceName,
                                               iconID : listViewElement.currentItem.iconID,
                                               iconName : listViewElement.currentItem.iconName,
                                               pinTypeID : listViewElement.currentItem.pinTypeID,
                                               pinTypeName : listViewElement.currentItem.pinTypeName,
                                               pinName : listViewElement.currentItem.pinName,
                                               value : listViewElement.currentItem.value,
                                               option : listViewElement.currentItem.option,
                                               description : listViewElement.currentItem.description
                                           })
                        }
                    }
                    Button {
                        text: "Delete"
                        onClicked: {
                            pinDetails.close()
                            deletePin.open()
                        }
                        enabled: !isShared
                    }
                }
            }
        }
    }

    Dialog{
        id: deletePin
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to delete this Pin?"
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
            pinList.getPinList()
        }
        onRejected: console.log("Cancel clicked")
    }
}
