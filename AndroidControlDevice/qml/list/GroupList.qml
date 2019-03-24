import QtQuick 2.9
import QtQuick.Controls 2.2
import Group 1.0

Page {
    anchors.fill: parent
    title: qsTr("Group List")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: GroupModel{
            list: groupList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Group %1 : ").arg(index + 1)
                }
                Text {
                    text: model.groupID
                }
                Text {
                    text: model.groupName
                }
                Text {
                    text: model.description
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


