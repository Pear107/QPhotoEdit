#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>

#include "app/app.h"
#include "paint/paint.h"
#include "paint/mini_paint.h"

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/icon/logo.ico"));
    qmlRegisterType<App>("Custom.App", 1, 0, "CApp");
    qmlRegisterType<Paint>("Custom.Paint", 1, 0, "CPaint");
    qmlRegisterType<MiniPaint>("Custom.MiniPaint", 1, 0, "CMiniPaint");
    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/view/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

