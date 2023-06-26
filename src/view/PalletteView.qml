import QtQuick
import QtQuick.Layouts 1.15

Rectangle {
    id: baseRect
    width: 220
    height: 300
    radius : 10
    border.color: "#000"
    ColumnLayout{
        anchors.fill: parent
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5

        Row{
            id: row
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            CupView {
                id: a_Cup
                width: baseRect.width -10
                height: baseRect.height *0.5-10
            }
        }
        Row{
            id: row1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            CupView {
                id: b_Cup
                width: baseRect.width -10
                height: baseRect.height *0.5 -10
            }
        }
    }
}
