/*
 * Central meterológica - SETR ESI
 *
 * Rúben Guimarães nº11156
 * Kyrylo Yavorenko nº10355
 *
 *  BackEnd do projecto
 */

#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QtSerialPort>
#include <QTimer>


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr, QQmlApplicationEngine *ptr = nullptr);




signals:

public slots:
    void dataReceived();

    void updateData(QString dataString);

private:
    QQmlApplicationEngine *engine;
    QSerialPort *mCOM;

    QObject *humidadeValue;
    QObject *temperaturaAmbValue;
    QObject *temperaturaAmbValue2;
    QObject *temperatuaAguaValue;
    QObject *pressaoAtmosfericaValue;
    QObject *altitudeValue;
    QObject *velocidadeVentoValue;
    QObject *sensorAguaValue;
    QObject *posicaoSolValue;
    QObject *meteoInfo;

    QObject *sunImage;
    QObject *rainImage;
    QObject *solPosicaoEsteImage;
    QObject *solPosicaoSulImage;
    QObject *solPosicaoOesteImage;

};

#endif // BACKEND_H
