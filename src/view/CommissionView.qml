import QtQuick
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.Material

Rectangle{
    id: baseRect
    width: 200
    height: 200
    color: "white"
    border.color: "#1F82B2"
    border.width: 2
    radius : 10
    anchors.margins: 5

    TableView {
            id: view
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: parent.width
            model: commissionModel
            alternatingRows: true
            rowSpacing: 5
            columnSpacing: 10
            clip: true

            delegate: Text{
                property string modelString: model.text
                text: modelString
                Layout.fillWidth: true
                clip: true
                padding: 5
            }
    }
}
