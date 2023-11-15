import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

Window{
    id: stocktakerwindow
    width: 1200
    height: 800
    ColumnLayout{
        id: maincolumn
        anchors.fill: parent
        spacing: 0
        Layout.fillHeight: true
        Layout.fillWidth: true
        TableView{
            id: storageVisu
            Layout.fillWidth: true
            Layout.fillHeight: true
            delegate: Rectangle{
                width: 10
                height: 10
            }
        }
        ListView{
            id: tableVIsu
            Layout.fillWidth: true
            Layout.fillHeight: true
            delegate: Rectangle{
                width: 10
                height: 10
            }
        }
        RowLayout{
            id: buttonRow
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Button{
                id: overviewcamButton
                text: "Übersichtskamera"
                onClicked: {
                    console.log("Übersichtskamera aufgerufen")
                }
            }
            Button{
                id: grippercamButton
                text: "Greiferkamera"
                onClicked: {
                    console.log("Greiferkamera aufgerufen")
                }
            }
            Button{
                id: inventoryButton
                text: "Inventur durchführen"
                onClicked: {
                    console.log("Inventur angefordert")
                }
            }
            Button{
                id: acceptButton
                text: "Inventurdaten übernehmen"
                onClicked:{
                    console.log("Inventur übernehmen")
                }
            }
            Button{
                id: autoButton
                text: "Automatische Inventur"
                onClicked:{
                    console.log("Automatikbetrieb")
                }
            }
        }
    }
}
