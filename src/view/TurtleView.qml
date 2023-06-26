import QtQuick

Rectangle {
    id: rectangle
    width: 400
    height: 400
    color: "transparent"

    Image {
        id: turtleBase
        y: 255
        height: rectangle.height*0.4
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "../assets/TurtleBase.svg"
        anchors.leftMargin: 0
        anchors.bottomMargin: 0
        anchors.rightMargin: 0
        fillMode: Image.PreserveAspectFit
    }

    CupView {
        id: cupVisu
        y: 125
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: rectangle.height*0.3
        height: 0.3*rectangle.height
        width: 0.3*rectangle.width
    }

    Image {
        property bool turtlePresent: false
        id: sensorSymbolleft
        y: 296
        anchors.left: parent.left
        source: turtlePresent? "../assets/SensorSymbolBlue.svg" :  "../assets/SensorSymbol.svg"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: leftSensorMouse
            anchors.fill: parent
            hoverEnabled: true

            onEntered: sensorSymbolleft.turtlePresent = true
            onExited: sensorSymbolleft.turtlePresent = false
        }
    }

    Image {
        property bool turtlePresent: false
        id: sensorSymbolright
        x: 329
        y: 296
        anchors.right: parent.right
        source: turtlePresent? "../assets/SensorSymbolBlue.svg" :  "../assets/SensorSymbol.svg"
        anchors.rightMargin: 0
        asynchronous: false
        mipmap: false
        smooth: true
        mirror: true
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: rightSensorMouse
            anchors.fill: parent
            hoverEnabled: true

            onEntered: sensorSymbolright.turtlePresent = true
            onExited: sensorSymbolright.turtlePresent = false
        }
    }
    Image {
        id: rfidicon
        width: 60
        anchors.bottom: cupVisu.top
        anchors.bottomMargin: 20
        source: "../assets/rfid-icon.svg"
        anchors.horizontalCenter: turtleVisu.horizontalCenter
        anchors.topMargin: 100
        fillMode: Image.PreserveAspectFit
    }
}
