
import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
import QtQuick.Window 2.15

Window {
    visible: true
    width: 300
    height: 480
    title: qsTr("Preferences and Settings")
    Material.theme: Material.Dark
    visibility: Window.Windowed

    Rectangle {
        id: mainRect
        anchors.fill: parent
        color :"black"
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
            RowLayout{

                Label{
                    text: qsTr("IP Address")
                    Layout.fillWidth: true
                }
                TextField{
                    id: modbusIpAddr
                    text: ""
                    Layout.fillWidth: true
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            RowLayout{

                Label{
                    text: qsTr("IP Port")
                    Layout.fillWidth: true
                }
                TextField{
                    id: modbusIpPort
                    text: ""
                    Layout.fillWidth: true
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            RowLayout{
                Label{
                    text: qsTr("Max.Reconnects")
                    Layout.fillWidth: true
                }
                TextField{
                    id: modbusMaxReconnects
                    text: ""
                    Layout.fillWidth: true
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
                    console.log(ipAddr.text)
                    console.log(ipPort.text)
                }
            }
            RowLayout{
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
            RowLayout{

                Label{
                    text: qsTr("IP Address")
                    Layout.fillWidth: true
                }
                TextField{
                    id: abbIpAddr
                    text: ""
                    Layout.fillWidth: true
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            RowLayout{

                Label{
                    text: qsTr("IP Port")
                    Layout.fillWidth: true
                }
                TextField{
                    id: abbIpPort
                    text: ""
                    Layout.fillWidth: true
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
                    console.log(ipAddr.text)
                    console.log(ipPort.text)
                }
            }
        }
    }
}
