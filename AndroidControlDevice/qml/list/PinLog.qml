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
        ItemDelegate{
            Layout.fillWidth: true
            clip: true
            icon.name: firstBar.visible ? "expand_less" : "expand_more"
            text: "Menu"
            onClicked: {
                firstBar.visible ? firstBar.visible = false : firstBar.visible = true
                secondBar.visible ? secondBar.visible = false : secondBar.visible = true
                thirdBar.visible ? thirdBar.visible = false : thirdBar.visible = true
            }
        }

        ToolBar{
            id : firstBar
            visible: false
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
                    id:weekbutton
                    property variant theValue: [1,2,3,4,5,6,7]
                    Layout.alignment: Qt.AlignLeft
                    text: "Week"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        logList.getThisWeekPinLogList(selectPin.currentText)
                        yearly.visible = false
                        monthly.visible = false;
                        weekly.visible = true;
                        weekbutton.theValue = [pinLogListView.dw1
                                               ,pinLogListView.dw2
                                               ,pinLogListView.dw3
                                               ,pinLogListView.dw4
                                               ,pinLogListView.dw5
                                               ,pinLogListView.dw6
                                               ,pinLogListView.dw7
                                ]
                        console.log(pinLogListView.dw1)
                        weeklyBarSet.values = weekbutton.theValue
                        weeklyBarSet.setAxisValue();
                        weeklyBarSet.values = weekbutton.theValue
                        summaryLabel.text = ""
                    }
                }
                ToolButton{
                    id : monthbutton
                    property variant theValue: [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
                    Layout.alignment: Qt.AlignLeft
                    text: "Month"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked:{
                        logList.getThisMonthPinLogList(selectPin.currentText)
                        yearly.visible = false
                        monthly.visible = true;
                        weekly.visible = false;
                        monthbutton.theValue = [pinLogListView.dm1
                                               ,pinLogListView.dm2
                                               ,pinLogListView.dm3
                                               ,pinLogListView.dm4
                                               ,pinLogListView.dm5
                                               ,pinLogListView.dm6
                                               ,pinLogListView.dm7
                                               ,pinLogListView.dm8
                                               ,pinLogListView.dm9
                                               ,pinLogListView.dm10
                                               ,pinLogListView.dm11
                                               ,pinLogListView.dm12
                                               ,pinLogListView.dm13
                                               ,pinLogListView.dm14
                                               ,pinLogListView.dm15
                                               ,pinLogListView.dm16
                                               ,pinLogListView.dm17
                                               ,pinLogListView.dm18
                                               ,pinLogListView.dm19
                                               ,pinLogListView.dm20
                                               ,pinLogListView.dm21
                                               ,pinLogListView.dm22
                                               ,pinLogListView.dm23
                                               ,pinLogListView.dm24
                                               ,pinLogListView.dm25
                                               ,pinLogListView.dm26
                                               ,pinLogListView.dm27
                                               ,pinLogListView.dm28
                                               ,pinLogListView.dm29
                                               ,pinLogListView.dm30
                                               ,pinLogListView.dm31
                                ]
                        console.log(pinLogListView.dm29)
                        monthlyBarSet.values = monthbutton.theValue;
                        monthlyBarSet.setAxisValue();
                        monthlyBarSet.values = monthbutton.theValue;
                        if(pinLogListView.datatype == 0){
                            summaryLabel.text = "Average this month = "+pinLogListView.thisMonth
                        }
                        else if(pinLogListView.datatype == 1){
                            summaryLabel.text = "Usage hour this month = "+pinLogListView.thisMonth
                        }
                    }
                }
                ToolButton{
                    id : yearbutton
                    property variant theValue: [1,2,3,4,5,6,7,8,9,10,11,12]
                    Layout.alignment: Qt.AlignLeft
                    text: "Year"
                    font.pixelSize: Qt.application.font.pixelSize
                    onClicked: {
                        logList.getThisYearPinLogList(selectPin.currentText)
                        yearly.visible = true
                        monthly.visible = false;
                        weekly.visible = false;
                        yearbutton.theValue = [pinLogListView.month1
                                               ,pinLogListView.month2
                                               ,pinLogListView.month3
                                               ,pinLogListView.month4
                                               ,pinLogListView.month5
                                               ,pinLogListView.month6
                                               ,pinLogListView.month7
                                               ,pinLogListView.month8
                                               ,pinLogListView.month9
                                               ,pinLogListView.month10
                                               ,pinLogListView.month11
                                               ,pinLogListView.month12
                                ]
                        console.log(pinLogListView.month7)
                        yearlyBarSet.values = yearbutton.theValue
                        yearlyBarSet.setAxisValue();
                        yearlyBarSet.values = yearbutton.theValue
                        if(pinLogListView.datatype == 0){
                            summaryLabel.text = "Average this year = "+pinLogListView.thisYear
                        }
                        else if(pinLogListView.datatype == 1){
                            summaryLabel.text = "Usage hour this year = "+pinLogListView.thisYear
                        }
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
        ToolBar{
            id : secondBar
            visible: false
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
            id : thirdBar
            visible: false
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
                            axisY: ValueAxis {    //  <- custom ValueAxis attached to the x-axis
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
                                            yearlyValueAxis.max = max + 1;
                                            yearlyValueAxis.min = 0;
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
                            axisY: ValueAxis {    //  <- custom ValueAxis attached to the x-axis
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
                                            monthlyValueAxis.max = max + 1;
                                            monthlyValueAxis.min = 0;
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
                                            weeklyValueAxis.max = max + 1;
                                            weeklyValueAxis.min = 0;
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
