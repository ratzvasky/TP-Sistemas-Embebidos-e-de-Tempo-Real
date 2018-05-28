import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 1080
    height: 720
    color: "#ffffff"
    title: qsTr("Central Meteorológica - SETR ESI")


    // Label's dos dados

    Text {
        id: titulo
        x: 0
        y: 57
        width: 1080
        height: 31
        text: qsTr("Central Meteorológica")
        wrapMode: Text.NoWrap
        elide: Text.ElideNone
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        style: Text.Normal
        font.pixelSize: 25
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


    // Value's que vão ser atualizados com dados do arduino

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
        id: temperaturaAmbValue
        text: qsTr("N/A")
        objectName: "temperaturaAmbValue"
        anchors.top: humidadeValue.bottom
        anchors.topMargin: 30
        anchors.left: temperaturaAmbLabel.right
        anchors.leftMargin: 71
        font.pixelSize: 12
    }

    Text {
        id: temperaturaAmbValue2
        width: 20
        height: 14
        text: qsTr("N/A")
        objectName: "temperaturaAmbValue2"
        anchors.top: temperaturaAmbValue.bottom
        anchors.topMargin: 30
        anchors.left: temperaturaAmb2Label.right
        anchors.leftMargin: 59
        font.pixelSize: 12
    }

    Text {
        id: temperatuaAguaValue
        text: qsTr("N/A")
        objectName: "temperatuaAguaValue"
        anchors.top: temperaturaAmbValue2.bottom
        anchors.topMargin: 30
        anchors.left: temperaturaAguaLabel.right
        anchors.leftMargin: 94
        font.pixelSize: 12
    }

    Text {
        id: pressaoAtmosfericaValue
        text: qsTr("N/A")
        objectName: "pressaoAtmosfericaValue"
        anchors.top: temperatuaAguaValue.bottom
        anchors.topMargin: 30
        anchors.left: pressaoAtmosfericaLabel.right
        anchors.leftMargin: 85
        font.pixelSize: 12
    }

    Text {
        id: altitudeValue
        text: qsTr("N/A")
        objectName: "altitudeValue"
        anchors.left: altitudeLabel.right
        anchors.leftMargin: 149
        anchors.top: temperatuaAguaValue.bottom
        anchors.topMargin: 75
        font.pixelSize: 12
    }

    Text {
        id: velocidadeVentoValue
        text: qsTr("N/A")
        objectName: "velocidadeVentoValue"
        anchors.top: altitudeValue.bottom
        anchors.topMargin: 30
        anchors.left: velocidadeVentoLabel.right
        anchors.leftMargin: 99
        font.pixelSize: 12
    }

    Text {
        id: sensorAguaValue
        text: qsTr("N/A")
        objectName: "sensorAguaValue"
        anchors.top: velocidadeVentoValue.bottom
        anchors.topMargin: 30
        anchors.left: sensorAguaLabel.right
        anchors.leftMargin: 99
        font.pixelSize: 12
    }

    Text {
        id: posicaoSolValue
        text: qsTr("N/A")
        objectName: "posicaoSolValue"
        anchors.top: sensorAguaValue.bottom
        anchors.topMargin: 30
        anchors.left: posicaoSolLabel.right
        anchors.leftMargin: 113
        font.pixelSize: 12
    }
}