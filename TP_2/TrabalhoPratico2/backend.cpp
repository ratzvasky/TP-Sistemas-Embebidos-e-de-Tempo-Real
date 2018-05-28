#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent, QQmlApplicationEngine *ptr) : QObject(parent)
{
    this->engine = ptr;

    this->humidadeValue = engine->rootObjects().at(0)->findChild<QObject*>("humidadeValue");


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

}
