import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
Rectangle {
    id: main_rect
    implicitWidth: 150
    implicitHeight: 150
    property bool previous_pallet: true
    property int previous_cupA: 0
    property int previous_cupB: 0
    property bool new_pallet : false
    property int new_cupA: 0
    property int new_cupB: 0
    property bool tested: true
    property int row : -1
    property int col : -1
    border.width: 3
    radius: 5
    color: "#00ffffff"
    border.color: tested? "#00ff00": "#ff0000"

    StocktakingDetail{
        id: detaildiag
        row: main_rect.row
        col: main_rect.col
    }

    Rectangle{
        id: previous_stock
        property double horizontalMargin: 0.03*parent.width
        property double verticalMargin: 0.03*parent.height
        width: parent.width/2 - horizontalMargin
        height: parent.height/2
        color: "#B9D5F0"
        border.color: "#1F82B2"
        radius: 5
        border.width: 1
        anchors{
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        anchors.leftMargin: horizontalMargin
        anchors.rightMargin: horizontalMargin
        anchors.topMargin: verticalMargin
        anchors.bottomMargin: verticalMargin
        Text {
            text: qsTr("Stock")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: previous_stock.verticalMargin
        }
        Rectangle{
            id: previous_slot_a
            property double horizontalMargin: 0.08*parent.width
            property double verticalMargin: 0.03*parent.height
            width: parent.width-2*horizontalMargin
            height: parent.height/3
            anchors{
                top: parent.top
                left: parent.left
            }
            anchors.leftMargin: horizontalMargin
            anchors.rightMargin: horizontalMargin
            anchors.topMargin: verticalMargin*4
            anchors.bottomMargin: verticalMargin
            radius: 5
            border.width: 2
            Text {
                id: prev_slota_cuptext
                anchors.centerIn: parent
                text: qsTr("Cup-ID: " + main_rect.previous_cupA)
            }
            opacity: main_rect.previous_cupA == 0 ? 0.5 : 1
        }
        Rectangle{
            id: previous_slot_b
            property double horizontalMargin: 0.08*parent.width
            property double verticalMargin: 0.03*parent.height
            width: parent.width-2*horizontalMargin
            height: parent.height/3
            anchors{
                bottom: parent.bottom
                left: parent.left
                top: previous_slot_a.bottom
            }
            anchors.leftMargin: horizontalMargin
            anchors.rightMargin: horizontalMargin
            anchors.topMargin: verticalMargin
            anchors.bottomMargin: verticalMargin*6
            radius: 5
            border.width: 2
            Text {
                id: prev_slotb_cuptext
                anchors.centerIn: parent
                text: qsTr("Cup-ID: " + main_rect.previous_cupB)
            }
            opacity: main_rect.previous_cupB == 0 ? 0.5 : 1
        }
    }
    Rectangle{
        id: new_stock
        property double horizontalMargin: 0.03*parent.width
        property double verticalMargin: 0.03*parent.height
        width: parent.width/2 -horizontalMargin
        height: parent.height/2
        color: "#B9D5F0"
        border.color: "#1F82B2"
        radius: 5
        border.width: 1
        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
        opacity: main_rect.new_pallet? 1 : 0.1
        anchors.leftMargin: horizontalMargin/2
        anchors.rightMargin: horizontalMargin
        anchors.topMargin: verticalMargin
        anchors.bottomMargin: verticalMargin
        Image {
            id: slot_icon
            property bool valid: main_rect.previous_pallet === main_rect.new_pallet
            visible: main_rect.tested
            source: valid? "../assets/icon_tick_circle.png" : "../assets/icon_exclamation_red.png"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: new_stock.verticalMargin/2
            }
        }
        Rectangle{
            id: new_slot_a
            property double horizontalMargin: 0.08*parent.width
            property double verticalMargin: 0.03*parent.height
            width: parent.width-2*horizontalMargin
            height: parent.height/3
            anchors{
                top: parent.top
                left: parent.left
            }
            anchors.leftMargin: horizontalMargin
            anchors.rightMargin: horizontalMargin
            anchors.topMargin: verticalMargin*4
            anchors.bottomMargin: verticalMargin
            radius: 5
            border.width: 2
            Text {
                id: new_slota_cuptext
                anchors.centerIn: parent
                text: qsTr("Cup-ID: "+ main_rect.new_cupA)
            }
            Image {
                id: slot_a_icon
                property bool valid: main_rect.previous_cupA === main_rect.new_cupA
                visible: main_rect.tested
                source: valid? "../assets/icon_tick_circle.png" : "../assets/icon_exclamation_red.png"
                anchors{
                    right: parent.right
                    top: parent.top
                    topMargin: new_slot_a.verticalMargin/2
                    rightMargin: new_slot_a.horizontalMargin/2
                }
            }
            opacity: main_rect.new_cupA == 0 ? 0.5 : 1
        }
        Rectangle{
            id: new_slot_b
            property double horizontalMargin: 0.08*parent.width
            property double verticalMargin: 0.03*parent.height
            width: parent.width-2*horizontalMargin
            height: parent.height/3
            anchors{
                bottom: parent.bottom
                left: parent.left
                top: new_slot_a.bottom
            }
            anchors.leftMargin: horizontalMargin
            anchors.rightMargin: horizontalMargin
            anchors.topMargin: verticalMargin
            anchors.bottomMargin: verticalMargin*6
            radius: 5
            border.width: 2
            Text {
                id: new_slotb_cuptext
                anchors.centerIn: parent
                text: qsTr("Cup-ID: "+ main_rect.new_cupB)
            }
            Image {
                id: slot_b_icon
                property bool valid: main_rect.previous_cupB === main_rect.new_cupB
                visible: main_rect.tested
                source: valid? "../assets/icon_tick_circle.png" : "../assets/icon_exclamation_red.png"
                anchors{
                    right: parent.right
                    top: parent.top
                    topMargin: new_slot_a.verticalMargin/2
                    rightMargin: new_slot_a.horizontalMargin/2
                }
            }
            opacity: main_rect.new_cupB == 0 ? 0.5 : 1
        }
    }
   Button{
       id: showButton
       text: "Detail"
       anchors{
           horizontalCenter: parent.horizontalCenter
           bottom: parent.bottom
           bottomMargin: 10
       }
       height: 30
       width: 60
       onClicked: {
           console.log("row: "+ main_rect.row + ", col: " + main_rect.col)
           detaildiag.open()
       }
   }
}
