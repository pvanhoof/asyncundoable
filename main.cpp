#include <QtQml>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <editor.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Editor>("be.codeminded.asyncundo", 1, 0, "Editor");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
