import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import LogView 1.0

Page {

    ColumnLayout {
        id: column
        spacing: 10
        anchors.fill: parent
        ToolBar{
            Layout.fillWidth: true
            clip: true
            RowLayout{
                anchors.fill: parent
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    icon.name: "sync"
                    onClicked: logList.getLogListData()
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Today"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: logList.getTodayLogList()
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Week"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: logList.getThisWeekLogList()
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Month"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: logList.getThisMonthLogList()
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Year"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: logList.getThisYearLogList()
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
        ListView{
            id : listViewElement
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: LogViewModel{
                list: logListView
            }
            delegate: ItemDelegate {
                width: parent.width
                text: model.description
                onClicked: {
                    if(listViewElement.currentIndex != index){
                        listViewElement.currentIndex = index
                    }
                }
                contentItem: Column{
                    spacing: 2
                    width: parent.width
                    Label{
                        id : detailLabel
                        anchors.left: parent.left
                        text: model.description
                    }
                    Label{
                        id: timeLabel
                        anchors.left: parent.left
                        text: model.timeStamp.toLocaleString(Qt.locale("en_US"))
                        font.pixelSize: Qt.application.font.pixelSize * 0.8
                    }
                }
            }
        }
    }
}
