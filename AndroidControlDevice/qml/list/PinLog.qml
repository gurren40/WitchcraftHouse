import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2
import QtCharts 2.3
import LogView 1.0
import Pin 1.0

Page {

    ColumnLayout {
        id: column
        spacing: 10
        anchors.fill: parent
        ToolBar{
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            clip: true
            RowLayout{
                anchors.fill: parent
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    icon.name: "sync"
                    onClicked: logList.getPinLogListData()
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Today"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        listViewElement.visible = true
                        lineSeriesElement.visible = false
                        logList.getTodayPinLogList(selectPin.currentText)
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Week"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        logList.getThisWeekPinLogList(selectPin.currentText)
                        yearly.visible = false
                        monthly.visible = false;
                        weekly.visible = true;
                        weeklyBarSet.values = [pinLogListView.readDayWeek(1)
                                               ,pinLogListView.readDayWeek(2)
                                               ,pinLogListView.readDayWeek(3)
                                               ,pinLogListView.readDayWeek(4)
                                               ,pinLogListView.readDayWeek(5)
                                               ,pinLogListView.readDayWeek(6)
                                               ,pinLogListView.readDayWeek(7)
                                ]
                        console.log(pinLogListView.readDayWeek(5))
                        summaryLabel.text = ""
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Month"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked:{
                        logList.getThisMonthPinLogList(selectPin.currentText)
                        yearly.visible = false
                        monthly.visible = true;
                        weekly.visible = false;
                        monthlyBarSet.values = [pinLogListView.readDayMonth(1)
                                               ,pinLogListView.readDayMonth(2)
                                               ,pinLogListView.readDayMonth(3)
                                               ,pinLogListView.readDayMonth(4)
                                               ,pinLogListView.readDayMonth(5)
                                               ,pinLogListView.readDayMonth(6)
                                               ,pinLogListView.readDayMonth(7)
                                               ,pinLogListView.readDayMonth(8)
                                               ,pinLogListView.readDayMonth(9)
                                               ,pinLogListView.readDayMonth(10)
                                               ,pinLogListView.readDayMonth(11)
                                               ,pinLogListView.readDayMonth(12)
                                               ,pinLogListView.readDayMonth(13)
                                               ,pinLogListView.readDayMonth(14)
                                               ,pinLogListView.readDayMonth(15)
                                               ,pinLogListView.readDayMonth(16)
                                               ,pinLogListView.readDayMonth(17)
                                               ,pinLogListView.readDayMonth(18)
                                               ,pinLogListView.readDayMonth(19)
                                               ,pinLogListView.readDayMonth(20)
                                               ,pinLogListView.readDayMonth(21)
                                               ,pinLogListView.readDayMonth(22)
                                               ,pinLogListView.readDayMonth(23)
                                               ,pinLogListView.readDayMonth(24)
                                               ,pinLogListView.readDayMonth(25)
                                               ,pinLogListView.readDayMonth(26)
                                               ,pinLogListView.readDayMonth(27)
                                               ,pinLogListView.readDayMonth(28)
                                               ,pinLogListView.readDayMonth(29)
                                               ,pinLogListView.readDayMonth(30)
                                               ,pinLogListView.readDayMonth(31)
                                ]
                        console.log(pinLogListView.readDayMonth(7))
                        monthlyBarSet.setAxisValue();
                        if(pinLogListView.datatype == 0){
                            summaryLabel.text = "Average this month = "+pinLogListView.readMonth(pinLogListView.month)
                        }
                        else if(pinLogListView.datatype == 1){
                            summaryLabel.text = "Usage hour this month = "+pinLogListView.readYear(pinLogListView.month)
                        }
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Year"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        logList.getThisYearPinLogList(selectPin.currentText)
                        yearly.visible = true
                        monthly.visible = false;
                        weekly.visible = false;
                        yearlyBarSet.values = [pinLogListView.readMonth(1)
                                               ,pinLogListView.readMonth(2)
                                               ,pinLogListView.readMonth(3)
                                               ,pinLogListView.readMonth(4)
                                               ,pinLogListView.readMonth(5)
                                               ,pinLogListView.readMonth(6)
                                               ,pinLogListView.readMonth(7)
                                               ,pinLogListView.readMonth(8)
                                               ,pinLogListView.readMonth(9)
                                               ,pinLogListView.readMonth(10)
                                               ,pinLogListView.readMonth(11)
                                               ,pinLogListView.readMonth(12)
                                ]
                        yearlyBarSet.setAxisValue();
                        if(pinLogListView.datatype == 0){
                            summaryLabel.text = "Average this year = "+pinLogListView.readYear(pinLogListView.year)
                        }
                        else if(pinLogListView.datatype == 1){
                            summaryLabel.text = "Usage hour this year = "+pinLogListView.readYear(pinLogListView.year)
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
        ToolBar{
            Layout.fillWidth: true
            clip: true
            horizontalPadding: 15
            RowLayout{
                anchors.fill: parent
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Hourly"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        pinLogListView.datatype = 1
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "Mean"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        pinLogListView.datatype = 0
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
        ToolBar{
            Layout.fillWidth: true
            clip: true
            horizontalPadding: 15
            RowLayout{
                anchors.fill: parent
                ComboBox{
                    property string displayName : "Select Pin"
                    id : selectPin
                    Layout.fillWidth: true
                    textRole: "UUID"
                    displayText: displayName
                    model: PinModel{
                        list: pinList
                    }
                    delegate: ItemDelegate{
                        width: parent.width
                        icon.name : model.iconName
                        text: model.pinName
                        onClicked: {
                            console.log(selectPin.currentText)
                            selectPin.displayName = model.pinName
                        }
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "ListView"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        listViewElement.visible = true
                        lineSeriesElement.visible = false
                    }
                }
                ToolButton{
                    Layout.alignment: Qt.AlignLeft
                    text: "BarSeries"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        listViewElement.visible = false
                        lineSeriesElement.visible = true
                    }
                }
            }
        }

        ListView{
            id : listViewElement
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: PinLogViewModel{
                list: pinLogListView
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
        ColumnLayout{
            id : lineSeriesElement
            visible: false
            Layout.fillHeight: true
            Layout.fillWidth: true
            Label{
                Layout.alignment: Qt.AlignHCenter
                id : summaryLabel
                text: "summary"
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                visible: !(yearly.visible || monthly.visible || weekly.visible)
            }
            ScrollView{
                Layout.fillHeight: true
                Layout.fillWidth: true
                contentWidth: width
                contentHeight: (height > 300) ? height : 300
                ScrollBar.vertical.interactive: true
                clip: true
                Column{
                    id : chartColumn
                    spacing: 15
                    height : (parent.height > 300) ? parent.height : 300
                    width: parent.width
                    clip: true
                    ChartView {
                        id : yearly
                        clip: true
                        visible: false
                        title: "Line"
                        width: parent.width
                        height: (parent.height > 300) ? parent.height : 300
                        //antialiasing: true

                        BarSeries {
                            //id : yearly
                            //visible: false
                            name: "Coba series"
                            axisX: BarCategoryAxis {categories: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" ]}
                            axisY: ValueAxis {    //  <- custom ValueAxis attached to the y-axis
                                id: yearlyValueAxis
                            }
                            BarSet{
                                id : yearlyBarSet
                                label: "This Year"
                                values: [1,2,3,4,5,6,7,8,9,10,11,12]
                                function setAxisValue(){
                                    var max = 0;
                                    for(var i = 0; i<values.length;i++){
                                        if(max < values[i]){
                                            max = values[i];
                                        }
                                        if(max > 0){
                                            yearlyValueAxis.max = max;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    ChartView {
                        id : monthly
                        clip: true
                        visible: false
                        title: "Line"
                        width: parent.width
                        height: (parent.height > 300) ? parent.height : 300
                        //antialiasing: true


                        BarSeries {
                            //id : monthly
                            //visible: false
                            name: "Coba series"
                            axisX: BarCategoryAxis { categories: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" ]}
                            axisY: ValueAxis {    //  <- custom ValueAxis attached to the y-axis
                                id: monthlyValueAxis
                            }
                            BarSet{
                                id : monthlyBarSet
                                label: "This Month"
                                values: [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
                                function setAxisValue(){
                                    var max = 0;
                                    for(var i = 0; i<values.length;i++){
                                        if(max < values[i]){
                                            max = values[i];
                                        }
                                        if(max > 0){
                                            monthlyValueAxis.max = max;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    ChartView {
                        id : weekly
                        clip: true
                        visible: false
                        title: "Line"
                        width: parent.width
                        height: (parent.height > 300) ? parent.height : 300
                        //antialiasing: true
                        BarSeries {
                            //id : weekly
                            //visible: false
                            name: "Coba series"
                            axisX: BarCategoryAxis {categories: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]}
                            axisY: ValueAxis {    //  <- custom ValueAxis attached to the y-axis
                                id: weeklyValueAxis
                            }
                            BarSet{
                                id : weeklyBarSet
                                label: "This Week"
                                values: [1,2,3,4,5,6,7]
                                function setAxisValue(){
                                    var max = 0;
                                    for(var i = 0; i<values.length;i++){
                                        if(max < values[i]){
                                            max = values[i];
                                        }
                                        if(max > 0){
                                            weeklyValueAxis.max = max;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
