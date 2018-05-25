#include "backend.h"
#include <QDebug>

Backend::Backend(QObject *parent, QQmlApplicationEngine *ptr) : QObject(parent)
{
    this->engine = ptr;

    this->humidadeValue = engine->rootObjects().at(0)->findChild<QObject*>("humidadeValue");


    /*


    this->m_rect = engine->rootObjects().at(0)->findChild<QObject*>("rect2"); */

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

    QByteArray dataString;
    QStringList listString;

    // salvaguarda a informação numa string
    dataString = mCOM->readLine();
    qDebug() << dataString;

    QString str(dataString);

    listString = str.split(";");

    qDebug() << listString.at(0);

     this->humidadeValue->setProperty("text", QString(listString.at(0)));




}
