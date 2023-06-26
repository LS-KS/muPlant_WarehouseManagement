import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

/*
  Create ApplicationWindow object as base which stores all other elements
  */

ApplicationWindow {
    property bool init: false
    id: mainWindow
    width: Screen.width/1.5
    minimumWidth : 480
    height: Screen.height/1.5
    minimumHeight: 200
    visible: true
    title: qsTr("Warehouse Management")
    color: "#BDBDBD"
    Dialog {
        id: aboutDialog
        title: "About"
        width : 400
        height: 400
        Text {
            anchors.centerIn: parent
            text: "Copyright 2023, Lennart Schink"
        }
        Button {
            text: qsTr("Close")
            onClicked: aboutDialog.close()
        }
    }
    MenuBar{
        id: menuBar
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Help...") }
            MenuSeparator { }
            Action { text: qsTr("Settings...") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }
        Menu {
            title: qsTr("&Tools")
            Action { text: qsTr("&RFID &Server") }
            Action { text: qsTr("&Camera Application") }
            Action { text: qsTr("&Show Productlist")}
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
    ProcessView{
        id: processView
        width: parent.width/2
        height: parent.height*0.6
        anchors.top: headerLine.bottom
    }

    EventView{
        id: eventlog
        width: mainWindow.width/2
        anchors{
            left: mainWindow.left
            right: processView.right
            top: processView.bottom
            bottom: mainWindow.bottom
        }
    }

    StorageView{
        width: Screen.width /2
        height: Screen.height
        anchors.top: headerLine.bottom
        anchors.left: processView.right
        anchors.bottom: mainWindow.bottom
        anchors.right: mainWindow.right
    }
}
