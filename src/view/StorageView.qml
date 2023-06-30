import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Dialogs

Rectangle{
    id: storageRect
    color: "white"
    border.color: "#1F82B2"
    border.width: 2
    radius: 10
    width: 600
    height: 400
    StorageDialog{
        //Dialog to edit storage data
        id: editDialog
    }
    Rectangle{
        id: titleRect
        height: 25
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            leftMargin: 20
            rightMargin: 20
            topMargin: 5
        }
        Row{
            anchors.fill: parent
            Text {
                id: title
                height: 40
                text: qsTr("Storage")
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: 12
                font.bold: true
            }

            Image {
                id: setImage
                width: 40
                source: "../assets/gear.png"
                fillMode: Image.PreserveAspectFit
                height: title.height
                Layout.fillHeight: true
                Layout.fillWidth: true
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        editDialog.open()
                    }
                }
            }
        }
    }
    // TableView holds objects of StorageData.db which is read in InventoryModel
    TableView {
        model: storageModel
        anchors{
            top: titleRect.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        anchors.margins: 10
        columnSpacing: 10
        rowSpacing: 5
        clip: true
        delegate: ProductView{
            cupA: model.a_CupID
            prodA: model.a_ProductID
            nameA: model.a_Name
            cupB: model.b_CupID
            prodB: model.b_ProductID
            nameB: model.b_Name
            name: "L"+ (model.col+1 +model.row*6)
            implicitHeight: 150
            implicitWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
