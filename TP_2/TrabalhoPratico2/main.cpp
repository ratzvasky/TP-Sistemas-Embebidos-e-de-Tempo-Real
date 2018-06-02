/*
 * Central meterológica - SETR ESI
 *
 * Rúben Guimarães nº11156
 * Kyrylo Yavorenko nº10355
 *
 *
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include "backend.h"


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QQuickView viewer;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    /*
    Backend *myBackend;
    myBackend = new Backend(0, &engine);

    */

    qmlRegisterType<Backend>("BackendLib", 1, 0, "Backend");



    /*
    Backend *myBackend;
    myBackend = new Backend(0, &engine);
*/

    return app.exec();

    /*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    Backend *myBackend;
    myBackend = new Backend(0, &engine);

    return app.exec();
    */
}
