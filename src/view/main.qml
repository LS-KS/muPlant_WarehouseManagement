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
        anchors.centerIn: parent
        Text {
            anchors.centerIn: parent
            text: "Created in 2023, Lennart Schink\nQuestions? Contact me via mail:\nL.i.schink@gmail.com"
        }
        Row {
            anchors{
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }

            Button {
                text: qsTr("Close")
                onClicked: aboutDialog.close()
            }
        }
    }
    PreferenceDialog{
        id : preferenceDialog
        width: 600
        height: Screen.height
        anchors.centerIn: parent
    }


    MenuBar{
        id: menuBar
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&Help...")
                onTriggered: {
                    var helpComponent = Qt.createComponent("Help.qml");
                    if (helpComponent.status === Component.Ready){
                        helpComponent.createObject();
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
            Action { 
                text: qsTr("&RFID &Server") 
                onTriggered: {
                    console.log("Start RFID-Server...")
                    var rfidServerComponent = Qt.createComponent("RFIDServerPlugin.qml");
                    if (rfidServerComponent.status === Component.Ready){
                        rfidServerComponent.createObject();
                    }
                    if(rfidServerComponent.status === Component.Error){
                        console.log("Error while loading RFID-Server-Plugin: "+ rfidServerComponent.errorString())
                    }
                }

            }
            Action {
                text: qsTr("&tocktaking Application")
                onTriggered: {
                    console.log("stocktaker action triggered")
                    var stocktakerComponent = Qt.createComponent("StocktakingPlugin.qml")
                    if(stocktakerComponent.status === Component.Ready){
                        var stocktakerWindow = stocktakerComponent.createObject()
                        stocktakerWindow.show()
                    }
                }
            }
            Action {
                text: qsTr("&Show Productlist")
                onTriggered: {
                    var plComponent = Qt.createComponent("ProductList.qml");
                    if (plComponent.status === Component.Ready){
                        plComponent.createObject();
                    }
                }
            }
            Action {
                text: qsTr("&Manual &Commission &Control")
                onTriggered: {
                    var mccPlugIn = Qt.createComponent("MCCPlugin.qml")
                    if(mccPlugIn.status === Component.Ready){
                        mccPlugIn.createObject();
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
    // Fill window with elements
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
        onClicked: {
            agentService.setupAgentService();
            opcuaService.startOpcuaService();
            visible = false;
            stopButton.visible = true;
        } 
    }
    Button{
        id: stopButton
        text: qsTr("Stop")
        width: parent.width/12
        height: parent.height/10
        visible: false
        anchors {
            left: processView.left
            top: headerLine.bottom
            margins: 10
        }
        onClicked: {
            agentService.stopAgentService();
            opcuaService.stopOpcuaService();
            visible= false;
            startButton.visible= true;
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
