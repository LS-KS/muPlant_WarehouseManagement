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
    title: "Override Gripper"
    width: 400
    height: stackLayout.currentIndex === 0 ? 600 : 400
    anchors.centerIn: parent
    property bool isPalletPresent: true
    property bool isCupPresent: true
    Behavior on height {
        NumberAnimation {
            duration: 100
        }
    }
    // ColumnLayout helps to organize Items in vertical order.
    ColumnLayout{
        id: editGripperLayout
        width: parent.width
        height: parent.height
        // This Row enables user to allocate the storage location
        Row {
            Text {
                id: choiceText
                width: parent.width/2
                height: 50
                text: qsTr("Item present: ")
                verticalAlignment: Text.AlignVCenter
            }
            ComboBox{
                id: choicePresent
                model: ["Pallet", "Cup"]
                width: parent.width/2
                height: 50

            }
            Layout.fillWidth: true
        }
        StackLayout{
            id: stackLayout
            currentIndex: choicePresent.currentIndex
            ColumnLayout{
                Text{
                   id: palletText
                   width: parent.width
                   height: 50
                   text: qsTr("Set Pallet Properties: ")
                   font.pixelSize: 20
                   font.bold: true
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
                   Layout.fillWidth: true
                }
                Row{
                    Text{
                        id: cupAText
                        width: parent.width
                        height: 50
                        text: qsTr("Slot A: ")
                        font.pixelSize: 20
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Layout.fillWidth: true
                }
                Row{
                    Label{
                        id: cupA
                        width: parent.width/2
                        height: 50
                        text: qsTr("Cup A: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField{
                        id: cupAEdit
                        width: parent.width/2
                        height: 50
                        text: qsTr("")
                        verticalAlignment: Text.AlignVCenter
                    }
                    Layout.fillWidth: true
                }
                Row{
                    Label{
                        id: prodA
                        width: parent.width/2
                        height: 50
                        text: qsTr("Produkt A: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    ComboBox{
                        id: prodAEdit
                        width: parent.width/2
                        height: 50
                        model: productListModel
                        textRole: 'name'
                        valueRole: 'id'
                    }
                    Layout.fillWidth: true
                }
                Row{
                    Text{
                        id: cupBText
                        width: parent.width
                        height: 50
                        text: qsTr("Slot B: ")
                        font.pixelSize: 20
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                    }
                    Layout.fillWidth: true
                }
                Row{
                    Label{
                        id: cupB
                        width: parent.width/2
                        height: 50
                        text: qsTr("Cup B: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField{
                        id: cupBEdit
                        width: parent.width/2
                        height: 50
                        text: qsTr("")
                        verticalAlignment: Text.AlignVCenter
                    }
                    Layout.fillWidth: true
                }
                Row{
                    Label{
                        id: prodB
                        width: parent.width/2
                        height: 50
                        text: qsTr("Produkt B: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    ComboBox{
                        id: prodBEdit
                        width: parent.width/2
                        height: 50
                        model: productListModel
                        textRole: 'name'
                        valueRole: 'id'
                    }
                    Layout.fillWidth: true
                }
                Layout.fillWidth: true
            }
            ColumnLayout{
               Text{
                   id: palletAText
                   width: parent.width
                   height: 50
                   text: qsTr("Set Cup Properties: ")
                   font.pixelSize: 20
                   font.bold: true
                   verticalAlignment: Text.AlignVCenter
                   horizontalAlignment: Text.AlignHCenter
               }
               Row{
                    Label{
                        id: cup
                        width: parent.width/2
                        height: 50
                        text: qsTr("Cup: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField{
                        id: cupEdit
                        width: parent.width/2
                        height: 50
                        text: qsTr("")
                        verticalAlignment: Text.AlignVCenter
                    }
                    Layout.fillWidth: true
               }
               Row{
                    Label{
                        id: prod
                        width: parent.width/2
                        height: 50
                        text: qsTr("Produkt: ")
                        verticalAlignment: Text.AlignVCenter
                    }
                    ComboBox{
                        id: prodEdit
                        width: parent.width/2
                        height: 50
                        model: productListModel
                        textRole: 'name'
                        valueRole: 'id'
                    }
                    Layout.fillWidth: true
               }
               Layout.fillWidth: true
            }
            Layout.fillWidth: true
        }

    }
    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: {
        console.log("Gripperdialog Accepted")
    }
    onRejected: {
        //console.log("Gripperdialog Rejected")
    }
    onOpened: {
        console.log("Gripperdialog Completed")
        inventoryController.loadGripper()
    }
    Connections {
        target: inventoryController
        function onTransmitGripper(isPallet, isCup, CupA, ProdA, ProdAName, CupB, ProdB, ProdBName){
            if(isPallet){
                choicePresent.currentIndex = 0
                cupAEdit.text = CupA
                prodAEdit.currentIndex = ProdA
                cupBEdit.text = CupB
                prodBEdit.currentIndex = ProdB
            }else{
                choicePresent.currentIndex = 1
                cupEdit.text = CupA
                prodEdit.currentIndex = ProdA
            }
        }
    }
}
