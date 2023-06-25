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
    width: Screen.width
    minimumWidth : 480
    height: Screen.height
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
}
