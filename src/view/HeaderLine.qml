import QtQuick 2.15


Rectangle {
        id: headerLine
        width: parent.width
        height: 100
        color : "white"
        anchors.top : parent.top
        anchors.left : parent.left

        Image {
            id: uniKassel
            source: "../assets/logo_unikassel.jpg"
            antialiasing: true
            height: parent.height / 2 -10
            fillMode: Image.PreserveAspectFit
            anchors.left : parent.left
            anchors.top : parent.top
            anchors.margins: 5
        }

        Image {
            id: mrt
            source: "../assets/logo_mrt.png"
            antialiasing: true
            height: parent.height / 2 -10
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter : uniKassel.horizontalCenter
            anchors.top : uniKassel.bottom
            anchors.margins: 5
        }

        Text {
            id: titleText
            width: headerLine.width / 2
            height: headerLine.height
            color: "#607d8b"
            text: "μPlant Model Factory: Warehouse"
            anchors.left : uniKassel.right
            anchors.top : headerLine.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            minimumPointSize: 9
            minimumPixelSize: 6
            font.pointSize: 20
            textFormat: Text.AutoText
            fontSizeMode: Text.HorizontalFit
            font.kerning: true
            style: Text.Raised
            styleColor: "#607d8b"
        }

        Image {
            id: muPlant
            source: "../assets/logo_uPlant.png"
            antialiasing: true
            height: headerLine.height -10
            fillMode: Image.PreserveAspectFit
            anchors.right : headerLine.right
            anchors.top : headerLine.top
            anchors.margins: 5
        }

    }
