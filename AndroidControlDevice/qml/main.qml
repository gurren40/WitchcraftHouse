import QtQuick 2.9
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Witchcraft House")

    //! [orientation]
    readonly property bool inPortrait: window.width < window.height
    //! [orientation]

    Dialog{
        id: exitDialog
        modal: true
        anchors.centerIn: parent
        title: "Are you sure want to Exit?"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: Qt.quit()
        onRejected: console.log("Cancel clicked")
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        onActivated: {
            if(stackView.depth > 1){
                stackView.pop()
                listView.currentIndex = -1
            }
            else{
                exitDialog.open()
            }
        }
    }

    header: ToolBar {
        Material.foreground: "white"
        id : toolBar
        contentHeight: toolButton.implicitHeight

        RowLayout {
            spacing: 20
            anchors.fill: parent
            ToolButton {
                id: toolButton
                icon.name: drawer.visible ? "chevron_left" : "menu"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    if(drawer.visible){
                        drawer.close()
                    }
                    else{
                        drawer.open()
                    }
                }
                anchors.left: parent.left
            }

            Label {
                text: stackView.currentItem.title
                font.bold: true
                anchors.centerIn: parent
            }

            ToolButton {
                id: menuButton
                icon.name: "refresh"
                icon.color: user.isOnline ? "green" : "red"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                anchors.right: parent.right
                onClicked: {
                    user.getAllData()
                }
            }
        }
    }

    Page {
        anchors.fill: parent

        Drawer{
            id : drawer
            width: (inPortrait) ? parent.width * 0.66 : parent.width * 0.25
            height: parent.height - toolBar.contentHeight
            y : toolBar.contentHeight
            modal: inPortrait
            interactive: inPortrait
            position: inPortrait ? 0 : 1
            visible: !inPortrait
            background: Rectangle{
                anchors.fill: parent
                color: window.palette.alternateBase
            }

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
                            stackView.replace(model.source)
                        }
                    }
                }

                model: ListModel{
                    ListElement { title: "Home"; source: "./list/PinList.qml" }
                    ListElement { title: "Shared Pin"; source: "./list/SharedPinList.qml" }
                    ListElement { title: "Device"; source: "./list/DeviceList.qml" }
                    ListElement { title: "Group"; source: "./list/GroupList.qml" }
                    ListElement { title: "Schedule"; source: "./list/ScheduleList.qml" }
                    ListElement { title: "Shared List"; source: "./list/SharedList.qml" }
                    ListElement { title: "Control Device"; source: "./list/ControlDeviceList.qml" }
                    ListElement { title: "Settings"; source: "./etc/settings.qml" }
                }
                ScrollBar.vertical: ScrollBar { }
            }
        }

        StackView {
            id: stackView
            focus: true
            initialItem: "./list/PinList.qml"
            height: parent.height - toolBar.contentHeight
            width: inPortrait ? parent.width : parent.width - (drawer.width * 2)
            anchors.centerIn: parent
            anchors.top : toolBar.bottom

            pushEnter : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 400
                }
            }
            pushExit : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 400
                }
            }
            popEnter : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 400
                }
            }
            popExit : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 400
                }
            }
            replaceEnter : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 400
                }
            }
            replaceExit : Transition {
                PropertyAnimation{
                    property: "opacity"
                    from: 1
                    to: 0
                    duration: 400
                }
            }
        }
    }
}
