#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent, QQmlApplicationEngine *ptr) : QObject(parent)
{
    this->engine = ptr;

    // Efetua a ligação das variaveis com os seus correnpondestes no frontend
    this->humidadeValue = engine->rootObjects().at(0)->findChild<QObject*>("humidadeValue"); 
    this->temperaturaAmbValue = engine->rootObjects().at(0)->findChild<QObject*>("temperaturaAmbValue");
    this->temperaturaAmbValue2 = engine->rootObjects().at(0)->findChild<QObject*>("temperaturaAmbValue2");
    this->temperatuaAguaValue = engine->rootObjects().at(0)->findChild<QObject*>("temperatuaAguaValue");
    this->pressaoAtmosfericaValue = engine->rootObjects().at(0)->findChild<QObject*>("pressaoAtmosfericaValue");
    this->altitudeValue = engine->rootObjects().at(0)->findChild<QObject*>("altitudeValue");
    this->velocidadeVentoValue = engine->rootObjects().at(0)->findChild<QObject*>("velocidadeVentoValue");
    this->sensorAguaValue = engine->rootObjects().at(0)->findChild<QObject*>("sensorAguaValue");
    this->posicaoSolValue = engine->rootObjects().at(0)->findChild<QObject*>("posicaoSolValue");
    this->meteoInfo = engine->rootObjects().at(0)->findChild<QObject*>("meteoInfo");

    this->sunImage = engine->rootObjects().at(0)->findChild<QObject*>("sunImage");
    this->rainImage = engine->rootObjects().at(0)->findChild<QObject*>("rainImage");
    this->solPosicaoEsteImage = engine->rootObjects().at(0)->findChild<QObject*>("solPosicaoEsteImage");
    this->solPosicaoSulImage = engine->rootObjects().at(0)->findChild<QObject*>("solPosicaoSulImage");
    this->solPosicaoOesteImage = engine->rootObjects().at(0)->findChild<QObject*>("solPosicaoOesteImage");

    this->grafico = engine->rootObjects().at(0)->findChild<QObject*>("grafico");



    // Configura a porta COM3
    this->mCOM = new QSerialPort();
    this->mCOM->setBaudRate(QSerialPort::Baud9600);
    this->mCOM->setStopBits(QSerialPort::OneStop);
    this->mCOM->setFlowControl(QSerialPort::NoFlowControl);
    this->mCOM->setParity(QSerialPort::NoParity);
    this->mCOM->setDataBits(QSerialPort::Data8);
    this->mCOM->setPortName("COM3");
    this->mCOM->open(QSerialPort::ReadWrite);

    connect(mCOM, SIGNAL(readyRead()), this, SLOT(dataReceived()));

}



// Método que le a informação da port COM3
void Backend::dataReceived()
{
    if(!mCOM->canReadLine())
        return;

    QByteArray dataArray;


    // Salvaguarda a informação numa string
    dataArray = mCOM->readLine();
    qDebug() << dataArray; // "31;22;20.94;20.40;34255;128;0;12;Sul;\r\n"


    QString dataString(dataArray); // converte QByteArray para QString


    updateData(dataString); // envia a data string para o método que faz update aos dados no frontend
}


// Método que trata a informação e atualiza o frontend
void Backend::updateData(QString dataString)
{
    QStringList listString;


    listString = dataString.split(";");

    listString.removeLast(); // Remove os caracteres de controlo


    // V se recebe a quantidade dados adequeada
    if(listString.count() != 9)
        return;


    // Verica se a humidade tem um valor valido
    if(QString(listString.at(0)).toInt() < 0 || QString(listString.at(0)).toInt() > 100 )
        this->humidadeValue->setProperty("text", "N/A");

    else
        this->humidadeValue->setProperty("text", QString(listString.at(0)) + "%");



    // Atualiza os valores
    this->temperaturaAmbValue->setProperty("text", QString(listString.at(1)) + "Cº");

    this->temperaturaAmbValue2->setProperty("text", QString(listString.at(3)) + "Cº");

    this->temperatuaAguaValue->setProperty("text", QString(listString.at(2)) + "Cº");

    this->pressaoAtmosfericaValue->setProperty("text", QString(listString.at(4)) + "Pa");

    this->altitudeValue->setProperty("text", QString(listString.at(5)) + "m");

    this->velocidadeVentoValue->setProperty("text", QString(listString.at(7)) + "RPM");



    // Modifica a imagem do fronend (sol ou chuva) dependedo do valor recevido do sensor de agua
    if (QString(listString.at(6)).toInt() == 1 )
    {
        this->sensorAguaValue->setProperty("text", "Chuva");
        this->sunImage->setProperty("visible", false);
        this->rainImage->setProperty("visible", true);
        this->meteoInfo->setProperty("text", "Não se esqueça do guarda-chuva!");
    }

    else
    {
        this->sensorAguaValue->setProperty("text", "Sol");
        this->sunImage->setProperty("visible", true);
        this->rainImage->setProperty("visible", false);
        this->meteoInfo->setProperty("text", "Não se esqueça do protector solar!");
    }


    this->posicaoSolValue->setProperty("text", QString(listString.at(8)));


    // define a source das imagens que indicam a posição do sol
    if (QString(listString.at(8)) == "Este")
    {
        this->solPosicaoEsteImage->setProperty("visible", true);
        this->solPosicaoSulImage->setProperty("visible", false);
        this->solPosicaoOesteImage->setProperty("visible", false);
    }

    if (QString(listString.at(8)) == "Sul")
    {
        this->solPosicaoEsteImage->setProperty("visible", false);
        this->solPosicaoSulImage->setProperty("visible", true);
        this->solPosicaoOesteImage->setProperty("visible", false);
    }

    if (QString(listString.at(8)) == "Oeste")
    {
        this->solPosicaoEsteImage->setProperty("visible", false);
        this->solPosicaoSulImage->setProperty("visible", false);
        this->solPosicaoOesteImage->setProperty("visible", true);
    }


    listaTemperaturas.append(1);
    listaTemperaturas.append(4);
    listaTemperaturas.append(6);

   grafico->removeSeries();
}
