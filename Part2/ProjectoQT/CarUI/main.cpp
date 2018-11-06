#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QSerialPort>

#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Backend mProcessing(0, &engine);

    return app.exec();
}
