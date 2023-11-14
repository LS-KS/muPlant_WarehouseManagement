import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.3


Rectangle {
    id: root
    width: 800
    height: infoLabel.height + entries.height +20
    color: "white"
    property string tagTextA: "0"
    property string tagTextB: "0"
    property string tagTextC: "0"
    property string readerIpAdress: ""
    property string readerPort: ""
    property string transponderType: ""
    property string iid:""
    property string dsfid: ""
    property string nameText: ""
    property string timestamp: ""

    onNameTextChanged: {
        name.text = nameText
    }
    property int idVal: 0
    property bool selected: false
    onSelectedChanged: {
        if (isSelected.checked !== selected){
            isSelected.checked = selected
        }
    }
    property var prefHeight : infoLabel.height + entries.height +20
    property bool minimized: false
    property bool locked: false
    border.color: "#1F82B2"
    border.width: 1
    radius: 5
    RowLayout{
        id: infoLabel
        anchors. top: parent.top
        anchors. left: parent.left
        anchors. right: parent.right
        anchors. leftMargin: 20
        anchors. rightMargin: 20
        Layout.fillWidth: true
        Image {
            id: arrow
            source: minimized === true ? "../assets/angle-small-down.png" : "../assets/angle-small-up.png"
            Layout.preferredHeight : 15
            fillMode: Image.PreserveAspectFit
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    minimized = minimized ? false : true
                    root.height = minimized?  50 : prefHeight
                    entries.visible = entries.visible ? false: true
                }
            }
        }
        Text{
            id: name
            text: "Node Name "
            font.bold: true
            Component.onCompleted: {
                name.text = nameText
            }
        }
        Text{
            id: idValText
            text: "(" + idVal + ")"
        }
        CheckBox{
            id: isSelected
            text: "selected"
            checked: false
            onCheckedChanged: {
                if (isSelected.checked !== selected){
                    rfidController.selectNode(idVal, checked)
                }
            }
            Component.onCompleted: {
                isSelected.checked = selected
            }
        }
        Text{
            id: tagText
            text: "Taginfo: " + root.tagTextA + " . " + root.tagTextB + " . " + root.tagTextC
        }
        Text{
            id: readerText
            property bool reader: false
            text: "Reader: " + 0 
        }
        Text{
            id: endpointText
            property bool reader: false
            text: "Endpoint: " + 0
        }
        Image{
            id: lock
            source: locked === true ? "../assets/Lock_closed.svg" : "../assets/Lock_open.svg"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    locked = locked ? false : true
                }
            }
            Layout.preferredHeight : 0.4*70
            Layout.preferredWidth : 0.4*50
        }        
    }
    ColumnLayout{
        id: entries
        anchors. top: infoLabel.bottom
        anchors. left: parent.left
        anchors. right: parent.right
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        clip: true
        Row {
            Label {
                text: "Name" 
                width: 120
                height:  30

            }
            TextField{
                id: nameTextField
                width: parent.width - 120
                height:  30
                text: ""
                onTextChanged: {
                    name.text = nameTextField.text
                }
                enabled: !locked
                Component.onCompleted: {
                    nameTextField.text = nameText
                }
            }
            Layout.fillWidth: true
            clip: true
        }
        Text{
            text: "Tag Reader"
            font.bold: true
            height: 50
        }
        Row {
            Label{
                text: "  Ip Adress: "
                width: 120
                height:  30
            }
            TextField{
                id: readerIpAdressField
                text: "0.0.0.0"
                width: parent.width - 120
                height:  30
                validator: RegularExpressionValidator {
                    regularExpression: /^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$/
                    // /^means string must start at the beginning
                    // {1,3} means 1 to 3 digits
                    // \. means a dot, [0-9] means a digit
                    // so /^(?:[0-9]{1,3}\.){3} means 1 to 3 digits followed by a dot, repeated 3 times
                    // followed by 1 to 3 digits
                }
                onEditingFinished: {
                    saveButton.enabled = true
                }
                enabled: !locked
                Component.onCompleted: {
                    readerIpAdressField.text = readerIpAdress
                }
            }
            Layout.fillWidth: true
            clip: true
        }
        Row {
            Label{
                text: "  Port: "
                width: 120
                height:  30
            }
            TextField{
                id: readerPortField
                text: "0"
                width: parent.width - 120
                height:  30
                enabled: !locked
                onEditingFinished: {
                    saveButton.enabled = true
                }
                Component.onCompleted: {
                    readerPortField.text = readerPort
                }
            }
            Layout.fillWidth: true
            clip: true

        }
        Text{
            text: "Tag"
            font.bold: true
            height: 50
        }
        Row {
            Label{
                id: transponderlabel
                text: "  Transponder: "
                width: 120
                height:  30
            }
            TextField{
                id: transponderField
                text: root.transponderType
                width: (parent.width/2 -120)
                height:  30
                readOnly: true
            }
            Label{
                id: timestamplabel
                text: "  Zeitstempel: "
                width: 120
                height:  30
            }
            TextField{
                id: timestampField
                text: root.timestamp
                width: (parent.width/2 -120)
                height:  30
                readOnly: true
            }
            Layout.fillWidth: true
            clip: true
        }
        Row {
            Label{
                text: "  IID: "
                width: 120
                height:  30
            }
            TextField{
                id: iidField
                text: root.iid
                width: parent.width - 120
                height:  30
                readOnly: true
            }
            Layout.fillWidth: true
            clip: true
        }
        Row{
            Label{
                text: "  DSF - ID: "
                width: 120
                height:  30

            }
            TextField{
                id: dsfidField
                text: root.dsfid
                width: parent.width - 120
                height:  30
                readOnly: true
            }
            Layout.fillWidth: true
            clip: true
        }
        Button{
            id: saveButton
            text: "Save Changes"
            enabled: false
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200
            onClicked:{
                rfidController.saveNodeChanges(
                    idVal,
                    nameTextField.text, 
                    readerIpAdressField.text, 
                    readerPortField.text,
                )
                saveButton.enabled = false
            }
        }
        Behavior on visible { PropertyAnimation{ duration: minimized? 10 : 1000; easing.type: Easing.InOutQuad}}
    }
    Behavior on height { PropertyAnimation{ duration: 1000; easing.type: Easing.OutCubic}}
}
