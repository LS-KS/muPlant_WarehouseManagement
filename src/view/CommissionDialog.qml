import QtQuick 2.15
import QtQuick.Dialogs
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3


Dialog {
    id: window

    ColumnLayout {
        x: 0
        y: 0
        width: 456
        height: 194
        RowLayout {
            Label {
                id: label1
                text: qsTr("ID:")
                horizontalAlignment: Text.AlignRight
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 100
            }

            ComboBox {
                id: idBox
                Layout.leftMargin: 10
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 234
                model: commissionModel
                textRole:  "text"
                editable: true
            }


            Button {
                id: loadButton
                text: qsTr("Load")
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 111

                Connections {
                    target: loadButton
                    onClicked: {
                        commissionController.loadCommission(idBox.currentText)
                    }
                }
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Label {
                id: label2
                text: qsTr("Item")
                horizontalAlignment: Text.AlignRight
                font.pointSize: 12
                Layout.preferredWidth: 100
            }


            TextInput {
                id: itemText
                height: 40
                text: qsTr("Text Input")
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                Layout.leftMargin: 10
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 20
                Layout.preferredWidth: 80
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Label {
                id: label
                text: qsTr("Source")
                horizontalAlignment: Text.AlignRight
                font.pointSize: 12
                Layout.preferredWidth: 100
            }


            TextInput {
                id: sourceText
                height: 40
                text: qsTr("Text Input")
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                Layout.leftMargin: 10
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 20
                Layout.preferredWidth: 80
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Label {
                id: label3
                text: qsTr("Target")
                horizontalAlignment: Text.AlignRight
                font.pointSize: 12
                Layout.preferredWidth: 100
            }


            TextInput {
                height: 40
                id: targetText
                text: qsTr("Text Input")
                font.pixelSize: 12
                verticalAlignment: Text.AlignVCenter
                Layout.leftMargin: 10
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 20
                Layout.preferredWidth: 80
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Label {
                id: label4
                text: qsTr("State")
                horizontalAlignment: Text.AlignRight
                font.pointSize: 12
                Layout.preferredWidth: 100
            }
            ComboBox {
                id: stateBox
                height: 40
                Layout.leftMargin: 10
                Layout.fillWidth: true
                Layout.fillHeight: false
                model: ListModel{
                    id: model
                    ListElement{ index: "OPEN"; text: "open"}
                    ListElement{ index: "PENDING"; text: "pending"}
                    ListElement{ index: "PROGRESS"; text: "in progress"}
                    ListElement{ index: "DONE"; text: "done"}
                }
                textRole: "text"
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: false
            Button {
                id: okButton
                height: 40
                text: qsTr("ok")
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 70

                Connections {
                    target: okButton
                    onClicked: {
                        commissionController.overwriteCommission(
                                    idBox.currentText,
                                    itemText.text,
                                    sourceText.text,
                                    targetText.text,
                                    stateBox.currentIndex
                                )
                    }
                }
            }

            Button {
                id: rejectButton
                height: 40
                text: qsTr("Abbrechen")
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 70

                Connections {
                    target: rejectButton
                    function onClicked() {
                        Dialog.close()
                    }
                }
            }

            Button {
                id: clearDoneButton
                height: 40
                text: qsTr("Clear All Done")
                down: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredHeight: 40
                Layout.preferredWidth: 70
                Connections {
                    target: clearDoneButton
                    onClicked: commissionController.clearDone()
                }
            }
        }


    }
    Connections{
        target: commissionController
        function onTransmitCommission(id, item, source, target, state){
            itemText.text = item
            sourceText.text = source
            targetText.text = target
            stateBox.currentIndex = state
        }
    }
}
