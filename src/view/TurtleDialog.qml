import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
/*
  This QML File shows a Dialog which enables the user to manually override the workbench data
  */
Dialog {
    id: turteDialog
    title: "Override mobile Robot"
    width: 350
    // ColumnLayout helps to organize Items in vertical order.
    ColumnLayout{
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true

        // This row has a textlabel and textfield which enables the user to override Cup ID
        Row{
            Text {
                id: cupText
                width: parent.width/2
                height: setCup.height
                text: qsTr("Set Cup ID: ")
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            TextField{
                id: setCup
                // limit the cup ID to positive integer between 0 and 9999
                validator: IntValidator{
                    bottom: 0
                    top: 9999
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // This row enables the user to override product id in mobile robot
        Row{
            Text {
                id: setProd
                width: parent.width/2
                height: setProduct.height
                text: qsTr("Set Product ID:")
                Layout.fillHeight: true
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox{
                id:setProduct
                model: productListModel
                textRole: 'name'
                valueRole: 'id'
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // clearbutton enables the user to set values for cup and product which implicate that the storage is empty
        DialogButtonBox{
            Button {
                id: clearButton
                text: "Clear"
                onClicked: {
                    console.log("Clear in WorkbenchDialog clicked")
                    setProduct.currentIndex = 0
                    setCup.text = "0"
                }
            }

        }
    }

    // standardbuttons are buttons which perform standard tasks.
    standardButtons: Dialog.Ok | Dialog.Cancel
    // signal which is emitted when Dialog.OK is clicked. It calls changeStorage() function of InventoryController
    onAccepted: {
        console.log("Change sent to InventoryController from TurtleDialog")
        console.log("cup: " + setCup.text)
        console.log("product: " + setProduct.currentValue)
        inventoryController.changeMobileRobot(setCup.text, setProduct.currentValue)
        console.log("Ok clicked in TurtleDialog")
    }
    onRejected: console.log("Cancel in turtleDialog clicked")
}
