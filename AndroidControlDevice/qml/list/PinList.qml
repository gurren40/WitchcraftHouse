import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Pin 1.0

Pane {
    padding: 0
    property string title: "Witchcraft House"

    property var delegateComponentMap: {
        "default": defaultDelegateComponent,
        "switch": switchDelegateComponent
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
            icon.name : "iconName"
            text : pinName
        }
    }

    Component{
        id: switchDelegateComponent

        ItemDelegate{
            contentItem : Row{
                width: parent.width
                spacing: 5
//                Icon{
//                    icon.name : iconName
//                }
                Label{
                    text: pinName
                    anchors.verticalCenter : parent.verticalCenter
                }
                Switch{
                    anchors.verticalCenter : parent.verticalCenter
                    anchors.right : parent.right
                }
            }
        }
    }

    ColumnLayout {
        id: column
        spacing: 40
        anchors.fill: parent
        //anchors.topMargin:window and 20

        /*Label {
            Layout.fillWidth: true
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "Delegate controls are used as delegates in views such as ListView."
        }*/

        ListView {
            id: listViewElement
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: PinModel{
                list: pinList
            }

            section.property: "groupName"
            section.delegate: ItemDelegate {
                //width: listView.width
                //height: sectionLabel.implicitHeight + 20

//                Label {
//                    id: sectionLabel
//                    text: section
//                    anchors.centerIn: parent
//                }
                icon.name : "expand_more"
                text: "Group : " + section
            }

            delegate: Loader {
                id: delegateLoader
                width: listView.width
                sourceComponent: delegateComponentMap[model.pinTypeName]

                property ListView view: listView
                property int ourIndex: index

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
            contentWidth: parent.width
            anchors.centerIn: parent
            Column {
                width: parent.width
                anchors.centerIn: parent
                spacing: 10
                Text {
                    text: "Pin Name\t: " + listViewElement.currentItem.pinName
                }
                Text {
                    text: "Pin UUID\t: " + listViewElement.currentItem.uuid
                }
                Text {
                    text: "User Email\t: " + listViewElement.currentItem.userName
                }
                Text {
                    text: "Group Name\t: " + listViewElement.currentItem.groupName
                }
                Text {
                    text: "Device Name\t: " + listViewElement.currentItem.deviceName
                }
                Text {
                    text: "Icon\t: " + listViewElement.currentItem.iconName
                }
                Text {
                    text: "Pin Type\t: " + listViewElement.currentItem.pinTypeName
                }
                Text {
                    text: "Current value\t: " + listViewElement.currentItem.value
                }
                Text {
                    text: "Option\t: " + listViewElement.currentItem.option
                }
                Text {
                    text: "Description\t: " + listViewElement.currentItem.description
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    spacing: 10
                    Button {
                        text: "Edit"
                        onClicked: editPin.open()
                    }
                    Button {
                        text: "Delete"
                        onClicked: deletePin.open()
                    }
                }
            }
        }
    }

}
