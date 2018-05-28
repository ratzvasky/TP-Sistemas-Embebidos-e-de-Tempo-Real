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



    // Setup Serial COM
    this->mCOM = new QSerialPort();
    this->mCOM->setBaudRate(QSerialPort::Baud9600);
    this->mCOM->setStopBits(QSerialPort::OneStop);
    this->mCOM->setFlowControl(QSerialPort::NoFlowControl);
    this->mCOM->setParity(QSerialPort::NoParity);
    this->mCOM->setDataBits(QSerialPort::Data8);
    this->mCOM->setPortName("COM3");
    this->mCOM->open(QSerialPort::ReadWrite);

    connect(mCOM, SIGNAL(readyRead()), this, SLOT(dataReceived()));

    //QTimer::singleShot(25, this, SLOT(updateUserInterface()));
}

void Backend::updateUserInterface()
{
    qDebug() << "in...";

    /*
    int rotation = m_rect->property("rotation").toInt();
    m_rect->setProperty("rotation", rotation+1);

    qDebug() << rotation;

    QTimer::singleShot(25, this, SLOT(updateUserInterface()));
    */
}


// Método que le a informação da port COM3
void Backend::dataReceived()
{
    if(!mCOM->canReadLine())
        return;

    QByteArray dataArray;


    // Salvaguarda a informação numa string
    dataArray = mCOM->readLine();
    qDebug() << dataArray;


    QString dataString(dataArray); // converte QByteArray para QString


    updateData(dataString);
}


// Método que trata a informação e atualiza o frontend
void Backend::updateData(QString dataString)
{
    QStringList listString;


    listString = dataString.split(";");

    listString.removeLast(); // Remove os caracteres de controlo


    if(listString.count() != 9) // verifica se recebe a quantidade dados adequeada
        return;

    qDebug() << listString.at(0);


    // Verica se a humidade tem um valor valido
    if(QString(listString.at(0)).toInt() < 0 || QString(listString.at(0)).toInt() > 100 )
        this->humidadeValue->setProperty("text", "N/A");

    else
        this->humidadeValue->setProperty("text", QString(listString.at(0)) + "%");


    this->temperaturaAmbValue->setProperty("text", QString(listString.at(1)) + "Cº");

    this->temperaturaAmbValue2->setProperty("text", QString(listString.at(2)) + "Cº");

    this->temperatuaAguaValue->setProperty("text", QString(listString.at(3)) + "Cº");

    this->pressaoAtmosfericaValue->setProperty("text", QString(listString.at(4)) + "h");

    this->altitudeValue->setProperty("text", QString(listString.at(5)) + "m");

    this->velocidadeVentoValue->setProperty("text", QString(listString.at(6)) + "RPM");


    if (QString(listString.at(7)).toInt() == 0 )
        this->sensorAguaValue->setProperty("text", "Chuva");
    else
        this->sensorAguaValue->setProperty("text", "Sol");


    this->posicaoSolValue->setProperty("text", QString(listString.at(8)));

}
