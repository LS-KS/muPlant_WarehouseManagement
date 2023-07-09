import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15
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

            TextArea {
                id: eventLogTextArea
                width: parent.width
                height: parent.height
                readOnly: true
                wrapMode: TextEdit.WordWrap

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
    Connections{
        target: eventLogController
        function onNewSignal(message){
            eventLogTextArea.text = message+ "\n"+ eventLogTextArea.text
        }
    }
}

