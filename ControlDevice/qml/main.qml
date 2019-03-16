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
    onWidthChanged: function(){
        if(width > 520){
            drawer.open()
        }
        else if(width <= 520){
            drawer.close()
        }
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
        }
    }

    header: ToolBar {
        id : toolBar
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u2630"
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

        Rectangle{
            id : drawer
            width: (parent.width <= 520) ? parent.width * 0.66 : 240
            height: parent.height
            anchors.left: parent.left
            //visible: false
            state: "close"
            color: window.palette.alternateBase
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
                        visible : true;
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
                            property: "visible"
                            value: true
                        }

                        PropertyAction {
                            target: drawer;
                            property: "width"
                            value: (drawer.parent.width <= 520) ? drawer.parent.width * 0.66 : 240
                        }

                        PropertyAnimation {
                            target: drawer
                            property: "width"
                            duration: 200
                            to : 1
                            easing.type: Easing.OutInQuad
                        }

                        PropertyAction {
                            target: drawer;
                            property: "visible"
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
                            property: "visible"
                            value: true
                        }

                        PropertyAction {
                            target: drawer;
                            property: "width"
                            value: 1
                        }

                        PropertyAnimation {
                            target: drawer
                            property: "width"
                            duration: 200
                            to : (drawer.parent.width <= 520) ? drawer.parent.width * 0.66 : 240
                            easing.type: Easing.InOutQuad
                        }

                        PropertyAction {
                            target: drawer;
                            property: "visible"
                            value: false
                        }
                    }
                }
            ]

            ListView{
                id : listView
                anchors.fill: parent
                focus: true
                currentIndex: 0
                delegate: ItemDelegate {
                    text: model.title
                    width: parent.width
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        if(listView.currentIndex != index){
                            listView.currentIndex = index
                            stackView.push(model.source)
                            if(window.width <= 520){
                                drawer.close()
                            }
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
            initialItem: "./list/PinList.qml"
            height: parent.height
            anchors.left: (drawer.visible) ? drawer.right : parent.left
            //width: parent.width
            width: ((parent.width > 520) && (drawer.visible)) ? parent.width - drawer.width : parent.width
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
