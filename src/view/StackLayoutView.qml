import QtQuick 2.9
import QtQuick.Controls 2.15
import QtQuick.Controls.Material
import QtQuick.Layouts 1.15

Rectangle {
    Material.accent: Material.DarkBlue
    Material.primary: Material.Dark
    Material.foreground: Material.White
    Material.background: Material.Black
    width: parent.width
    height: 330
    TabBar {
        id: tabBar
        width: parent.width
        height: 50
        TabButton {
            text: "Commission"
            onClicked: stackLayout.currentIndex = 0
        }

        TabButton {
            text: "Eventlog"
            onClicked: stackLayout.currentIndex = 1
        }

        TabButton {
            text: "Inventory"
            onClicked: stackLayout.currentIndex = 2
        }
    }
    StackLayout {
        id: stackLayout
        anchors.top: tabBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: 0
        CommissionView {
            id: commissionView
            width: parent.width
            height: parent.height
        }
        EventView {
            id: eventView
            width: parent.width
            height: parent.height
        }
        InventoryView {
            id: inventoryView
            width: parent.width
            height: parent.height
        }

    }
}