import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
Dialog {
    id: dialog_rect
    width: 300
    height: 465
    property int row: -1
    property int col: -1
    property int slotid_a: -1
    property int slotid_b: -1
    property bool pallet_detected: false

    ColumnLayout{
        RowLayout{
            Column{
                id: pallet
                leftPadding: 5
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Text{
                    id: palletText
                    text: "Pallet detected: " + dialog_rect.pallet_detected
                }
                Rectangle{
                    width: dialog_rect.width -15
                    height: 250
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: palletImage
                        property int counter: 0
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
        RowLayout{
            Column{
                leftPadding: 5
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: slotA
                Text{
                    id: slotAText
                    text: "Slot A: Detected ID: " + dialog_rect.slotid_a
                }
                Rectangle{
                    width: dialog_rect.width/2 -15
                    height: 125
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: slotAImage
                        property int counter: 0
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
            Column{
                leftPadding: 5
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: slotB
                Text{
                    id: slotBtext
                    text: "Slot B: Detected ID: "+ dialog_rect.slotid_b
                }
                Rectangle{
                    width: dialog_rect.width/2 -15
                    height: 125
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: slotBImage
                        property int counter: 0
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        cache: false

                    }
                }
            }
        }
        RowLayout{
            Button{
                id: loadButton
                text: "load data..."
                onClicked: dialog_rect.loadImages()
                Layout.preferredHeight: 40
                Layout.preferredWidth: dialog_rect.width/4
            }
            Button{
                id: okButton
                text: "Ok"
                onClicked: console.log("nothing here ... yet")
                Layout.preferredHeight: 40
                Layout.preferredWidth: dialog_rect.width/5
            }
            Button{
                id: cancelButton
                text: "Cancel"
                onClicked: dialog_rect.close()
                Layout.preferredHeight: 40
                Layout.preferredWidth: dialog_rect.width/5
            }
            Button{
                id: saveButton
                text: "Save changes"
                Layout.fillWidth: true
                enabled: false
                onClicked: console.log("nothing here.... yet")
                Layout.preferredHeight: 40
                Layout.preferredWidth: dialog_rect.width/5
                Layout.alignment: Qt.AlignRight
            }
        }
    }
    onAboutToShow: {
        loadImages()
    }
    Connections{
        target: stocktaker
        function onTransmit_data_to_plugin(row, col, pallet, cupa_id, cupb_id){
            //all parameters are int, except pallet which is bool
            if (row === dialog_rect.row && col === dialog_rect.col){
                dialog_rect.slotid_a = cupa_id
                dialog_rect.slotid_b = cupb_id
                dialog_rect.pallet_detected = pallet
            }

        }
    }

    function loadImages(){
        /*
        Simply to set the same sourrce string again won't update the images.
        Trick is to call the virtual load() function in C++ backend which is protected.
        There is no other known way to do this than to change the source string.
        Honestly, one single counter would have also worked.
        In earlier Qt Versions it was possible to doo that with bool properties which are toggled everytime the image shall get loaded.
        Since Qt6 this is not possible. Even if the cache is 0 (maybe 0 stands for infinity?!?)

        The counters are increased everytime this function is called. This is fine since the python backend splits the string by '_' and
        compares the last string with __contains__.
        */

        // Call stocktaking slot to emit id data.
        stocktaker.requestIDData(dialog_rect.row, dialog_rect.col)

        slotAImage.counter += 1
        let a_sourcestring = "image://stockimage/"+ dialog_rect.row + "_" + dialog_rect.col +"_A.png" + slotAImage.counter
        slotBImage.counter += 1
        let b_sourcestring = "image://stockimage/"+ dialog_rect.row + "_" + dialog_rect.col +"_B.png" + slotBImage.counter
        palletImage.counter += 1
        let pallet_string = "image://stockimage/" + dialog_rect.row + "_" + dialog_rect.col +"_Pallet.png" + slotBImage.counter
        slotAImage.source = a_sourcestring
        slotBImage.source = b_sourcestring
        palletImage.source = pallet_string
    }
}
