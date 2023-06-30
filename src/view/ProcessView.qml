import QtQuick 2.0


Rectangle{
    id: rectangle

    WorkbenchDialog{
        id: workbenchDialog
    }

    Image {
        id: robot_ref_img
        x: 143
        anchors.right: parent.right
        anchors.top: parent.top
        source: "../assets/robot_ref_img.png"
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 20
        fillMode: Image.PreserveAspectFit


        CupView {
            width: parent.width/4
            height: 0.75*width
            id: gripperCup
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 10
            anchors.topMargin: 10

        }
    }
    Image {
        id: kommissionTable
        y: 348
        width: 400
        height: 120
        source: "../assets/KommissionTable.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        fillMode: Image.PreserveAspectFit

        PalletteView{
            width: parent.width/2 -20
            id: k1
            height: 1.2*width
            anchors.left: parent.left
            anchors.bottom: parent.top
            anchors.leftMargin: 10
            anchors.bottomMargin: -20
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: setWorkbench.opacity = 1;
                onExited: setWorkbench.opacity = 0;
            }

        }
        PalletteView{
            width: parent.width/2 -20
            id: k2
            height: 1.2*width
            anchors.right: parent.right
            anchors.bottom: parent.top
            anchors.rightMargin: 10
            anchors.bottomMargin: -20
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: setWorkbench.opacity = 1;
                onExited: setWorkbench.opacity = 0;
            }
        }
        Image {
        id: setWorkbench
        source: "../assets/gear.png"
        anchors.right: k1.left
        anchors.top: k1.top
        anchors.rightMargin: 5
        fillMode: Image.PreserveAspectFit
        opacity: 0
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered: setWorkbench.opacity = 1;
            onExited: setWorkbench.opacity = 0;
            onClicked: workbenchDialog.open();
        }
    }
    }
    TurtleView{
        id: turtleVisu
        width: parent.width*0.4
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
    }



}
