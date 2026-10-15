#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "core/installerbackend.h"

int main(int argc, char *argv[]) {
    // Optimasi untuk RAM 512MB Raspberry Pi
    qputenv("QML_DISABLE_DISK_CACHE", "1");
    // qputenv("QT_QPA_PLATFORM", "eglfs"); // Buka komentar ini saat di-deploy ke RPi

    QGuiApplication app(argc, argv);

    InstallerBackend installerBackend;
    QQmlApplicationEngine engine;

    // Ekspos kelas Backend C++ ke QML
    engine.rootContext()->setContextProperty("installerBackend", &installerBackend);

    const QUrl url(u"qrc:/AppUI/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}