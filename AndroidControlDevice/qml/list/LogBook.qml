import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import Group 1.0
import Icon 1.0

Page {
    property bool canCreate: false
    property int listID : 2
    padding: 0
    //function create(){stackView.push("../create/createGroup.qml")}
    //anchors.fill: parent
    title: qsTr("Log Book")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        ActivityLog {
        }

        PinLog {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Activity Log")
        }
        TabButton {
            text: qsTr("Pin Log")
        }
    }
}


