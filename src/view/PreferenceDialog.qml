import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

Dialog {
    id: preferenceDialog
    title: qsTr("Preferences and Settings")
    Rectangle {
        id: mainRect
        anchors.fill: parent
        Text{
            id: text1
            text: qsTr("Modbus Preferences")
            color : "white"
            anchors{
                top: parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
            }
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
        }
        ColumnLayout{
            anchors{
                top: text1.bottom
                topMargin: 20
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
                bottomMargin: 10
            }
            Row{

                Label{
                    text: qsTr("IP Address")
                    width: parent.width/3
                    height: modbusIpAddr.height
                    verticalAlignment: Text.AlignVCenter

                }
                TextField{
                    id: modbusIpAddr
                    text: ""
                    width: parent.width*2/3
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{

                Label{
                    text: qsTr("IP Port")
                    width: parent.width/3
                    height: modbusIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: modbusIpPort
                    text: ""
                    width: parent.width*2/3
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{
                Label{
                    text: qsTr("Max.Reconnects")
                    width: parent.width/3
                    height: modbusMaxReconnects.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: modbusMaxReconnects
                    text: ""
                    width: parent.width*2/3
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Button{
                id: modbusSaveButton
                text: qsTr("Save")
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                Layout.fillHeight: true
                onClicked: {
                    console.log("Save button clicked")
                    console.log(modbusIpAddr.text)
                    console.log(modbusIpPort.text)
                }
            }
            Row{
                id: seperator
                Rectangle{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.maximumHeight: 3
                    color: "white"
                }
            }
            Text{
                id: text2
                text: qsTr("ABB Robot Preferences")
                color : "white"
                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
            }
            Row{

                Label{
                    text: qsTr("IP Address")
                    width: parent.width/3
                    height: abbIpAddr.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: abbIpAddr
                    text: ""
                    width: parent.width*2/3
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{

                Label{
                    text: qsTr("IP Port")
                    width: parent.width/3
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: abbIpPort
                    text: ""
                    width: parent.width*2/3
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Button{
                id: abbSaveButton
                text: qsTr("Save")
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                Layout.fillHeight: true
                onClicked: {
                    console.log("Save button clicked")
                    console.log(abbIpAddr.text)
                    console.log(abbIpPort.text)
                }
            }
        }

    }
    Connections {
        target: preferenceController

        function onSendPreferences(modbusip, modbusport, modbusmaxtries, abbip, abbport) {
            console.log("Preferences loaded");
            modbusIpAddr.text = preferenceController.modbusIpAddr;
            modbusIpPort.text = preferenceController.modbusIpPort;
            modbusMaxReconnects.text = preferenceController.modbusMaxReconnects;
            abbIpAddr.text = preferenceController.abbIpAddr;
            abbIpPort.text = preferenceController.abbIpPort;
        }
    }
    onOpened: {
        preferenceController.loadPreferences();
    }
}
