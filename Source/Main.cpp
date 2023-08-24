#include <MathParser/Parser/Token.hpp>
#include "Calculator.hpp"

#include <QtCore>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include <chrono>
#include <thread>


auto main(int argc, char** argv) -> int {
    QGuiApplication app(argc, argv);

    qRegisterMetaType<Calculator::TokenType>("Calculator::TokenTyp");
    qmlRegisterType<Calculator>("Calculator", 1, 0, "Calculator");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.load(url);

    return QGuiApplication::exec();
}