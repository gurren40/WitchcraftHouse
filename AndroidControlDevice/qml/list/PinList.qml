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
        "textarea" : textAreaDelegateComponent,
        "tumbler" : tumblerDelegateComponent,
        "spinbox" : spinboxDelegateComponent,
        "combobox" : comboboxDelegateComponent,
        "webview" : webviewDelegateComponent,
        "slider" : sliderDelegateComponent

//    mItems.append({ 0, QStringLiteral("default") });
//    mItems.append({ 1, QStringLiteral("switch") });
//    mItems.append({ 2, QStringLiteral("textout") });
//    mItems.append({ 3, QStringLiteral("tempc") });
//    mItems.append({ 4, QStringLiteral("textfield") });
//    mItems.append({ 5, QStringLiteral("textarea") });
//    mItems.append({ 6, QStringLiteral("tumbler") });
//    mItems.append({ 7, QStringLiteral("spinbox") });
//    mItems.append({ 8, QStringLiteral("combobox") });
//    mItems.append({ 9, QStringLiteral("webview") });
//    mItems.append({ 10,QStringLiteral("slider")});
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
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
            contentItem : Item{
                width: parent.width
                //color: transparent
                ItemDelegate{
                    id:switchIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                    text: pinName
                    onClicked: {
                        if(listViewElement.currentIndex != thisIndex){
                            listViewElement.currentIndex = thisIndex
                        }
                        pinDetails.open()
                    }
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
        }
    }

    Component{
        id : textoutDelegateComponent
        ItemDelegate{
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
            contentItem: Item{
                width: parent.width
                //color: transparent
                ItemDelegate{
                    id:textIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                    text: pinName
                    onClicked: {
                        if(listViewElement.currentIndex != thisIndex){
                            listViewElement.currentIndex = thisIndex
                        }
                        pinDetails.open()
                    }
                }
                Label{
                    id:actualLabel
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    text: value
                }
            }
        }
    }

    Component{
        id : tempcDelegateComponent
        ItemDelegate{
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
            contentItem: Item{
                width: parent.width
                //color: transparent
                ItemDelegate{
                    id:tempIcon
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                    text: pinName
                    onClicked: {
                        if(listViewElement.currentIndex != thisIndex){
                            listViewElement.currentIndex = thisIndex
                        }
                        pinDetails.open()
                    }
                }
                Label{
                    id:actualTempLabel
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    text: value + "\u2103"
                }
            }
        }
    }

    Component{
        id : textfieldDelegateComponent
        ItemDelegate{
            contentItem: Frame{
                width: parent.width
                ColumnLayout{
                    width: parent.width
                    ItemDelegate{
                        id : textFieldLabel
                        leftPadding: 0
                        bottomPadding: 0
                        topPadding: 0
                        Layout.fillWidth: true
                        icon.name: iconName
                        text: pinName
                        onClicked: {
                            if(listViewElement.currentIndex != thisIndex){
                                listViewElement.currentIndex = thisIndex
                            }
                            pinDetails.open()
                        }
                    }
                    TextField {
                        id: actualTextField
                        Layout.fillWidth: true
                        text: value
                        width: parent.width * 0.4
                        font.pointSize: 12
                        onEditingFinished: pinList.setPinValue(uuid,text)
                    }
                }
            }
        }
    }

    Component{
        id : textAreaDelegateComponent
        ItemDelegate{
            contentItem: Frame{
                width: parent.width
                ColumnLayout{
                    width: parent.width
                    ItemDelegate{
                        id : textAreaLabel
                        leftPadding: 0
                        bottomPadding: 0
                        topPadding: 0
                        Layout.fillWidth: true
                        icon.name: iconName
                        text: pinName
                        onClicked: {
                            if(listViewElement.currentIndex != thisIndex){
                                listViewElement.currentIndex = thisIndex
                            }
                            pinDetails.open()
                        }
                    }
                    TextArea {
                        id: actualTextArea
                        Layout.fillWidth: true
                        text: value
                        width: parent.width * 0.4
                        font.pointSize: 12
                        onEditingFinished: pinList.setPinValue(uuid,text)
                    }
                }
            }
        }
    }

    Component{
        id : tumblerDelegateComponent
        ItemDelegate{
            contentItem: Frame{
                width: parent.width
                ColumnLayout{
                    width: parent.width
                    ItemDelegate{
                        id : tumblerLabel
                        leftPadding: 0
                        bottomPadding: 0
                        topPadding: 0
                        Layout.fillWidth: true
                        icon.name: iconName
                        text: pinName
                        onClicked: {
                            if(listViewElement.currentIndex != thisIndex){
                                listViewElement.currentIndex = thisIndex
                            }
                            pinDetails.open()
                        }
                    }
                    Row{
                        Layout.alignment: Qt.AlignHCenter
                        spacing: 20
                        //Layout.fillWidth: true
                        //anchors.horizontalCenter: parent.horizontalCenter
                        Frame{
                            padding: 0
                            Tumbler {
                                id: actualTumbler
                                anchors.centerIn: parent
                                //Layout.fillWidth: true
                                width: parent.width * 0.4
                                font.pointSize: 12
                                model: option
                                currentIndex: value
                                //pinList.setPinValue(uuid,text)
                            }
                        }
                        Button{
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Set"
                            onClicked: pinList.setPinValue(uuid,actualTumbler.currentIndex)
                        }
                    }
                }
            }
        }
    }

    Component{
        id : spinboxDelegateComponent
        ItemDelegate{
            id : spinboxDelegate
            property int spinboxValue: value
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
            contentItem: Item{
                width: parent.width
                //color: transparent
                ItemDelegate{
                    padding: 0
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                    text: pinName
                    onClicked: {
                        if(listViewElement.currentIndex != thisIndex){
                            listViewElement.currentIndex = thisIndex
                        }
                        pinDetails.open()
                    }
                }
                SpinBox{
                    id:actualLabel
                    width: 120
                    anchors.right: parent.right
                    anchors.verticalCenter : parent.verticalCenter
                    stepSize: 1
                    from: fromAndTo(option,true)
                    to : fromAndTo(option,false)
                    value: spinboxDelegate.spinboxValue
                    function fromAndTo(options,from){
                        var thevalue = options.split(",");
                        if(from){
                            return thevalue[0];
                        }
                        else{
                            return thevalue[1];
                        }
                    }
                    onValueModified: pinList.setPinValue(uuid,value)
                }
            }
        }
    }

    Component{
        id : comboboxDelegateComponent
        ItemDelegate{
            contentItem: Frame{
                width: parent.width
                ColumnLayout{
                    width: parent.width
                    ItemDelegate{
                        id : comboBoxLabel
                        leftPadding: 0
                        bottomPadding: 0
                        topPadding: 0
                        Layout.fillWidth: true
                        icon.name: iconName
                        text: pinName
                        onClicked: {
                            if(listViewElement.currentIndex != thisIndex){
                                listViewElement.currentIndex = thisIndex
                            }
                            pinDetails.open()
                        }
                    }
                    Row{
                        spacing: 20
                        //Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                        //anchors.horizontalCenter: parent.horizontalCenter
                        ComboBox{
                            id : actualComboBox
                            clip: true
                            textRole: "value"
                            ListModel{
                                id : theModel
                            }
                            function comboItems(options){
                                var theValue = options.split(",");
                                theValue.forEach(function(theValue){
                                    theModel.append({"value":theValue});
                                });
                                return theModel;
                            }
                            model: comboItems(option)
                            currentIndex: getIndex(option,value)
                            function getIndex(options,values){
                                var theValue = options.split(",");
                                var theIndex = 0;
                                for(var i = 0; i<theValue.length; i++){
                                    if(theValue[i] == values){
                                        theIndex = i;
                                    }
                                }
                                return theIndex;
                            }
                        }
                        Button{
                            text: "Set"
                            onClicked: pinList.setPinValue(uuid,actualComboBox.currentText)
                        }
                    }
                }
            }
        }
    }

    Component{
        id: webviewDelegateComponent
        ItemDelegate{
            text: pinName
            icon.name: iconName
            contentItem: Item{
                width: parent.width
                //color: transparent
                ItemDelegate{
                    id:webviewIcon
                    padding: 0
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                    icon.name: iconName
                }
                Button{
                    text: "View"
                    anchors.verticalCenter : parent.verticalCenter
                    anchors.right: parent.right
                    onClicked: {
                        //webviewDialog.title = pinName
                        //webviewDialog.url = value
                        //webviewDialog.open()
                        //stackView.replace(model.source,{isShared : false})
                        stackView.push("../etc/webview.qml",{url : value})
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
        id: sliderDelegateComponent
        ItemDelegate{
            id : sliderDelegate
            property int sliderValue: value
            onClicked: {
                if(listViewElement.currentIndex != thisIndex){
                    listViewElement.currentIndex = thisIndex
                }
                pinDetails.open()
            }
            contentItem: Frame{
                //color: transparent
                ColumnLayout{
                    width: parent.width
                    ItemDelegate{
                        padding: 0
                        Layout.fillWidth: true
                        //anchors.verticalCenter : parent.verticalCenter
                        icon.name: iconName
                        text: pinName
                        onClicked: {
                            if(listViewElement.currentIndex != thisIndex){
                                listViewElement.currentIndex = thisIndex
                            }
                            pinDetails.open()
                        }
                    }
                    Row{
                        Layout.fillWidth: true
                        //Layout.alignment: Qt.AlignHCenter
                        spacing: 5
                        Label{
                            id : fromLabel
                            text: actualSlider.fromAndTo(option,true)
                            anchors.verticalCenter : parent.verticalCenter
                        }
                        Slider{
                            id:actualSlider
                            //Layout.fillWidth: true
                            //width: 120
                            //anchors.right: parent.right
                            anchors.verticalCenter : parent.verticalCenter
                            width: parent.width - (10 + fromLabel.width + toLabel.width)
                            stepSize: 1
                            from: fromAndTo(option,true)
                            to : fromAndTo(option,false)
                            value: sliderDelegate.sliderValue
                            orientation: Qt.Horizontal
                            snapMode: Slider.SnapOnRelease
                            function fromAndTo(options,from){
                                var thevalue = options.split(",");
                                if(from){
                                    return thevalue[0];
                                }
                                else{
                                    return thevalue[1];
                                }
                            }
                            //onValueModified: pinList.setPinValue(uuid,value)
                            onMoved: pinList.setPinValue(uuid,value)
                        }
                        Label{
                            id : toLabel
                            text: actualSlider.fromAndTo(option,false)
                            anchors.verticalCenter : parent.verticalCenter
                        }
                    }
                }
            }
        }
    }

//    Dialog{
//        property string url: ""
//        title: ""
//        id : webviewDialog
//        width: parent.width * 0.9
//        height: parent.height * 0.9
//        standardButtons: Dialog.Close
//        anchors.centerIn: parent
//        modal: true
//        contentItem: WebView{
//            anchors.centerIn: parent
//            width: parent.width
//            height: parent.height
//            url : webviewDialog.url
//        }
//    }

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
                Material.foreground: "white"
                text: section
                width: parent.width
                height: 48
                contentItem: Frame{
                    anchors.centerIn: parent
                    padding: 0
                    background: Image{
                        anchors.centerIn: parent
                        clip: true
                        asynchronous: true
                        width: parent.width
                        height: parent.height
                        source: "/images/drawer_header.jpeg"
                        fillMode: Image.PreserveAspectCrop
                    }
                    Label{
                        anchors.centerIn: parent
                        text: section
                        font.pointSize: 18
                        font.bold: true
                    }
                }
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
                    text: "Owner Name\t: " + listViewElement.currentItem.userName
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
                        visible: !isShared
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
