import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 1080
    height: 720
    title: qsTr("Central Meteorológica - SETR ESI")

    Text {
        id: titulo
        x: 73
        y: 61
        width: 181
        height: 31
        text: qsTr("Valores dos sensores")
        font.bold: true
        style: Text.Normal
        font.pixelSize: 20
    }
}
