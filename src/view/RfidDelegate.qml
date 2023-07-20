import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3


Rectangle {
    id: root
    width: 400
    height: 400
    color: "white"
    property string tagTextA
    property string tagTextB
    property string tagTextC
    
    RowLayout{
        id: infoLabel
        anchors. top: parent.top
        anchors. left: parent.left
        width: parent.width
        anchors. topMargin: 10
        anchors. leftMargin: 10
        anchors. rightMargin: 10
        Layout.fillWidth: true
        
        TextField{
            id: name
            placeholderText: "... Enter Name ... "
            Layout.fillWidth: true
        }
        CheckBox{
            id: isSelected
            text: "selected"
            Layout.fillWidth: true
        }
        Text{
            property int textA: 0
            property int textB: 0
            property int textC: 0
            text: "Taginfo: " + tagTextA + " . " + tagTextB + " . " + tagTextC
            Layout.fillWidth: true
        }
        Text{
            id: readerText
            property bool reader: false
            text: "Reader: " + reader 
            Layout.fillWidth: true
        }
        Text{
            id: endpointText
            property bool reader: false
            text: "Endpoint: " + reader 
            Layout.fillWidth: true
        }
    }
    ColumnLayout{
        id: entries
        Row {
            Label {
                text: "Name" 
            }
            TextField{
                id: nameText

            }
        }
        Text{
            text: "Tag Reader"
        }
        Row {
            Label{
                text: "  Ip Adress: "
            }
            TextField{
                id: readerIpAdress
                text: ""
            }
        }
        Row {
            Label{
                text: "  Port: "
            }
            TextField{
                id: readerPort
                text: ""
            }
        }
        Text{
            text: "Tag Endpoint"
        }
        Row {
            Label{
                text: "  Ip Adress: "
            }
            TextField{
                id: endpointIpAdress
                text: ""
            }
        }
        Row {
            Label{
                text: "  Port: "
            }
            TextField{
                id: endpointPort
                text: ""
            }
        }
        Row{
            Label{
                text: "  Modbus Address: "
            }
            TextField{
                id: endpointModbusAddress
                text: ""
            }
        }
    }
}