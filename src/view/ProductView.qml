import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15



Rectangle {
    id: productSlot
    width: 200
    height: 400
    radius: 10
    border.width: 2
    border.color: "#1F82B2"

    property string name: "ProductSlot"
    property string cupA: ""
    property string prodA: ""
    property string nameA: ""
    property string cupB: ""
    property string prodB: ""
    property string nameB: ""


    Text {
        id: title
        text: name
        width: parent.width
        height: 20
        verticalAlignment: Text.AlignVCenter
        minimumPixelSize: 6
        horizontalAlignment: Text.AlignHCenter
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            leftMargin: 10
            topMargin: 5
        }

        fontSizeMode: Text.HorizontalFit
        font.bold: true
    }

    Rectangle {
        id: greySpace
        height: parent.height
        width: parent.width
        anchors {
            top: title.bottom
            left: parent.left
            bottom: parent.bottom
            right: parent.right
            margins: 5
        }
        radius: 5
        color: "#81B8D4"
        border.width: 1
        border.color: "#1F82B2"
        ColumnLayout{
            anchors.fill: parent
            spacing: 2
            // Rectangle holding Product A
            Rectangle{
                id: productSlotA
                implicitHeight: parent.height/2-10
                implicitWidth: parent.width
                color: selected ? "#81B8D4": "white"
                border.color: "#1F82B2"
                border.width: 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                activeFocusOnTab: true
                radius: 5
                property bool selected: false
                ColumnLayout{
                   anchors.fill: parent
                   Text{
                       text:"Cup ID: "+cupA
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       Layout.fillHeight: true
                       Layout.fillWidth: true
                   }
                   Text{
                       text:nameA
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       Layout.fillHeight: true
                       Layout.fillWidth: true
                   }

                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (!productSlotA.selected){
                           inventoryController.selectRow(prodA)
                        }

                    }

                }
            }
            // Rectangle holds Product B
            Rectangle{
                id: productSlotB
                implicitHeight: parent.height/2-10
                implicitWidth: parent.width
                color: selected ? "#81B8D4": "white"
                border.color: "#1F82B2"
                border.width: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
                radius: 5
                property bool selected: false
                ColumnLayout{
                   anchors.fill: parent
                   Text{
                       text:"Cup ID: "+cupB
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       Layout.fillHeight: true
                       Layout.fillWidth: true
                   }

                   Text{
                       text:nameB
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                       Layout.fillHeight: true
                       Layout.fillWidth: true
                   }

                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (!productSlotB.selected){
                           inventoryController.selectRow(prodB)
                        }

                    }

                }
            }

        }
        //Connect to InventoryController.py's InventoryController and change color of selected Product.
        Connections{
            target: inventoryController
            function onProductSelected(message){
                if (prodA === message){
                    productSlotA.selected = true
                }else{
                    productSlotA.selected = false
                }
                if (prodB === message){
                    productSlotB.selected = true
                }else{
                    productSlotB.selected = false
                }
            }
        }
    }
}

