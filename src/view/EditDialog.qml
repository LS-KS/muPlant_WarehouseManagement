import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
/*
  This QML File shows a Dialog which enables the user to manually override the storage data
  */
Dialog {
    id: editDialog
    title: "Override Storage"
    // ColumnLayout helps to organize Items in vertical order.
    ColumnLayout{
        Layout.fillHeight: true
        Layout.fillWidth: true
        // This Row enables user to allocate the storage location
        Row{
            Text {
                id: location
                text: qsTr("Location: ")
                width: parent.width/2
                height: setLocation.height
                Layout.fillHeight: true
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
            }
            // Comobobox has List of all possible hardcoded storage locations
            ComboBox{
                id: setLocation
                model: ['L1', 'L2', 'L3', 'L4', 'L5', 'L6', 'L7', 'L8', 'L9', 'L10', 'L11', 'L12', 'L13', 'L14', 'L15', 'L16', 'L17', 'L18']
                Layout.fillHeight: true
                Layout.fillWidth: true
                onCurrentValueChanged: {
                    if(setLocation.currentValue !==''){
                        inventoryController.loadStorage(setLocation.currentValue, setAB.currentValue)
                    }
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // This Row enables the user to select either he wants to override the cup in front or at the backside.
        Row{
            Text {
                id: slotText
                width: parent.width/2
                text: qsTr("Product a or b: ")
                Layout.fillHeight: true
                Layout.fillWidth: true
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox{
                // a = front, b = back
                id: setAB
                model: ["a","b"]
                Layout.fillHeight: true
                Layout.fillWidth: true
                // load actual storage values if storage location is changed and not empty
                onCurrentValueChanged: {
                    if(setLocation.currentValue !==''){
                        inventoryController.loadStorage(setLocation.currentValue, setAB.currentValue)
                    }
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // This row has a textlabel and textfield which enables the user to override Cup ID
        Row{
            Text {
                id: cupText
                width: parent.width/2
                text: qsTr("Set Cup ID: ")
                verticalAlignment: Text.AlignVCenter
            }
            TextField{
                id: setCup
                // limit the cup ID to positive integer between 0 and 9999
                validator: IntValidator{
                    bottom: 0
                    top: 9999
                }
            }
        }
        // This row enables the user to override product id in storage
        Row{
            Text {
                id: setProd
                width: parent.width/2
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
                Layout.fillHeight: true
                Layout.fillWidth: true

            }
        }
        // clearbutton enables the user to set values for cup and product which implicate that the storage is empty
        DialogButtonBox{
            Button {
                id: clearButton
                text: "Clear"
                onClicked: {
                    console.log("Clear Clicked")
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
        console.log("location: "+ setLocation.currentText)
        console.log("slot: " +setAB.currentText)
        console.log("cup: " + setCup.text)
        console.log("product: " + setProduct.currentValue)
        inventoryController.changeStorage(setLocation.currentText, setAB.currentText, setCup.text, setProduct.currentValue)
        console.log("Ok clicked")
    }
    onRejected: console.log("Cancel clicked")
    // Connect InventoryController's transmitData Signal to this qml file. If storage is set and InventoryController's loadStorage() function is called
    // data will be transmitted by this signal
    Connections{
        target: inventoryController
        function onTransmitData(slot, cup, product){
            setCup.text = cup
            setProduct.currentIndex = product
        }
    }
}
