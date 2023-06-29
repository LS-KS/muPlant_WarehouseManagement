import QtQuick
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    width:  200
    height: 150
    color: "#E1F5FE"
    border.color: "#1F82B2"
    border.width: 2

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        Row {
            id: row
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Text {
                id: name
                text: qsTr("muPlant Spezial")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Row {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Text {
                id: itemId
                text: qsTr("Cup: 25")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
}
