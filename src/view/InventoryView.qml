import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

Rectangle{
    id: rect
    width: 400
    height: 200
    color: "white"
    border.color: "#1F82B2"
    border.width: 2
    radius: 10

    ListView{
        id: list
        anchors.fill: parent
        anchors.margins: 10
        model: productSummaryModel
        clip: true
        Layout.fillHeight: true
        Layout.fillWidth: true
        delegate: Rectangle{
            id: rect1
            width: ListView.view.width
            height: 50
            property bool selected: model.selected
            color: selected ? "#81B8D4": "white"

            RowLayout{
                id: row
                anchors.fill: parent
                Text {
                    id: id
                    text: model.id
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 50
                }
                Text {
                    id: name
                    text: model.name
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 400
                }
                Text {
                    id: quantity
                    text: model.quantity
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 100
                }
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(!rect1.selected) {
                        inventoryController.selectRow(model.id)
                        rect1.selected= true
                    }
                }
            }
            Connections {
                target: inventoryController
                function onProductSelected(message) {
                    //console.log("onSelectRow - message: " + message + " id: " + model.id)
                    if (model.id !== message) {
                        rect1.selected = false
                        //console.log("delegate set false:" + model.id)
                    }
                    if(parseInt(model.id) === parseInt(message)) {
                        rect1.selected = true
                        //console.log("delegate set true:" + model.id)

                    }
                }
            }
        }
    }
}
