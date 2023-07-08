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
        height: 50
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            leftMargin: 20
            rightMargin: 20
            topMargin: 5
        }
        Row{
            id: row
            anchors.fill: parent
            Text {
                id: title
                height: titleRect.height
                text: qsTr("Storage Visualization")
                verticalAlignment: Text.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                font.pixelSize: 12
                font.bold: true
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true;
                    onEntered: setImage.opacity = 1;
                    onExited: setImage.opacity = 0;
                }
            }
            Image {
                id: setImage
                width: 30
                height: 30
                anchors.verticalCenter: title.verticalCenter
                source: "../assets/gear.png"
                anchors.verticalCenterOffset: 0
                fillMode: Image.PreserveAspectFit
                Layout.fillHeight: true
                Layout.fillWidth: true
                opacity: 0
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        editDialog.open()
                    }
                    hoverEnabled: true;
                    onEntered: setImage.opacity = 1;
                    onExited: setImage.opacity = 0;
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
        anchors.topMargin: 0
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
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
            withPallet: model.isPallet
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
