import QtQuick 2.9
import QtQuick.Controls 2.2
import Schedule 1.0

Page {
    anchors.fill: parent
    title: qsTr("Witchcraft House")

    ListView{
        id:listViewElement
        anchors.fill: parent
        currentIndex: 0
        model: ScheduleModel{
            list: scheduleList
        }

        delegate: ItemDelegate {
            width: parent.width
            Row {
                spacing: 20
                Text {
                    text: qsTr("Schedule %1 : ").arg(index + 1)
                }
                Text {
                    text: model.scheduleID
                }
                Text {
                    text: model.scheduleName
                }
                Text {
                    text: model.value
                }
            }
        }

        ScrollBar.vertical: ScrollBar { }
    }
}


