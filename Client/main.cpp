#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickview.h>
#include "mytcpclient.h"
#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    MyTcpClient client;

    QQmlContext* context = engine.rootContext();


    context->setContextProperty("extern_client", &client);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

