import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3


// View implementation of Manual Commission Control which allows
// Plugin allows to manipulate commission stack

Window {
    id: mccWindow
    width: Screen.width/3
    height: 2*Screen.width/3
    visible: true

    ColumnLayout{
        id: basicLayout
        anchors.fill: parent
        anchors.margins: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        Row{
            id: header
            Text{
                id: headerText
                text: "Manual Commission Control"
                font.pixelSize: 20
                font.bold: true
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: mccModbusLabel
                text: "Modbus Connection"
                font.pixelSize: 15
                height: mccModbusStatusRect.height
                width: parent.width/2
            }
            Rectangle{
                id: mccModbusStatusRect
                color: mccModbusStatusText.connected? "green":"red"
                height: 30
                width: parent.width/2
                Text{
                    id: mccModbusStatusText
                    property var connected: false
                    text: connected? "Connected" : "Disconnected"
                    font.pixelSize: 15
                    anchors.centerIn: mccModbusStatusRect
                }
            }
            Layout.fillWidth: true
        }
        Rectangle{
            id: mccSeperator
            height: 3
            color: "black"
            Layout.fillWidth: true
        }
        Row{
            Text{
                id: mccCommissionHeader
                text: "Create Commission"
                font.pixelSize: 15
                font.bold: true
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: mccObjectLabel
                text: "transportable Object"
                font.pixelSize: 15
                height: mccCommissionObject.height
                width: parent.width/2
            }
            ComboBox{
                id: mccCommissionObject
                height: 30
                width: parent.width/2
                model: ['Cup', 'Pallet']
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: mccSourceLabel
                text: "Source"
                font.pixelSize: 15
                height: mccCommissionSource.height
                width: parent.width/2
            }
            ComboBox{
                id: mccCommissionSource
                height: 30
                width: parent.width/2
                model: ['Mobile Robot', 'Commission Table', 'Storage']
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: mccCommissionDetail
                text: "Detailed Source"
                font.pixelSize: 15
                height: mccCommissionDetailSource.height
                width: parent.width/2
            }
            ComboBox{
                id: mccCommissionDetailSource
                height: 30
                width: parent.width/2
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
        Row{
            Label{
                id: mccSourceSlotLabel
                text: "Slot"
                font.pixelSize: 15
                height: mccCommissionSourceSlot.height
                width: parent.width/2 
            }
            ComboBox{
                id: mccCommissionSourceSlot
                height: 30
                width: parent.width/2
                model: {
                    if ( mccCommissionObject.currentValue == 'Cup'){
                        if (mccCommissionSource.currentValue == 'Mobile Robot'){
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
        Row{
            Label{
                id: mccDestinationLabel
                text: "Destination"
                font.pixelSize: 15
                height: mccCommissionDestination.height
                width: parent.width/2 
            }
            ComboBox{
                id: mccCommissionDestination
                height: 30
                width: parent.width/2
                model: ['Mobile Robot', 'Commission Table', 'Storage']
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: mccCommissionDestDetail
                text: "Detailed Source"
                font.pixelSize: 15
                height: mccCommissionDetailSource.height
                width: parent.width/2
            }
            ComboBox{
                id: mccCommissionDetailDestination
                height: 30
                width: parent.width/2
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
        Row{
            Label{
                id: mccDestinationSlotLabel
                text: "Slot"
                font.pixelSize: 15
                height: mccCommissionSourceSlot.height
                width: parent.width/2 
            }
            ComboBox{
                id: mccCommissionDestinationSlot
                height: 30
                width: parent.width/2
                model: {
                    if ( mccCommissionObject.currentValue == 'Cup'){
                        if (mccCommissionSource.currentValue == 'Mobile Robot'){
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
        Row{
            Button{
                id: checkButton
                text: "Check Commission"
                font.pixelSize: 15
                height: 30
                width: parent.width/2
            }
            Button{
                id: submitButton
                text: "Submit Commission"
                font.pixelSize: 15
                height: 30
                width: parent.width/2
                enabled: false
            }
            Layout.fillWidth: true
        }
        Rectangle{
            id: mccSeperator2
            height: 3
            color: "black"
            Layout.fillWidth: true
        }
        Row{
            id: rfidHeader
            Text{
                id: rfidHeaderText
                text: "Manual RFID I/O"
                font.pixelSize: 20
                font.bold: true
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: rfidCupLabel
                text: "Cup-ID"
                font.pixelSize: 15
                height: rfidCup.height
                width: parent.width/2
            }
            TextField{
                id: rfidCup
                height: 30
                width: parent.width/2
            }
            Layout.fillWidth: true
        }
        Row{
            Label{
                id: rfidProductLabel
                text: "Product-ID"
                font.pixelSize: 15
                height: rfidProduct.height
                width: parent.width/2
            }
            TextField{
                id: rfidProduct
                height: 30
                width: parent.width/2
            }
            Layout.fillWidth: true
        }
        Row{
            Button{
                id: rfidReadButton
                text: "Read RFID"
                height: 30
                Layout.fillWidth: true
            }
            Button{
                id: rfidWriteButton
                text: "Write RFID"
                height: 30
                Layout.fillWidth: true
            }
            Layout.fillWidth: true
        }
    }
}
