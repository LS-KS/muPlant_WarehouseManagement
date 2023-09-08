import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

/*
  Create Window object as parent. Mustn't be ApplicationWindow because QMLEngine ans QGuiApllication instance already exist
  */
Window {
    id: window
    title: "Warehouse Management - Camera Application"
    color: "white"
    width: 800
    height: 800
    visibility: "Maximized"
    visible: true

    // Draw a Rectangle with colored border and radius as basic screen element
    Rectangle {
        id: baseRect
        visible: true
        color: "white"
        anchors.fill: parent
        anchors.margins: 10
        border.color: "#546E7A"
        border.width: 2
        radius: 10

        // Draw a Rectangle as Container for Image
        Rectangle{
            id: imRim
            width: baseRect.width
            height: baseRect.height * 0.7
            anchors{
                top: baseRect.top
                left: baseRect.left
                right: baseRect.right
            }
            border.color: "#546E7A"
            border.width: 2
            radius: 10
            // Image shows VideoPlayer's captured and processed images
            Image {
                id: camImage
                height: parent.height
                width: height* 1.5
                anchors.centerIn: parent
                source: "image://camApp/img"
                property bool counter: false

            }
            // Connect VideoPlayer's imageChanged Signal with Image item in qml
            Connections{
                target: camApp
                // this function toggles the counter property to constantly alternate the id value to get another picture as before.
                // Sets the new incoming picture as Content of Image item camImage
                function onImageChanged(image){
                    console.log("new image emitted")
                    camImage.counter = !camImage.counter
                    camImage.source = "image://camApp/img?id="+camImage.counter
                }
            }

        }
        // Just a describing Text
        Text {
            text: "arUco Camera Application"
            font.pixelSize: 24
            font.bold: true
            anchors.left: baseRect.left
            anchors.right: baseRect.right
            anchors.top: baseRect.top
            anchors.topMargin: 20
            horizontalAlignment: Text.AlignHCenter
        }
        // This Rowlayout stores the buttons to controll the CameraApplication
        RowLayout{
            id: buttonBar
            anchors.left: imRim.left
            anchors.right: imRim.right
            anchors.top: imRim.bottom
            height: 100
            anchors.rightMargin: 100
            anchors.leftMargin: 100
            anchors.topMargin: 10

            Row{
                // Startbutton calls VideoPlayers start - function
                Button{
                    id: startButton
                    text: "Camera Start"
                    width: 200
                    height: 50
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    onClicked: {
                        camApp.start()
                    }
                }
                // This button calls VideoPlayers toggleDetection - function
                Button{
                    id: toggleButton
                    text: "Detection Start"
                    width: 200
                    height: 50
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    property bool toggle : false
                    onClicked: {
                        camApp.toggleDetection()
                        toggle = !toggle
                        if(toggle){
                            text = "Detection Stop"
                        } else {
                            text = "Detection Start"
                        }
                    }

                }
                // This Button stops the actual Video feed
                Button{
                    id: stopButton
                    text: "Camera Stop"
                    width: 200
                    height: 50
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    onClicked: {
                        camApp.stop()
                    }
                }
                Layout.alignment: Qt.AlignHCenter
            }
        }

    }
    // If someone closes the Window the VideoPlayer instance has to destroy VideoThread instance.
    onClosing: {
        camApp.stop()
    }
}

