import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

Rectangle{
    id: baseRect
    width: 200
    height: 200
    color: "white"
    border.color: "#1F82B2"
    border.width: 2
    radius : 10
    anchors.margins: 5
    ListView {
            id: view
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 5
            width: parent.width
            model: commissionModel
            delegate:
                RowLayout{
                    anchors.margins: 5
                    spacing: 5
                    height: 30
                    Text {
                        text: id
                        font.pixelSize: 18
                    }
                    Text {
                        text: source
                        font.pixelSize: 18
                    }
                    Text {
                        text: target
                        font.pixelSize: 18
                    }
                    Text {
                        text: object
                        font.pixelSize: 18
                    }
                    Text {
                        text: cup
                        font.pixelSize: 18
                    }
                    Text {
                        text: pallet
                        font.pixelSize: 18
                    }
                    Text {
                        text: state
                        font.pixelSize: 18
                    }
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
}
