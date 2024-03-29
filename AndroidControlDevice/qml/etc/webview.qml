import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtWebView 1.1
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Universal 2.12

Page{
    id : webViewPage
    title: webView.title
    property string url: ""
    property bool canCreate : false
    padding: 20
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
            Column{
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20
                TextField{
                    id : urlField
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    text: webViewPage.url
                    onEditingFinished: webView.url = text
                    enabled: true
                }
                Row{
                    spacing: 30
                    //width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Button{
                        enabled: webView.canGoBack
                        icon.name: "back"
                        onClicked: webView.goBack()
                    }
                    Button{
                        icon.name: webView.loading ? "close" : "refresh"
                        onClicked: webView.loading ? webView.stop() : webView.reload()
                    }
                    Button{
                        enabled: webView.canGoForward
                        icon.name: "forward"
                        onClicked: webView.goForward()
                    }
                }
                ItemDelegate{
                    width: parent.width
                    height: parent.width * 3 / 4
                    contentItem: WebView{
                        anchors.horizontalCenter: parent.horizontalCenter
                        id : webView
                        anchors.centerIn: parent
                        width: parent.width
                        height: parent.width * 3 / 4
                        url : webViewPage.url
                        onUrlChanged: urlField.text = url
                    }
                }
            }
        }
    }
}
