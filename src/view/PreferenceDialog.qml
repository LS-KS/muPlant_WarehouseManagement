import QtQuick 2.9
import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs

Dialog {
    id: preferenceDialog
    Rectangle {
        id: mainRect
        anchors.fill: parent
        ColumnLayout{
            anchors{
                top: text1.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
            }
            Text{ // Title for Modbus Preferences
                id: text1
                text: qsTr("Modbus Preferences")
                color : "#1F82B2"
                font.pixelSize: 24
            }
            Row{ // Modbus IP Address
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
            }
            Row{ // Modbus IP Port
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
            }
            Row{ // Modbus Max Reconnects
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
            }
            Button{ // Save Button for Modbus
                id: modbusSaveButton
                text: qsTr("Save")
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                onClicked: {
                    console.log("Save button clicked")
                    console.log(modbusIpAddr.text)
                    console.log(modbusIpPort.text)
                    preferenceController.setModBusPreferences(modbusIpAddr.text, modbusIpPort.text, modbusMaxReconnects.text);
                }
            }
            Text{ // Title for ABB Preferences
                id: text2
                text: qsTr("ABB Robot Preferences")
                color : "#1F82B2"
                font.pixelSize: 24
            }
            Row{ // ABB IP Address
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
            }
            Row{ // ABB IP Port
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
            }
            Button{ // Save Button for ABB
                id: abbSaveButton
                text: qsTr("Save")
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                onClicked: {
                    console.log("Save button clicked")
                    console.log(abbIpAddr.text)
                    console.log(abbIpPort.text)
                    preferenceController.setAbbPreferences(abbIpAddr.text, abbIpPort.text);
                }
            }
            CheckBox{ // Run RFID Server plugin automatically with START
                id: runRfidBox
                text: qsTr("Run RFID Server automatically with START")
                onCheckedChanged: {
                    console.log("Run MCC checked changed")
                    preferenceController.setPlugInPreferences(runRfidBox.checked, runMccBox.checked);
                }
            }
            CheckBox{ // Run MCC Server plugin automatically with START
                id: runMccBox
                text: qsTr("Run Manual Commission Control automatically with START")
                onCheckedChanged: {
                    console.log("Run MCC checked changed")
                    preferenceController.setPlugInPreferences(runRfidBox.checked, runMccBox.checked);
                }
            }
            Text{ // Title for OPC UA Preferences
                id: text3
                text: qsTr("OPC UA Preferences")
                color : "#1F82B2"
                font.pixelSize: 24
            }
            Row{ // OPC UA Server Endpoint
                Label{
                    text: qsTr("OPC UA Endpoint")
                    width: parent.width/3-25
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: opcEndpoint
                    text: ""
                    width: parent.width*2/3 - 25
                }
                Layout.fillWidth: true
            }
            Row{ // OPC UA Server Namespace
                Label{
                    text: qsTr("OPC UA Namespace")
                    width: parent.width/3-25
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: opcNamespace
                    text: ""
                    width: parent.width*2/3 - 25
                }
                Layout.fillWidth: true
            }
            Row{ // OPC UA Client URL
                Label{
                    text: qsTr("OPC UA Client URL")
                    width: parent.width/3-25
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: opcCUrlField
                    text: ""
                    width: parent.width*2/3 - 25
                }
                Layout.fillWidth: true
            }
            Row{ // OPC UA Client Namespace
                Label{
                    text: qsTr("OPC UA Client Namespcace")
                    width: parent.width/3-25
                    height: abbIpPort.height
                    verticalAlignment: Text.AlignVCenter
                }
                TextField{
                    id: opcCNamespace
                    text: ""
                    width: parent.width*2/3 - 25
                }
                Layout.fillWidth: true
            }
            Button{ // Save Button for OPC UA
                id: opcSaveButton
                text: qsTr("Save")
                Layout.maximumHeight: 50
                Layout.fillWidth: true
                onClicked: {
                    console.log("Save button clicked")
                    console.log(opcEndpoint.text)
                    console.log(opcNamespace.text)
                    console.log(opcCUrl.text)
                    console.log(opcCNamespace.text)
                    preferenceController.setOPCPreferences(opcEndpoint.text, opcNamespace.text, opcCUrl.text, opcCNamespace.text );
                }
            }
        }
    }
    Connections { // Write data to QML fields above when preferencecontroller emits signal sendPreferences
        target: preferenceController

        function onSendPreferences(modbusip, modbusport, modbusmaxtries, abbip, abbport, rfid, mcc, opcEp, opcNs, opcCUrl, opcCNs) {
            console.log("Preferences loaded");
            modbusIpAddr.text = modbusip;
            modbusIpPort.text = modbusport;
            modbusMaxReconnects.text = modbusmaxtries;
            abbIpAddr.text = abbip;
            abbIpPort.text = abbport;
            runRfidBox.checked = rfid;
            runMccBox.checked = mcc;
            opcEndpoint.text = opcEp;
            opcNamespace.text = opcNs;
            opcCUrlField.text = opcCUrl;
            opcCNamespace.text = opcCNs;
        }

        function onModbusIPError(error){ // Show error icon if IP address is invalid
            modbusIpError.visible = error;
            console.log("Modbus IP Error" + error);
        }

        function onModbusPortError(error){ // Show error icon if IP port is invalid
            modbusPortError.visible = error;
            console.log("Modbus Port Error" + error);
        }

        function onModbusReconnectError(error){ // Show error icon if max reconnects is invalid
            modbusReconnectError.visible = error;
            console.log("Modbus Reconnect Error" + error);
        }

        function onAbbIPError(error){ // Show error icon if IP address is invalid
            abbIpError.visible = error;
            console.log("ABB IP Error" + error);
        }

        function onAbbPortError(error){ // Show error icon if IP port is invalid
            abbPortError.visible = error;
            console.log("ABB Port Error" + error);
        }

    }
    onOpened: { // Load preferences when dialog is opened
        preferenceController.loadPreferences();
    }
}
