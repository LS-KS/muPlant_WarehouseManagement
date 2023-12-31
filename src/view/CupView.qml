import QtQuick
import QtQuick.Layouts 1.15

Rectangle{
    id: productSlot
    implicitHeight: parent.height/2-10
    implicitWidth: parent.width
    color: selected ? "#81B8D4": "white"
    border.color: "#1F82B2"
    border.width: 2
    Layout.fillWidth: true
    Layout.fillHeight: true
    activeFocusOnTab: true
    radius: 5
    property bool selected: false
    property int cup: 0
    property string name: "Kein Becher"
    property int prod: 0
    Image{
        id: cupImage
        anchors{
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        anchors.margins: 5
        source: "../assets/cup.svg"
        fillMode: Image.PreserveAspectFit
    }
    ColumnLayout{
       anchors.fill: parent
       Text{
           text:"Cup ID: "+cup
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
       }
       Text{
           text:name
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           Layout.fillHeight: true
           Layout.fillWidth: true
       }
    }
    MouseArea {
        id: mouseAreaA
        anchors.fill: parent
        propagateComposedEvents: true
        onClicked: {
            if (!productSlot.selected){
               inventoryController.selectRow(prod)
            }
        }
    }
}
