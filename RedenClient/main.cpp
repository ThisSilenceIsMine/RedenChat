#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QBuffer>
#include <QByteArray>
#include <QTextStream>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include "include/client.h"
#include "include/contactslist.h"
#include "include/contactsmodel.h"
#include "include/messageslist.h"
#include "include/messagesmodel.h"
#include "include/userdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Client client;

    QFontDatabase fontDB;
    fontDB.addApplicationFont("qrc:/qml/fonts/OpenSansEmoji.ttf");
    app.setFont(QFont(QStringLiteral("OpenSansEmoji")));

    ContactsList contactsList;
    ContactsModel contactsModel;
    contactsModel.setList(&contactsList);
    client.setContactsModel(&contactsModel);

    MessagesList messagesList;
    MessagesModel messagesModel;
    messagesModel.setList(&messagesList);
    client.setMessagesModel(&messagesModel);

    UserData user;
    client.setUser(&user);  

    QFile conf("config.json");
    QByteArray configBytes;
    if(!conf.open(QIODevice::ReadOnly))
        client.start();
    else {
        qDebug() << "Getting settings from config.json...";
        QJsonParseError err;
        QJsonDocument config = QJsonDocument::fromJson(conf.readAll(), &err);
        qDebug() << err.errorString();
        QString hostAdress = config["host_adress"].toString();
        quint16 port = quint16(config["port"].toInt());
        client.start(hostAdress,port);
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    qmlRegisterType<ContactsModel>("reden.models.contactsModel",1,0,"ContactsModel");
    qmlRegisterType<MessagesModel>("reden.models.messagesModel",1,0,"MessagesModel");
    qmlRegisterType<Client>("reden.net.client",1,0,"Client");

    engine.rootContext()->setContextProperty("contactsModel", &contactsModel);
    engine.rootContext()->setContextProperty("messagesModel", &messagesModel);
    engine.rootContext()->setContextProperty("client", &client);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.addImportPath(":/qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
