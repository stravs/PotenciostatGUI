#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "potenciostat.h"

//jean
//working na 1,5V
//refernece na 2V
//kaj dobis nazaj



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);


    Potenciostat pot;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QByteArray ba{"r:DONE\r\n-1000,0\r\n"};

    engine.rootContext()->setContextProperty("pot", &pot);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
