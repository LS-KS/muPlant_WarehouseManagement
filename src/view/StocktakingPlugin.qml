import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

ApplicationWindow{
    id: stocktakerwindow
    width: 1300
    height: 1100
    title: "Stocktaking - Overview"
    ColumnLayout{
        id: maincolumn
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.margins: 10
        RowLayout{
            spacing: 20
            TableView{
                id: storagevisu
                Layout.minimumHeight: 600
                rowSpacing: 5
                columnSpacing: 5
                model: stockmodel
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 3*180
                delegate:Row{
                    id: stockrow
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 10
                    Rectangle{
                        id: stocklabel
                        width: 50
                        height: 180
                        color: "#00ffffff"
                        visible: model.column === 0
                        anchors.verticalCenter: parent.verticalCenter
                        ColumnLayout{
                            id: stocklablecol
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Rectangle{
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "#00ffffff"
                            }
                            Text {
                                text: qsTr("a")
                                horizontalAlignment: Text.AlignHCenter
                                font.bold: true
                                font.pointSize: 14
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }
                            Text {
                                text: qsTr("b")
                                horizontalAlignment: Text.AlignHCenter
                                font.bold: true
                                font.pointSize: 14
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }
                            Rectangle{
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "#00ffffff"
                            }
                        }
                    }
                    Column{
                        id: column
                        Text{
                            text: "L" + ((model.row * 6) + (model.column + 1))
                            font.bold: true
                            font.pointSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            Layout.fillWidth: true
                        }
                        StocktakingDelegate{
                            height: 180
                            width: 180
                            previous_pallet: model.previous_pallet
                            previous_cupA: model.previous_cupA
                            previous_cupB: model.previous_cupB
                            new_pallet : model.new_pallet
                            new_cupA: model.new_cupA
                            new_cupB: model.new_cupB
                            tested: model.tested
                            row: model.row
                            col: model.column
                        }
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
                Connections{
                    target: stockmodel
                    function onDataChanged(){
                        console.log("data changed")
                    }
                }
            }
            ListView{
                id: tablevisu
                Layout.minimumHeight: 160
                Layout.maximumHeight: 180
                Layout.preferredHeight: 10
                Layout.preferredWidth: 400
                Layout.fillWidth: false
                Layout.fillHeight: true
                model: tablemodel
                orientation: Qt.Horizontal
                delegate: Row{
                    id: row
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    spacing: 10
                    Rectangle{
                        id: tablelabel
                        width: 50
                        height: 180
                        color: "#00ffffff"
                        visible: model.row === 0
                        anchors.verticalCenter: parent.verticalCenter
                        ColumnLayout{
                            id: tablelablecol
                            anchors.verticalCenter: parent.verticalCenter
                            spacing: 50
                            anchors.horizontalCenter: parent.horizontalCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            Rectangle{
                                id: filler_rect
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "#00ffffff"
                            }
                            Text {
                                id: table_a
                                text: qsTr("a")
                                horizontalAlignment: Text.AlignHCenter
                                font.bold: true
                                font.pointSize: 14
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }
                            Text {
                                id: table_b
                                text: qsTr("b")
                                horizontalAlignment: Text.AlignHCenter
                                font.bold: true
                                font.pointSize: 14
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                            }
                            Rectangle{
                                id: filler_rect2
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                color: "#00ffffff"
                            }
                        }
                    }
                    Column{
                        id: tablecolumn
                        Text{
                            text: "K" + (model.row + 1)
                            font.bold: true
                            font.pointSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            Layout.fillWidth: true
                        }
                        StocktakingDelegate{
                            height: 180
                            width: 180
                            previous_pallet: model.previous_pallet
                            previous_cupA: model.previous_cupA
                            previous_cupB: model.previous_cupB
                            new_pallet : model.new_pallet
                            new_cupA: model.new_cupA
                            new_cupB: model.new_cupB
                            tested: model.tested
                        }
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                }
            }
        }
        RowLayout{
            id: buttonRow
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: 5
            Button{
                id: overviewcamButton
                text: "Overview Camera"
                onClicked: {
                    text: "running..."
                    enabled: false
                    stocktaker.callOverviewCam()
                    text: "Overview Camera"
                    enabled: true
                }
                Layout.fillWidth: true
            }
            Button{
                id: grippercamButton
                text: "Gripper Camera"
                onClicked: {
                    console.log("called gripper camera")
                    stocktaker.evaluate_gripper()
                }
                Layout.fillWidth: true
            }
            Button{
                id: inventoryButton
                text: "Perform Inventory"
                onClicked: {
                    console.log("called stocktaking - not implemented yet")
                }
                Layout.fillWidth: true
            }
            Button{
                id: acceptButton
                text: "Accept and Overwrite Inventory"
                enabled: false
                onClicked:{
                    console.log("called accept - not implemented yet")
                }
                Layout.fillWidth: true
                Connections{
                    target: stocktaker
                    function onAllow_accept_stock(ret){
                        acceptButton.enabled = ret
                    }
                }
            }
            Button{
                id: autoButton
                text: "Automated Stocktaking"
                onClicked:{
                    console.log("called auto stocktaking - not implemented yet")
                }
                Layout.fillWidth: true
            }
        }
    }
}
