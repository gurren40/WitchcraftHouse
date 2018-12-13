import QtQuick 2.6
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import Device 1.0

Pane {
    padding: 0
    property string title: "Device List"

    property var delegateComponentMap: {
        "LampDelegate": lampDelegateComponent,
        "lock": lockDelegateComponent,
        "OutletDelegate": outletDelegateComponent,
        "ThermostatDelegate": thermostatDelegateComponent,
        "ThermometerDelegate": thermometerDelegateComponent,
        "CCTVDelegate": cctvDelegateComponent,
        "SwitchDelegate": switchDelegateComponent
    }

    Component{
        id: lampDelegateComponent

        ItemDelegate{
            Rectangle{
                id: lampimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/lampu.png"
                }
            }
            Label{
                text: labelText
                anchors.left: lampimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            Switch{
                id: theswitch
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
            signal todetail(string group, string text, string devicename, string devicevalue)
            MouseArea{
                id: mousearea
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: theswitch.left
                onClicked: {
                    stackView.push("Detail.lamp.ui.qml")
                }
            }
            Component.onCompleted: {
                mousearea.clicked.connect(todetail(group,text,devicename,devicevalue))
            }
        }
    }

    Component{
        id: lockDelegateComponent

        ItemDelegate{
            Rectangle{
                id: lockimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/handle.png"
                }
            }
            Label{
                text: labelText
                anchors.left: lockimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            Switch{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                checked: getValue()
                onClicked: setValue()
                function setValue(){
                    if(checked == true){
                        //value = "true"
                        backend.setValue(uuid,"true")
                    }else if (checked == false){
                        //value = "false"
                        backend.setValue(uuid,"false")
                    }
                }
                function getValue(){
                    if(value == "true"){
                        return true;
                    }else if(value == "false"){
                        return false;
                    }
                }
            }
        }
    }

    Component{
        id: outletDelegateComponent

        ItemDelegate{
            Rectangle{
                id: outletimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/outlet.png"
                }
            }
            Label{
                text: labelText
                anchors.left: outletimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            Switch{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component{
        id: thermostatDelegateComponent

        ItemDelegate{
            Rectangle{
                id: thermostatimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/thermostat.png"
                }
            }
            Label{
                text: labelText
                anchors.left: thermostatimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            SpinBox{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width * 0.25
                value: value
            }
        }
    }

    Component{
        id: thermometerDelegateComponent

        ItemDelegate{
            Rectangle{
                id: thermometerimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/thermostat.png"
                }
            }
            Label{
                text: labelText
                anchors.left: thermometerimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            Label{
                text: value
                anchors.right: parent.right
                anchors.rightMargin:15
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component{
        id: cctvDelegateComponent

        ItemDelegate{
            Rectangle{
                id: cctvimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/cctv.png"
                }
            }
            Label{
                text: labelText
                anchors.left: cctvimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component{
        id: switchDelegateComponent

        ItemDelegate{
            Rectangle{
                id: switchimg
                anchors.left: parent.left
                anchors.leftMargin:15
                anchors.verticalCenter: parent.verticalCenter
                height: parent.height * 0.9
                width: parent.height * 0.9
                color: "#FFFFFF"
                border.width: 1
                border.color: "#000000"
                Image{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: parent.height * 0.9
                    width: parent.height * 0.9
                    source: "./images/switch.png"
                }
            }
            Label{
                text: labelText
                anchors.left: switchimg.right
                anchors.leftMargin:5
                anchors.verticalCenter: parent.verticalCenter
            }
            Switch{
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    ColumnLayout {
        id: column
        spacing: 40
        anchors.fill: parent
        //anchors.topMargin:window and 20

        /*Label {
            Layout.fillWidth: true
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "Delegate controls are used as delegates in views such as ListView."
        }*/

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: DeviceModel{
                list: deviceList
            }

            section.property: "group"
            section.delegate: Pane {
                width: listView.width
                height: sectionLabel.implicitHeight + 20

                Label {
                    id: sectionLabel
                    text: section
                    anchors.centerIn: parent
                }
            }

            delegate: Loader {
                id: delegateLoader
                width: listView.width
                sourceComponent: delegateComponentMap[model.type]

                property string labelText: model.name
                property var value : model.value
                property var uuid: model.uuid
                property ListView view: listView
                property int ourIndex: index

                // Can't find a way to do this in the SwipeDelegate component itself,
                // so do it here instead.
                ListView.onRemove: SequentialAnimation {
                    PropertyAction {
                        target: delegateLoader
                        property: "ListView.delayRemove"
                        value: true
                    }
                    NumberAnimation {
                        target: item
                        property: "height"
                        to: 0
                        easing.type: Easing.InOutQuad
                    }
                    PropertyAction {
                        target: delegateLoader
                        property: "ListView.delayRemove"
                        value: false
                    }
                }
            }
        }
    }
}
