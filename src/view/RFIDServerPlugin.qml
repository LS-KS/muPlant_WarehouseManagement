import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("RFID Server")
    Rectangle{
        id: header
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        Text{
            text: "RFID Server"
            font.pixelSize: 14
            font.bold: true
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }
        Button{
            text: "Add New"
            onClicked: {
                console.log("Add New - Not implemented yet")
            }
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Rectangle{
        id: contentRect
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height - header.height -50
        anchors.margins: 10
        ListView{
            id: listView
            anchors.fill: parent
            model: rfidModel
            delegate: RfidDelegate{
                width: contentRect.width
                idVal: model.idVal
                selected: model.selected
                tagTextA: model.tagId
                tagTextB: model.productID
                tagTextC: model.cupSize
                nameText: model.name
                readerIpAdress: model.ipAddr
                readerPort: model.ipPort
                endpointIpAdress: model.endPointipAddr
                endpointPort: model.endPointipPort
                endpointModbusAddress: model.endPointModbus
                locked: true
            }
            Connections{
                target: listView.model
                function onDataChanged(index, index){
                    listView.forceLayout()
                    console.log("Data Changed")
                }
            }
        }
    }
    RowLayout{
        id: leftFooter
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width *2/6
        height: 50
        Button{
            text: "Select All"
            Layout.preferredWidth: 150
            onClicked:{
                rfidController.selectAll()
            }
        }
        Button{
            text: "Select None"
            Layout.preferredWidth: 150
            onClicked:{
                rfidController.selectNone()
            }
        }
    }
    RowLayout{
        id: rightFooter
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        width: parent.width *3/6
        height: 50
        Button{
            text: "Remove Selected"
            Layout.preferredWidth: 150
            onClicked: {
                rfidController.removeSelected()
            }
        }
        Button{
            text: "Start Selected"
            Layout.preferredWidth: 150
            onClicked: {
                rfidController.startSelected()
            }
        }
        Button{
            text: "Stop Selected"
            Layout.preferredWidth: 150
            onClicked: {
                rfidController.stopSelected()
            }
        }
    }

}
