import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 1080
    height: 720
    title: qsTr("Central Meteorológica - SETR ESI")

    Text {
        id: titulo
        x: 73
        y: 61
        width: 225
        height: 31
        text: qsTr("Valores dos sensores")
        font.bold: true
        style: Text.Normal
        font.pixelSize: 20
    }

    Text {
        id: humidadeLabel
        y: 121
        text: qsTr("Humidade:")
        anchors.left: humidadeValue.right
        anchors.leftMargin: -92
        font.pixelSize: 12
    }

    Text {
        id: humidadeValue
        objectName: "humidadeValue"
        text: qsTr("")
        anchors.left: parent.left
        anchors.leftMargin: 148
        anchors.top: parent.top
        anchors.topMargin: 121
        font.pixelSize: 12
    }
}
