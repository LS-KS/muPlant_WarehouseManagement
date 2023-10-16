import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3


// View implementation of Manual Commission Control which allows
// Plugin allows to manipulate commission stack

Window {
    id: mccWindow
    visible: true
    property bool connected: false
    width: 450
    height: 800
    ScrollView{
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        anchors.fill: parent
        anchors.margins: 20
        ColumnLayout{
            id: basicLayout
            Layout.fillWidth: true
            RowLayout{
                id: header
                Text{
                    id: headerText
                    text: "Manual Commission Control"
                    font.pixelSize: 20
                    font.bold: true
                }
                Layout.fillWidth: true
            }
            RowLayout{
                width: 405
                Layout.fillHeight: false
                Label{
                    id: mccModbusLabel
                    text: "OPC UA Connection"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccModbusStatusRect.height
                    Layout.preferredWidth: 200
                }
                Rectangle{
                    id: mccModbusStatusRect
                    color: connected? "green": "#C6055A"
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: mccModbusStatusText.width + 20
                    Text{
                        id: mccModbusStatusText
                        text: connected? "Connected" : "Disconnected"
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
                Layout.fillWidth: true
                
            }
            Rectangle{
                id: mccSeperator
                height: 3
                color: "#1F82B2"
                Layout.fillWidth: true
            }
            RowLayout{
                Text{
                    id: mccCommissionHeader
                    text: "Create Commission"
                    font.pixelSize: 15
                    font.bold: true

                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccObjectLabel
                    text: "transportable Object"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionObject.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionObject
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: ['Cup', 'Pallet']
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccSourceLabel
                    text: "Source"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionSource.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionSource
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: ['Mobile Robot', 'Commission Table', 'Storage']
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccCommissionDetail
                    text: "Detailed Source"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionDetailSource.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionDetailSource
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: {
                        if (mccCommissionSource.currentText === "Mobile Robot"){
                            return ['-']
                        } else if (mccCommissionSource.currentText === "Commission Table"){
                            return ['K1', 'K2']
                        } else if (mccCommissionSource.currentText === "Storage"){
                            return ['L1', 'L2', 'L3', 'L4', 'L5', 'L6', 'L7', 'L8',
                                    'L9', 'L10', 'L11', 'L12', 'L13', 'L14', 'L15',
                                    'L16', 'L17', 'L18']
                        }
                    }
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccSourceSlotLabel
                    text: "Slot"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionSourceSlot.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionSourceSlot
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: {
                        if ( mccCommissionObject.currentValue === 'Cup'){
                            if (mccCommissionSource.currentValue === 'Mobile Robot'){
                                return ['-']
                            }else{
                                return ['a', 'b']
                            }
                        }else{
                            return ['NA']
                        }
                    }
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccDestinationLabel
                    text: "Destination"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionDestination.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionDestination
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: ['Mobile Robot', 'Commission Table', 'Storage']
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccCommissionDestDetail
                    text: "Detailed Source"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionDetailSource.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionDetailDestination
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: {
                        if (mccCommissionDestination.currentText === "Mobile Robot"){
                            return ['-']
                        } else if (mccCommissionDestination.currentText === "Commission Table"){
                            return ['K1', 'K2']
                        } else if (mccCommissionDestination.currentText === "Storage"){
                            return ['L1', 'L2', 'L3', 'L4', 'L5', 'L6', 'L7', 'L8',
                                    'L9', 'L10', 'L11', 'L12', 'L13', 'L14', 'L15',
                                    'L16', 'L17', 'L18']
                        }
                    }
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: mccDestinationSlotLabel
                    text: "Slot"
                    font.pixelSize: 15
                    Layout.preferredHeight: mccCommissionSourceSlot.height
                    Layout.preferredWidth: 200
                }
                ComboBox{
                    id: mccCommissionDestinationSlot
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                    model: {
                        if ( mccCommissionObject.currentValue === 'Cup'){
                            if (mccCommissionSource.currentValue === 'Mobile Robot'){
                                return ['-']
                            }else{
                                return ['a', 'b']
                            }
                        }else{
                            return ['NA']
                        }
                    }
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Button{
                    id: checkButton
                    text: "Check Commission"
                    font.pixelSize: 15
                    Layout.preferredHeight : 50
                    Layout.fillWidth: true
                }
                Button{
                    id: submitButton
                    text: "Submit Commission"
                    font.pixelSize: 15
                    Layout.preferredHeight : 50
                    Layout.fillWidth: true
                    enabled: false
                }
                Layout.fillWidth: true
            }
            Rectangle{
                id: mccSeperator2
                height: 3
                color: "#1F82B2"
                Layout.fillWidth: true
            }
            RowLayout{
                id: rfidHeader
                Text{
                    id: rfidHeaderText
                    text: "Manual RFID I/O"
                    font.pixelSize: 20
                    font.bold: true
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: rfidCupLabel
                    text: "Cup-ID"
                    font.pixelSize: 15
                    Layout.preferredHeight: rfidCup.height
                    Layout.preferredWidth: 200
                }
                TextField{
                    id: rfidCup
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Label{
                    id: rfidProductLabel
                    text: "Product-ID"
                    font.pixelSize: 15
                    Layout.preferredHeight: rfidProduct.height
                    Layout.preferredWidth: 200
                }
                TextField{
                    id: rfidProduct
                    Layout.preferredHeight : 50
                    Layout.preferredWidth: 200
                }
                Layout.fillWidth: true
            }
            RowLayout{
                Button{
                    id: rfidReadButton
                    text: "Read RFID"
                    Layout.preferredHeight: 50
                    Layout.fillWidth: true
                }
                Button{
                    id: rfidWriteButton
                    text: "Write RFID"
                    Layout.preferredHeight: 50
                    Layout.fillWidth: true
                }
                Layout.fillWidth: true
            }
        }
    }
    Connections{
        target: opcuaService
        function onOnline(isrunning){
            console.log("received opc ua status signal" + isrunning);
            connected = isrunning;
            console.log("connected is set to"+ connected)
        }
    }
    Component.onCompleted:{
        opcuaService.check_online_status();
    }
}
