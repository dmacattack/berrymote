#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QDebug>
#include "berrymotemain.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    QObject *pRootObj = engine.rootObjects().first();

    if (pRootObj == NULL)
    {
        qCritical() << "root object is null";
    }
    else
    {
        BerrymoteMain *pMain = new BerrymoteMain(pRootObj);
        pMain->init();
    }

    return app.exec();
}
