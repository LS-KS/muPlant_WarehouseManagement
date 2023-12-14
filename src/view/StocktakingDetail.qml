import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs
Dialog {
    id: main_rect
    width: 300
    height: 465
    property int row: -1
    property int col: -1
    property int slotid_a: -1
    property int slotid_b: -1
    property int pallet_id: -1


    ColumnLayout{
        RowLayout{
            Column{
                id: pallet
                leftPadding: 5
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Text{
                    id: palletText
                    text: "Pallet: Detected ID: " + main_rect.pallet_id
                }
                Rectangle{
                    width: main_rect.width -15
                    height: 250
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: palletImage
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
                    text: "Slot A: Detected ID: " + main_rect.slotid_a
                }
                Rectangle{
                    width: main_rect.width/2 -15
                    height: 125
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: slotAImage
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
                    text: "Slot B: Detected ID: "+ main_rect.slotid_b
                }
                Rectangle{
                    width: main_rect.width/2 -15
                    height: 125
                    radius: 5
                    border.width: 2
                    border.color: 'black'
                    Image{
                        id: slotBImage
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
        RowLayout{
            Button{
                id: loadButton
                text: "load data..."
                onClicked: loadImages()
                Layout.preferredHeight: 40
                Layout.preferredWidth: main_rect.width/4
            }
            Button{
                id: okButton
                text: "Ok"
                onClicked: console.log("nothing here ... yet")
                Layout.preferredHeight: 40
                Layout.preferredWidth: main_rect.width/5
            }
            Button{
                id: cancelButton
                text: "Cancel"
                onClicked: main_rect.close()
                Layout.preferredHeight: 40
                Layout.preferredWidth: main_rect.width/5
            }
            Button{
                id: saveButton
                text: "Save changes"
                Layout.fillWidth: true
                enabled: false
                onClicked: console.log("nothing here.... yet")
                Layout.preferredHeight: 40
                Layout.preferredWidth: main_rect.width/5
                Layout.alignment: Qt.AlignRight
            }
        }
    }
    onAboutToShow: {
        loadImages()
    }
    function loadImages(){
        //console.log("try to load Images for "+ main_rect.row+ ", "+main_rect.col)
        let a_sourcestring = "image://stockimage/"+ main_rect.row + "_" + main_rect.col +"_A.png"
        let b_sourcestring = "image://stockimage/"+ main_rect.row + "_" + main_rect.col +"_B.png"
        let pallet_string = "image://stockimage/" + main_rect.row + "_" + main_rect.col +"_Pallet.png"
        //console.log("string for slot A: "+ a_sourcestring )
        //console.log(b_sourcestring)
        slotAImage.source = a_sourcestring
        slotBImage.source = b_sourcestring
        palletImage.source = pallet_string
    }
}
