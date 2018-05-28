import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 1080
    height: 720
    color: "#ffffff"
    title: qsTr("Central Meteorológica - SETR ESI")


    Text {
        id: titulo
        x: 56
        y: 57
        width: 225
        height: 31
        text: qsTr("Valores dos sensores")
        font.bold: true
        style: Text.Normal
        font.pixelSize: 20
    }

    Text {
        id: humidadeLabel
        x: 56
        text: qsTr("Humidade:")
        anchors.top: titulo.bottom
        anchors.topMargin: 33
        font.pixelSize: 12
    }

    Text {
        id: humidadeValue
        y: 121
        objectName: "humidadeValue"
        text: qsTr("N/A")
        anchors.left: humidadeLabel.right
        anchors.leftMargin: 137
        font.pixelSize: 12
    }

    Text {
        id: temperaturaAmbLabel
        x: 56
        y: 161
        text: qsTr("Temperatura ambiente:")
        anchors.top: humidadeLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: temperaturaAguaLabel
        x: 56
        y: 203
        text: qsTr("Temperatura água:")
        anchors.top: temperaturaAmb2Label.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: temperaturaAmb2Label
        x: 56
        y: 344
        text: qsTr("Temperatura ambiente 2:")
        anchors.top: temperaturaAmbLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: pressaoAtmosfericaLabel
        x: 56
        y: 288
        text: qsTr("Pressão atmosferica:")
        anchors.top: temperaturaAguaLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: altitudeLabel
        x: 56
        y: 303
        width: 45
        height: 15
        text: qsTr("Altitude:")
        anchors.top: pressaoAtmosfericaLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: posicaoSolLabel
        x: 56
        y: 306
        text: qsTr("Posicao do sol:")
        anchors.top: sensorAguaLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: sensorAguaLabel
        x: 56
        y: 295
        text: qsTr("Estado do tempo:")
        anchors.top: velocidadeVentoLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }

    Text {
        id: velocidadeVentoLabel
        x: 56
        y: 328
        text: qsTr("Velocidade vento:")
        anchors.top: altitudeLabel.bottom
        font.pixelSize: 12
        anchors.topMargin: 30
    }
}
