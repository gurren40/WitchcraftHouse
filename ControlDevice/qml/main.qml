import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 360
    height: 520
    title: qsTr("Witchcraft House")

    //! [orientation]
    readonly property bool inPortrait: window.width < window.height
    //! [orientation]

    onWidthChanged: function(){
        if(!inPortrait){
            drawer.open()
        }
        else if(inPortrait){
            drawer.close()
        }
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            listView.currentIndex = -1
        }
    }

    header: ToolBar {
        id : toolBar
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: {
                if(inPortrait && !drawer.visible){
                   return "\u2630"
                }
                else if(drawer.visible){
                    return "\u25C0"
                }
                else{
                    return "\u25B6"
                }
            }

            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if(drawer.visible){
                    drawer.close()
                }
                else{
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Page {
        anchors.fill: parent

        Drawer{
            id : drawer
            width: (inPortrait) ? parent.width * 0.66 : parent.width * 0.33
            y: toolBar.height
            height: window.height - toolBar.height
            modal: inPortrait
            interactive: inPortrait
            position: inPortrait ? 0 : 1
            visible: !inPortrait

            ListView{
                id : listView
                anchors.fill: parent
                currentIndex: 0
                delegate: ItemDelegate {
                    text: model.title
                    width: parent.width
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        inPortrait ? drawer.close() : undefined
                        if(listView.currentIndex != index){
                            listView.currentIndex = index
                            stackView.push(model.source)
                        }
                    }
                }

                model: ListModel{
                    ListElement { title: "Home"; source: "./list/PinList.qml" }
                    ListElement { title: "Device"; source: "./list/DeviceList.qml" }
                    ListElement { title: "Group"; source: "./list/GroupList.qml" }
                    ListElement { title: "Schedule"; source: "./list/ScheduleList.qml" }
                    ListElement { title: "Shared List"; source: "./list/SharedList.qml" }
                    ListElement { title: "Control Device"; source: "./list/ControlDeviceList.qml" }
                }
                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }

        StackView {
            id: stackView
            focus: true
            initialItem: "./list/PinList.qml"
            height: parent.height
            width: (!inPortrait && drawer.visible) ? parent.width - drawer.width : parent.width
            anchors.right: parent.right
            anchors.top : toolBar.bottom
        }
    }
}
