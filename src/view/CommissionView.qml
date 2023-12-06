import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material
Rectangle{
    id: baseRect
    width: 200
    height: 200
    color: "#B9D5F0"
    border.color: "#1F82B2"
    border.width: 2
    radius : 10
    anchors.margins: 5

    CommissionDialog{
        id: comdiag
    }

    RowLayout{
        id: commHeaders
        height: 30
        anchors.top: baseRect.top
        anchors.right: baseRect.right
        anchors.left: baseRect.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        Text{
            id: colId
            text: "ID"
            Layout.preferredWidth: baseRect.width*1/21-10
        }
        Text{
            id: colSource
            text: "From..."
            Layout.preferredWidth: baseRect.width*5/21
        }
        Text {
            id: colTarget
            text: qsTr("...To")
            Layout.preferredWidth: baseRect.width*5/21
        }
        Text {
            id: colObject
            text: qsTr("Object")
            Layout.preferredWidth: baseRect.width*2/21
        }
        Text{
            text: ""
            Layout.preferredWidth: baseRect.width*2/21
        }
        Text{
            text: ""
            Layout.preferredWidth: baseRect.width*2/21
        }
        Text{
            id: colState
            text: "State"
            Layout.preferredWidth: baseRect.width*4/21
        }
        Layout.fillWidth: true
    }

    TableView {
        id: view
        anchors.right: baseRect.right
        anchors.bottom: baseRect.bottom
        anchors.left: baseRect.left
        anchors.top: baseRect.top
        topMargin: commHeaders.height
        anchors.margins: 5
        width: parent.width
        model: commissionModel
        rowSpacing: 5
        columnSpacing: 0
        clip: true


        delegate: Rectangle{
            implicitWidth: delegateText.width*1.2
            implicitHeight: delegateText.height * 1.2
            id: delegateRect
            color: "white"
            Text{
                id: delegateText
                property string modelString: model.text
                property bool isPending: model.state === "pending"
                property bool inProgress: model.state ==="in progress"
                property bool isFinished: model.state === "done"
                property bool prepared: model.state ==="prepare"
                font.bold: inProgress
                font.pointSize: inProgress? 15 : 14
                color: delegateText.isPending ? "#1F82B2" : inProgress? "#C6055A" : isFinished? "grey": "black"
                text: inProgress? modelString + "..." : modelString
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
                padding: 5
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Layout.fillWidth: true
        }
        columnWidthProvider: function(column){
            if (column === 0 ){
                return baseRect.width*1/21 -5;
            }
            if (column === 1){
                return baseRect.width*5/21;
            }
            if (column === 2){
                return baseRect.width*5/21;
            }
            if (column === 3){
                return baseRect.width*2/21;
            }
            if (column === 4){
                return baseRect.width*2/21;
            }
            if (column === 5){
                return baseRect.width*2/21;
            }
            if (column === 6){
                return baseRect.width*4/21-5;
            }
            forceLayout();
        }
    }

    Image {
        id: editbutton
        x: -25
        width: 20
        height: 20
        anchors.right: parent.right
        anchors.top: parent.top
        source: "../assets/gear.png"
        anchors.topMargin: 4
        anchors.rightMargin: 4
        fillMode: Image.PreserveAspectFit
        MouseArea{
            id: editmouse_area
            anchors.fill: parent
            onClicked: {
                comdiag.open()
            }
        }
    }
}
