import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Controls.Material
import QtQuick.Layouts 1.3


Window {
    visible: true
    width: 300
    height: 480
    title: qsTr("Productlist")

    Material.theme: Material.Dark

    ListView {
        id: listView
        anchors.fill: parent
        model: productListModel

        delegate: Rectangle {
            width: parent.width
            height: 30
            color: "white"
            Text {
                text: model.id +" - "+ model.name
            }
        }
    }
}