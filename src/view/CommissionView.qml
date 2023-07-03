import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3

Rectangle{
    id: rect
    width: 200
    height: 200
    color: "red"

    ListView{
        id: list
        anchors.fill: parent
        model: commissionModel
        delegate: Rectangle{
            width: 100
            height: 50
            color: "blue"
            Text{
                anchors.centerIn: parent
                text: index
                //nothing here yet...
            }
        }
    }
}