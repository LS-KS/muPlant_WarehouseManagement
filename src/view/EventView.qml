import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
import Qt.labs.qmlmodels
/*
  EventView.qml
  This Qml file implements a basic eventlogger textarea.
  It uses the EventLogController.
  */
Rectangle{
    id: eventWindow
    width: 640
    height: 400

    Rectangle {
        id: pane
        radius: 10
        border.color: "#1F82B2"
        border.width: 2
        anchors.fill: parent
        property string dateTimeFormat: "yyyy-MM-dd hh:mm:ss"

        Text {
            id: eventLogTitle
            text: qsTr("Event Log:")
            horizontalAlignment: Text.AlignHCenter
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 30
            verticalAlignment: Text.AlignVCenter
        }

        ScrollView {
            id: eventScrollView
            width: parent.width
            anchors.top: eventLogTitle.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10

            TableView {
                id: eventLogView
                width: parent.width
                height: parent.height
                model: eventModel
                clip: true
                columnWidthProvider: function (column) {
                    if (column === 0) return 100
                    if (column === 1) return 150
                    if (column === 2) return eventLogView.width - 250
                }
                rowHeightProvider: function (row) {
                    if (isRowLoaded(row)) {
                        var item = loadedRow(row);
                        var contentHeight = 0;
                        for (var i = 0; i < item.children.length; i++) {
                            if (item.children[i].contentHeight > contentHeight) {
                                contentHeight = item.children[i].contentHeight;
                            }
                        }
                        return contentHeight + 10;
                    } else {
                        return -1;
                    }
                }
                delegate: DelegateChooser{
                    role: "column"
                    DelegateChoice {
                        roleValue: 0
                        EventDelegate {
                            displayText: model.text
                            isTime: true
                        }
                    }

                    DelegateChoice {
                        roleValue: 1
                        EventDelegate {
                            displayText: model.text
                            isSource: true
                        }
                    }

                    DelegateChoice {
                        roleValue: 2
                        EventDelegate {
                            displayText: model.text
                            isEvent: true
                        }
                    }
                }
            }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Button {
        id:clearButton
        width: 100
        height: 30
        text: "clear"
        anchors {
            top: parent.top
            right: parent.right
            margins: 10
        }
        onClicked: {
            eventLogTextArea.text = ""
        }

    }
}

