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

    client.start();

//    QString fileUrl = QDir::currentPath() + "/Contacts.json";
//    QFile file(fileUrl);
//    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {

//        QJsonDocument js = QJsonDocument::fromJson(file.readAll());

//        file.close();
//        QJsonArray arr = js["data"].toVariant().toJsonArray();

//        client.loadContactsList(arr);

//    }

//    QString msgUrl = QDir::currentPath() + "/Messages.json";
//    QFile msgFile(msgUrl);
//    if(msgFile.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QJsonDocument js = QJsonDocument::fromJson(msgFile.readAll());

//        msgFile.close();
//        QJsonArray arr = js["data"].toVariant().toJsonArray();
//        client.loadMessageHistory(arr);
//    }
    QQmlApplicationEngine engine;

    //qmlRegisterUncreatableType<ContactsList>("reden.models.contactsList",1,0,"ContactsList",QStringLiteral("ContactsList cannot be created in QML"));
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
