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
    visibility: user.isFullScreen ? "FullScreen" : "Maximized"


    //timer and stuff
    Timer{
        id : initTimer
        repeat: false
        interval: 200
        running: true
        onTriggered: {
            user.initActivity()
            user.getAllData()
        }
    }
    Timer{
        id : getAllDataTimer
        repeat: true
        interval: 60000
        running: true
        onTriggered: {
            user.getAllData()
        }
    }

    //! [orientation]
    readonly property bool inPortrait: window.width < window.height
    //! [orientation]
    Material.theme: user.darkTheme ? Material.Dark : Material.Light
    Material.primary: Material.background //user.darkTheme ? Material.background : Material.Orange
    Material.accent: Material.Orange //user.darkTheme ? Material.Grey :
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
                //listView.currentIndex = -1
            }
            else{
                exitDialog.open()
            }
        }
    }

    header: ToolBar {
        //Material.foreground: "white"
        id : toolBar
        contentHeight: toolButton.implicitHeight

        RowLayout {
            spacing: 20
            anchors.fill: parent
            ToolButton {
                id: toolButton
                icon.name: (drawer.visible || (stackView.depth > 1)) ? "chevron_left" : "menu"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    if(stackView.depth > 1){
                        stackView.pop()
                    }
                    else{
                        if(drawer.visible){
                            drawer.close()
                        }
                        else{
                            drawer.open()
                        }
                    }
                }
                //anchors.left: parent.left
                Layout.alignment: Qt.AlignLeft
            }

            Label {
                text: stackView.currentItem.title
                font.bold: true
                //anchors.centerIn: parent
                Layout.alignment: Qt.AlignHCenter
            }

            ToolButton {
                id: menuButton
                icon.name: "refresh"
                icon.color: user.isOnline ? "green" : "red"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                //anchors.right: parent.right
                Layout.alignment: Qt.AlignRight
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
            width: (inPortrait) ? parent.width * 0.8 : parent.width * 0.618
            height: parent.height - toolBar.contentHeight
            y : toolBar.contentHeight
            //modal: inPortrait
            //interactive: inPortrait
            //position: inPortrait ? 0 : 1
            //visible: !inPortrait
            visible: false

            ListView{
                id : listView
                clip: true
                anchors.fill: parent
                currentIndex: 0
                header : ItemDelegate{
                    id : listViewHeader
                    clip : true
                    width: parent.width
                    height: width * 0.55
                    icon.name: "house"
                    icon.height: 48
                    icon.width: 48
                    icon.color: user.isOnline ? "green" : "red"
                    text: qsTr("Witchcraft House")
                    font.bold: true
                    font.pointSize: 20
                    contentItem : Column{
                        clip: true
                        width: parent.width
                        height: parent.height
                        RoundButton{
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: parent.height * 0.618
                            height: parent.height * 0.618
                            icon.name: "witchcraft"
                            icon.color: "white"
                            icon.height: height * 0.8
                            icon.width: width * 0.8
                            onClicked: user.reconnect()
                            Material.background: user.isOnline ? Material.Green : Material.Red
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            id: headerText
                            text: qsTr("Witchcraft House")
                            font.family: "URW Gothic"
                            font.pointSize: 20
                            font.bold: true
                            color: "white"
                        }
                    }

                    background: Image{
                        width: parent.width
                        height: parent.height
                        source: "/images/drawer_header.jpeg"
                    }
                    onClicked: {
                        user.restartService()
                        initTimer.start()
                    }
                }

                delegate: ItemDelegate {
                    icon.name: model.icon
                    text: model.title
                    width: parent.width
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        //inPortrait ? drawer.close() : undefined
                        drawer.close()
                        if(listView.currentIndex != index){
                            listView.currentIndex = index
                            if(model.title === "Home"){
                                stackView.replace(model.source,{isShared : false})
                            }
                            else if(model.title === "Shared Pin"){
                                stackView.replace(model.source,{isShared : true})
                            }
                            else{
                                stackView.replace(model.source)
                            }
                        }
                    }
                }

                model: ListModel{
                    ListElement { icon : "chevron_right"; title: "Home"; source: "./list/PinList.qml" }
                    //ListElement { title: "Shared Pin"; source: "./list/SharedPinList.qml" }
                    ListElement { icon : "chevron_right"; title: "Shared Pin"; source: "./list/PinList.qml" }
                    ListElement { icon : "chevron_right"; title: "Device"; source: "./list/DeviceList.qml" }
                    ListElement { icon : "chevron_right"; title: "Group"; source: "./list/GroupList.qml" }
                    ListElement { icon : "chevron_right"; title: "Schedule"; source: "./list/ScheduleList.qml" }
                    ListElement { icon : "chevron_right"; title: "Shared List"; source: "./list/SharedList.qml" }
                    ListElement { icon : "chevron_right"; title: "Control Device"; source: "./list/ControlDeviceList.qml" }
                    ListElement { icon : "chevron_right"; title: "Settings"; source: "./etc/settings.qml" }
                }

                footer: ItemDelegate{
                    id : exitDelegate
                    width: parent.width
                    text: "Exit"
                    icon.name: "power"
                    icon.color: "red"
                    onClicked: Qt.quit()
                }
            }
        }

        StackView {
            id: stackView
            focus: true
            initialItem: "./list/PinList.qml"
            //height: parent.height - toolBar.contentHeight
            //width: inPortrait ? parent.width : parent.width - (drawer.width * 2)
            //anchors.centerIn: parent
            //anchors.top : toolBar.bottom
            anchors.fill : parent

//            pushEnter : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: 400
//                }
//            }
//            pushExit : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 1
//                    to: 0
//                    duration: 400
//                }
//            }
//            popEnter : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: 400
//                }
//            }
//            popExit : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 1
//                    to: 0
//                    duration: 400
//                }
//            }
//            replaceEnter : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 0
//                    to: 1
//                    duration: 400
//                }
//            }
//            replaceExit : Transition {
//                PropertyAnimation{
//                    property: "opacity"
//                    from: 1
//                    to: 0
//                    duration: 400
//                }
//            }
        }
    }
    RoundButton {
        id: createButton
        //text: qsTr("+")
        icon.name: "plus"
        icon.height: 36
        icon.width: 36
        icon.color: Material.background
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 70
        width: height
        //font.pointSize: 35
        onClicked: stackView.currentItem.create()
        visible: stackView.currentItem.canCreate
    }
}
