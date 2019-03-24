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

    onWidthChanged: drawerControl()
    onHeightChanged: drawerControl()

    function drawerControl(){
        if(!inPortrait){
            drawer.open()
        }
        else if(inPortrait){
            drawer.close()
        }
    }

    Timer{
        interval: 200
        repeat: false
        running: true
        triggeredOnStart: true
        onTriggered: window.drawerControl()
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
        Material.foreground: "white"
        id : toolBar
        contentHeight: toolButton.implicitHeight

        RowLayout {
            spacing: 20
            anchors.fill: parent
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

            ToolButton {
                id: menuButton
                text: "\u22EE"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: optionsMenu.open()
                anchors.right: parent.right

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                    }
                    MenuItem {
                        text: "Windowed Mode"
                        onTriggered: window.showNormal()
                    }
                    MenuItem {
                        text: "FullScreen Mode"
                        onTriggered: window.showFullScreen()
                    }

                    MenuItem {
                        text: "Exit"
                        onTriggered: Qt.quit()
                    }
                }
            }
        }
    }

    Page {
        anchors.fill: parent

        Page{
            id : drawer
            width: (inPortrait) ? parent.width * 0.66 : parent.width * 0.25
            height: parent.height
            anchors.left: parent.left
            state: "close"
            background: Rectangle{
                anchors.fill: parent
                color: window.palette.alternateBase
            }

            function open(){
                drawer.state = "open"
            }

            function close(){
                drawer.state = "close"
            }

            states: [
                State {
                    name: "open"
                    PropertyChanges {
                        target: drawer;
                        visible: true;
                    }
                },
                State {
                    name: "close"
                    PropertyChanges {
                        target: drawer;
                        visible: false;
                    }
                }
            ]

            transitions: [
                Transition {
                    from: "open"
                    to: "close"
                    SequentialAnimation{
                        PropertyAction {
                            target: drawer;
                            property: "visible";
                            value: true
                        }
                        PropertyAction {
                            target: drawer;
                            property: "width";
                            value: (inPortrait) ? drawer.parent.width * 0.66 : drawer.parent.width * 0.2
                        }
                        NumberAnimation {
                            target: drawer
                            property: "width"
                            to: 1
                            duration: 400
                            easing.type: Easing.InOutQuad
                        }
                        PropertyAction {
                            target: drawer;
                            property: "visible";
                            value: false
                        }
                    }
                },
                Transition {
                    from: "close"
                    to: "open"
                    SequentialAnimation{
                        PropertyAction {
                            target: drawer;
                            property: "visible";
                            value: true
                        }
                        PropertyAction {
                            target: drawer;
                            property: "width";
                            value: 1
                        }
                        NumberAnimation {
                            target: drawer
                            property: "width"
                            to: (inPortrait) ? drawer.parent.width * 0.66 : drawer.parent.width * 0.2
                            duration: 400
                            easing.type: Easing.InOutQuad
                        }
                    }
                }
            ]

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
                    ListElement { title: "Shared Pin"; source: "./list/SharedPinList.qml" }
                    ListElement { title: "Device"; source: "./list/DeviceList.qml" }
                    ListElement { title: "Group"; source: "./list/GroupList.qml" }
                    ListElement { title: "Schedule"; source: "./list/ScheduleList.qml" }
                    ListElement { title: "Shared List"; source: "./list/SharedList.qml" }
                    ListElement { title: "Control Device"; source: "./list/ControlDeviceList.qml" }
                    //ListElement { title: "Settings"; source: "./Settings.qml" }
                }
                ScrollBar.vertical: ScrollBar { }
            }
        }

        StackView {
            id: stackView
            focus: true
            initialItem: "./list/PinList.qml"
            height: parent.height
            width: (!inPortrait && drawer.visible) ? parent.width - drawer.width : parent.width
            anchors.left: drawer.visible ? drawer.right : parent.left
            anchors.right: !inPortrait ? parent.right : undefined
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
