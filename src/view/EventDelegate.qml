// EventDelegate.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property string displayText
    property bool isTime: false
    property bool isSource: false
    property bool isEvent: false

    Text{
        anchors.fill: parent
        text: displayText
        font.pixelSize: isTime? 10 : 12
        font.bold: !!isSource
        color: {
            if (isSource){
                if (displayText === "CommissionController"){
                    return '#DD2C00'
                } else if (displayText === "AgentService"){
                    return "#FF6D00"
                } else if (displayText === "OpcuaService"){
                    return "#FFC400"
                } else {
                    return "#000000"
                }
            }
            return "#000000"
        }
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
    }
}
