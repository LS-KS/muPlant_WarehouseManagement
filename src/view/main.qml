import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs


/*
  Create ApplicationWindow object as base which stores all other elements
  */

Window {
    Material.accent: Material.Dark
    property bool init: false
    id: mainWindow
    width: Screen.width*2/3
    minimumWidth : 480
    height: Screen.height*2/3
    minimumHeight: 200
    visible: true
    title: qsTr("Warehouse Management")
    color: "#BDBDBD"

    Dialog {
        id: aboutDialog
        title: "About"
        width : 400
        height: 400
        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            text: "Copyright 2023, Lennart Schink"
        }
        Button {
            text: qsTr("Close")
            onClicked: aboutDialog.close()
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
    PreferenceDialog{
        id : preferenceDialog
        width: 500
        height: 800
        anchors.centerIn: parent
    }
    MenuBar{
        id: menuBar
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Help...")
                onTriggered: {
                    var component = Qt.createComponent("Help.qml");
                    if (component.status === Component.Ready){
                        component.createObject();
                    }
                }
            }
            MenuSeparator { }
            Action { text: qsTr("Settings...")
                onTriggered: {
                    preferenceDialog.open()
                }
            }
            MenuSeparator { }
            Action { text: qsTr("&Quit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("&Tools")
            Action { text: qsTr("&RFID &Server") }
            Action { text: qsTr("&Camera Application") }
            Action {
                text: qsTr("&Show Productlist")
                onTriggered: {
                    var component = Qt.createComponent("ProductList.qml");
                    if (component.status === Component.Ready){
                        component.createObject();
                    }
                }
            }
        }
        Menu {
            title: qsTr("&About")
            Action { text: qsTr("&About")
                onTriggered: {
                    aboutDialog.open()
                }
            }
        }
    }
    HeaderLine{
        id: headerLine
        anchors {
            left: parent.left
            right: parent.right
            top: menuBar.bottom
        }
    }
    // Ab hier Fensterfläche füllen
    ProcessView{
        id: processView
        height: parent.height/2*1.2-headerLine.height
        width: parent.width/2
        anchors {
            left: parent.left
            top: headerLine.bottom
        }
    }
    Button{
        id: startButton
        text: qsTr("Start")
        width: parent.width/12
        height: parent.height/10
        anchors {
            left: processView.left
            top: headerLine.bottom
            margins: 10
        }
    }
    StackLayoutView{
        id: stackLayoutView
        height: parent.height/2-headerLine.height
        width: parent.width/2
        anchors {
            left: parent.left
            top: processView.bottom
            bottom: parent.bottom
        }
    }
    StorageView{
        id: storageView
        height: parent.height-headerLine.height
        width: parent.width/2
        anchors {
            left: processView.right
            top: headerLine.bottom
        }
    }

}
