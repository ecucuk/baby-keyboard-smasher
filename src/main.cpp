#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

/*    QQmlApplicationEngine splashEngine{};
    QObject::connect(
        &splashEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
        );

    splashEngine.loadFromModule("baby-keyboard-smasher", "Splash");
*/


    QQmlApplicationEngine mainEngine;
    QObject::connect(
        &mainEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    mainEngine.loadFromModule("baby-keyboard-smasher", "Main");

    return app.exec();
}
