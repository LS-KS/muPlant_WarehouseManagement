import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
import QtQuick.Window 2.15
import QtWebEngine 1.1


Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: "Help Menu"
    WebEngineView {
        id: webView
        //url: "http://www.example.com"
        anchors.fill: parent

    }
    Component.onCompleted: {
            var path = Qt.resolvedUrl("../../sphinx_build/index.html")
            webView.url = path
    }
}
