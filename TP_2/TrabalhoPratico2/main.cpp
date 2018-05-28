#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    Backend *myBackend;
    myBackend = new Backend(0, &engine);

    return app.exec();
}