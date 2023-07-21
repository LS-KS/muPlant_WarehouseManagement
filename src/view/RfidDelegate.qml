import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3


Rectangle {
    id: root
    width: 400
    height: 350
    color: "white"
    property string tagTextA: "0"
    property string tagTextB: "0"
    property string tagTextC: "0"
    property bool minimized: false
    border.color: "black"
    border.width: 1
    radius: 5
    RowLayout{
        id: infoLabel
        anchors. top: parent.top
        anchors. left: parent.left
        anchors. right: parent.right
        anchors. leftMargin: 20
        anchors. rightMargin: 20
        Layout.fillWidth: true
        Image {
            id: arrow
            source: minimized === true ? "../assets/angle-small-down.png" : "../assets/angle-small-up.png"
            height: 15
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    minimized = minimized ? false : true
                    root.height = minimized?  50 : 400
                    entries.visible = entries.visible ? false: true
                }
            }
        }
        Text{
            id: name
            text: "Node Name "
            font.bold: true
        }
        CheckBox{
            id: isSelected
            text: "selected"
        }
        Text{
            property int textA: 0
            property int textB: 0
            property int textC: 0
            text: "Taginfo: " + tagTextA + " . " + tagTextB + " . " + tagTextC
        }
        Text{
            id: readerText
            property bool reader: false
            text: "Reader: " + reader 
        }
        Text{
            id: endpointText
            property bool reader: false
            text: "Endpoint: " + reader 

        }
    }
    ColumnLayout{
        id: entries
        anchors. top: infoLabel.bottom
        anchors. left: parent.left
        anchors. right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        clip: true
        Row {
            Label {
                text: "Name" 
                width: 120
                height:  30

            }
            TextField{
                id: nameText
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Text{
            text: "Tag Reader"
            font.bold: true
            height: 50
        }
        Row {
            Label{
                text: "  Ip Adress: "
                width: 120
                height:  30
            }
            TextField{
                id: readerIpAdress
                text: ""
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Row {
            Label{
                text: "  Port: "
                width: 120
                height:  30
            }
            TextField{
                id: readerPort
                text: ""
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Text{
            text: "Tag Endpoint"
            font.bold: true
            height: 50
        }
        Row {
            Label{
                text: "  Ip Adress: "
                width: 120
                height:  30
            }
            TextField{
                id: endpointIpAdress
                text: ""
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Row {
            Label{
                text: "  Port: "
                width: 120
                height:  30
            }
            TextField{
                id: endpointPort
                text: ""
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Row{
            Label{
                text: "  Modbus Address: "
                width: 120
                height:  30

            }
            TextField{
                id: endpointModbusAddress
                text: ""
                width: parent.width - 120
                height:  30
            }
            Layout.fillWidth: true
            clip: true
        }
        Behavior on visible { PropertyAnimation{ duration: minimized? 10 : 1000; easing.type: Easing.InOutQuad}}
    }
    Behavior on height { PropertyAnimation{ duration: 1000; easing.type: Easing.OutCubic}}
}
