import QtQuick
import QtQuick.Window
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

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
}