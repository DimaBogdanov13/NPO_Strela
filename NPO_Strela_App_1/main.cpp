#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "page_logic.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<Page_Logic>("Page_Logic", 1, 0, "Page_Logic");



    QQmlApplicationEngine engine;

    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
