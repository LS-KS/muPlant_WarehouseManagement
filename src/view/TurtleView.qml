import QtQuick

Rectangle {
    id: rectangle
    width: 400
    height: 400
    color: "transparent"

    TurtleDialog {
        id: turtleDialog
    }

    Image {
        id: turtleBase
        height: rectangle.height*0.4
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: "../assets/TurtleBase.svg"
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.rightMargin: 5
        fillMode: Image.PreserveAspectFit
    }

    CupView {
        id: cupVisu
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: rectangle.height*0.3
        height: 0.55*width
        width: turtleBase.height
        opacity: cup == 0 ? 0 : 1
        MouseArea {
            id: cupMouse
            propagateComposedEvents: true
            anchors.fill: parent
            hoverEnabled: true
            onEntered: setTurtle.opacity = 1;
            onExited: setTurtle.opacity = 0;
            onClicked: turtleDialog.open();
        }
        Connections {
            target: inventoryController
            function onTransmitMobileRobot(cup, product, name) {
                console.log("transmitMobileRobot received; Cup: " + cup + " Product: " + product + " Name: " + name);
                cupVisu.cup = cup;
                cupVisu.prod = product;
                cupVisu.name = name;
            }
        }
    }

    Image {
        id: setTurtle
        width: 30
        source: "../assets/gear.png"
        anchors.right: cupVisu.left
        anchors.top: cupVisu.top
        anchors.rightMargin: 5
        fillMode: Image.PreserveAspectFit
        opacity: 0
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: setTurtle.opacity = 1;
            onExited: setTurtle.opacity = 0;
            onClicked: turtleDialog.open();
        }
    }

    Image {
        property bool turtlePresent: false
        id: sensorSymbolleft
        anchors.right: cupVisu.left
        anchors.top: turtleBase.top
        height: parent.height/6
        source: turtlePresent? "../assets/SensorSymbolBlue.svg" :  "../assets/SensorSymbol.svg"
        anchors.leftMargin: 0
        anchors.topMargin: -parent.height/10
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
        anchors.left: cupVisu.right
        anchors.top: turtleBase.top
        source: turtlePresent? "../assets/SensorSymbolBlue.svg" :  "../assets/SensorSymbol.svg"
        height: parent.height/6
        anchors.rightMargin: 0
        anchors.topMargin: -parent.height/10
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
        property bool selected
        width: cupVisu.width/2
        anchors.bottom: cupVisu.top
        anchors.bottomMargin: 20
        source: selected? "../assets/RfidIconBlue.svg": "../assets/RfidIcon.svg"
        anchors.horizontalCenter: turtleVisu.horizontalCenter
        anchors.topMargin: 100
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: rfidMouse
            anchors.fill: parent
            hoverEnabled: true
            onEntered: rfidicon.selected = true
            onExited: rfidicon.selected = false
        }
    }
}
