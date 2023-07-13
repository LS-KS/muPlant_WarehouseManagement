import QtQuick 2.9
import QtQuick 2.15
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
                    width: parent.width/3-25
                    height: modbusIpAddr.height
                    verticalAlignment: Text.AlignVCenter

                }
                TextField{
                    id: modbusIpAddr
                    text: ""
                    width: parent.width*2/3-25
                    validator: RegularExpressionValidator {
                        regularExpression: /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
                        // /^means string must start at the beginning
                        // {1,3} means 1 to 3 digits
                        // \. means a dot, [0-9] means a digit
                        // so /^(?:[0-9]{1,3}\.){3} means 1 to 3 digits followed by a dot, repeated 3 times
                        // followed by 1 to 3 digits
                    }
                }
                Image{
                    id: modbusIpError
                    source: "../assets/icon_warning.svg"
                    width: Image.PreseveAspectFit
                    height: modbusIpAddr.height
                    visible: false
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{

                Label{
                    text: qsTr("IP Port")
                    width: parent.width/3-25
                    height: modbusIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: modbusIpPort
                    text: ""
                    width: parent.width*2/3-25
                     validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{1,5}$/
                    }
                }
                Image{
                    id: modbusPortError
                    source: "../assets/icon_warning.svg"
                    width: Image.PreseveAspectFit
                    height: modbusIpPort.height
                    visible: false
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{
                Label{
                    text: qsTr("Max.Reconnects")
                    width: parent.width/3-25
                    height: modbusMaxReconnects.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: modbusMaxReconnects
                    text: ""
                    width: parent.width*2/3-25
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{1,2}$/
                    }
                }
                Image{
                    id: modbusReconnectError
                    source: "../assets/icon_warning.svg"
                    width: Image.PreseveAspectFit
                    height: modbusIpPort.height
                    visible: false
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
                    preferenceController.setModBusPreferences(modbusIpAddr.text, modbusIpPort.text, modbusMaxReconnects.text);
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
                    width: parent.width/3-25
                    height: abbIpAddr.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: abbIpAddr
                    text: ""
                    width: parent.width*2/3-25
                    validator: RegularExpressionValidator {
                        regularExpression: /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
                        // /^means string must start at the beginning
                        // {1,3} means 1 to 3 digits
                        // \. means a dot, [0-9] means a digit
                        // so /^(?:[0-9]{1,3}\.){3} means 1 to 3 digits followed by a dot, repeated 3 times
                        // followed by 1 to 3 digits
                    }
                }
                Image{
                    id: abbIpError
                    source: "../assets/icon_warning.svg"
                    width: Image.PreseveAspectFit
                    height: modbusIpPort.height
                    visible: false
                }
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Row{

                Label{
                    text: qsTr("IP Port")
                    width: parent.width/3-25
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: abbIpPort
                    text: ""
                    width: parent.width*2/3-25
                    validator: IntValidator {
                        bottom: 0
                        top: 65535
                    }
                    //RegularExpressionValidator {
                    //    regularExpression: /^[0-9]{1,5}$/ // 1 to 5 digits
                    //}
                }
                Image{
                    id: abbPortError
                    source: "../assets/icon_warning.svg"
                    width: Image.PreseveAspectFit
                    height: modbusIpPort.height
                    visible: false
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
                    preferenceController.setAbbPreferences(abbIpAddr.text, abbIpPort.text);
                }
            }
        }

    }
    Connections {
        target: preferenceController

        function onSendPreferences(modbusip, modbusport, modbusmaxtries, abbip, abbport) {
            console.log("Preferences loaded");
            modbusIpAddr.text = modbusip;
            modbusIpPort.text = modbusport;
            modbusMaxReconnects.text = modbusmaxtries;
            abbIpAddr.text = abbip;
            abbIpPort.text = abbport;
        }

        function onModbusIPError(error){
            modbusIpError.visible = error;
            console.log("Modbus IP Error" + error);
        }

        function onModbusPortError(error){
            modbusPortError.visible = error;
            console.log("Modbus Port Error" + error);
        }

        function onModbusReconnectError(error){
            modbusReconnectError.visible = error;
            console.log("Modbus Reconnect Error" + error);
        }

        function onAbbIPError(error){
            abbIpError.visible = error;
            console.log("ABB IP Error" + error);
        }

        function onAbbPortError(error){
            abbPortError.visible = error;
            console.log("ABB Port Error" + error);
        }

    }
    onOpened: {
        preferenceController.loadPreferences();
    }
}
