import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3
/*
  This QML File shows a Dialog which enables the user to manually override the workbench data
  */
Dialog {
    id: workbenchDialog
    title: "Override Workbench"
    property bool isPalletPresent: true
    width: 350
    // ColumnLayout helps to organize Items in vertical order.
    ColumnLayout{
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true
        // This Row enables user to allocate the workbench location
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
            // Comobobox has List of all possible hardcoded workbench locations
            ComboBox{
                id: setLocation
                model: ['K1', 'K2']
                Layout.fillHeight: true
                Layout.fillWidth: true
                onCurrentValueChanged: {
                    if(setLocation.currentValue !==''){
                        inventoryController.loadWorkbench(setLocation.currentValue, setAB.currentValue)
                    }
                }
            }
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        Row {
            Text {
                id: palletText
                text: qsTr("Pallet present: ")
                width: parent.width/2
                height: palletPresent.height
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            ComboBox{
                id: palletPresent
                model: ["Yes", "No"]
                onCurrentValueChanged: {
                    if(palletPresent.currentText === "Yes"){
                        isPalletPresent = true
                    }
                    else{
                        isPalletPresent = false
                    }
                }
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        // This Row enables the user to select either he wants to override the cup in front or at the backside.
        Row{
            Text {
                id: slotText
                width: parent.width/2
                height: setAB.height
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
                    if (setLocation.currentText !== '') {
                        inventoryController.loadWorkbench(setLocation.currentValue, setAB.currentValue)
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
        // This row enables the user to override product id in workbench
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
        Text {
            id: warningText
            width: parent.width
            height: 200
            text: qsTr("WARNING: Pallet not present! This will erase current Cups in both slots!")
            verticalAlignment: Text.AlignVCenter
            opacity: isPalletPresent? 0 : 1
            wrapMode: "WordWrap"
            Layout.fillWidth: true
            Layout.fillHeight: true
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
        console.log("Change sent to InventoryController")
        console.log("location: "+ setLocation.currentText)
        console.log("slot: " +setAB.currentText)
        console.log("cup: " + setCup.text)
        console.log("product: " + setProduct.currentValue)
        inventoryController.changeWorkbench(setLocation.currentText, setAB.currentText, setCup.text, setProduct.currentValue, isPalletPresent)
        console.log("Ok clicked in WorkbenchDialog")
    }
    onRejected: console.log("Cancel in workbench dialog clicked")
    // Connect InventoryController's transmitData Signal to this qml file. If storage is set and InventoryController's loadWorkbench() function is called
}
