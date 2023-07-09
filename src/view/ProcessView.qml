import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle{
    id: rectangle

    WorkbenchDialog{
        id: workbenchDialog
    }

    GripperDialog{
        id: gripperDialog
    }

    Image {
        id: robot_ref_img
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width/2
        source: "../assets/robot_ref_img.png"
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 20
        fillMode: Image.PreserveAspectFit
        Image {
            id: setGripper
            width: 30
            source: "../assets/gear.png"
            anchors{
                right: parent.right
                bottom: parent.top
                topMargin: parent.height/10
                rightMargin: parent.width/3
            }
            fillMode: Image.PreserveAspectFit
            opacity: 0
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: setGripper.opacity = 1;
                onExited: setGripper.opacity = 0;
                onClicked: gripperDialog.open();
            }
        }


        StackLayout {
            width: parent.width/4
            height: currentIndex == 0 ? 0.75*width : width*1.5
            id: gripperLayout
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: 10
            anchors.topMargin: 10
            currentIndex: 0
            CupView{
                id: gripperCup
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            ProductView{
                id: gripperPallet
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            Connections{
                target: inventoryController
                function onTransmitGripper(isPallet, isCup, cupAID, prodAID, prodAName, cupBID, prodBID, prodBName){
                    console.log("transmitGripper received: "+isPallet+" "+isCup+" "+cupAID+" "+prodAID+" "+prodAName+" "+cupBID+" "+prodBID+" "+prodBName);
                    if(isPallet){
                        gripperLayout.currentIndex = 1;
                        gripperPallet.cupA = cupAID;
                        gripperPallet.prodA = prodAID;
                        gripperPallet.nameA = prodAName;
                        gripperPallet.withPallet = true;
                        gripperPallet.cupB = cupBID;
                        gripperPallet.prodB = prodBID;
                        gripperPallet.nameB = prodBName;
                        console.log("Gripper: loaded a pallet");
                        gripperLayout.opacity = 1;
                    }
                    else if(isCup){
                        gripperLayout.currentIndex = 0;
                        gripperCup.cup = cupAID;
                        gripperCup.prod = prodAID;
                        gripperCup.name = prodAName;
                        console.log("Gripper: loaded a cup");
                        gripperLayout.opacity = 1;
                    }
                    else {
                        gripperLayout.currentIndex = 0;
                        gripperCup.cup = cupAID;
                        gripperCup.prod = prodAID;
                        gripperCup.name = prodAName;
                        console.log("Gripper: loaded an empty cup");
                        gripperLayout.opacity = 0;
                    }
                }
            }
        }
    }
    Image {
        id: kommissionTable
        width: parent.width/2 > 350? 350 : parent.width/2
        height: 0.33*width
        source: "../assets/KommissionTable.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        fillMode: Image.PreserveAspectFit
        ProductView{
            width: parent.width/2 -20
            id: k1
            name: "K1"
            height: 1.2*width
            anchors.right: k2.left
            anchors.bottom: parent.top
            anchors.rightMargin: 10
            anchors.bottomMargin: -20
            MouseArea{
                propagateComposedEvents: true
                anchors.fill: parent
                hoverEnabled: true
                onEntered: setWorkbench.opacity = 1;
                onExited: setWorkbench.opacity = 0;
            }
            Component.onCompleted: {
                //console.log("K1 completed");
                inventoryController.getWorkbenchSlot(name);
            }
            Connections{
                target: inventoryController
                function onTransmitWorkbenchPallet(slot, cupIDA, productIDA, productNameA, isPallet, cupIDB, productIDB, productNameB){
                    //console.log("transmitWorkbenchPallet received in K1");
                    if(slot === "K1"){
                        console.log("K1 transmit");
                        k1.cupA = cupIDA;
                        k1.prodA = productIDA;
                        k1.nameA = productNameA;
                        k1.cupB = cupIDB;
                        k1.prodB = productIDB;
                        k1.nameB = productNameB;
                        k1.withPallet = isPallet;
                    }
                }
            }
        }
        ProductView{
            width: parent.width/2 -20
            id: k2
            name: "K2"
            height: 1.2*width
            anchors.right: parent.right
            anchors.bottom: parent.top
            anchors.rightMargin: 10
            anchors.bottomMargin: -20
            MouseArea{
                propagateComposedEvents: true
                anchors.fill: parent
                hoverEnabled: true
                onEntered: setWorkbench.opacity = 1;
                onExited: setWorkbench.opacity = 0;
            }
            Component.onCompleted: {
                console.log("K2 completed");
                inventoryController.getWorkbenchSlot(name);
            }
            Connections{
                target: inventoryController
                function onTransmitWorkbenchPallet(slot, cupIDA, productIDA, productNameA, isPallet, cupIDB, productIDB, productNameB){
                    //console.log("transmitWorkbenchPallet received in K2");
                    if(slot === "K2"){
                        console.log("K2 transmit");
                        k2.cupA = cupIDA;
                        k2.prodA = productIDA;
                        k2.nameA = productNameA;
                        k2.cupB = cupIDB;
                        k2.prodB = productIDB;
                        k2.nameB = productNameB;
                        k2.withPallet = isPallet;
                    }
                }
            }
        }

        Image {
        id: setWorkbench
        width: 30
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
        height: parent.height*0.8
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
    }



}
