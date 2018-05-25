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
    void updateUserInterface();
    void dataReceived();

private:
    QQmlApplicationEngine *engine;
    QSerialPort *mCOM;

    QObject *humidadeValue;


};

#endif // BACKEND_H
