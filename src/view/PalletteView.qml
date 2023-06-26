import QtQuick
import QtQuick.Layouts 1.15

Rectangle {
    id: baseRect
    width: 220
    height: 420
    ColumnLayout{
        anchors.fill: parent
        Row{
            CupVisu{
                width: parent.width/4
                height: 0.75*width
                id: a_Cup
            }
        }
        Row{
            CupVisu{
                width: parent.width
                height: 0.75*width
                id: b_Cup
            }
        }
    }
}
