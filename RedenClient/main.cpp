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

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Client client;

    QFontDatabase fontDB;
    fontDB.addApplicationFont("qrc:/qml/fonts/OpenSansEmoji.ttf");
    app.setFont(QFont(QStringLiteral("OpenSansEmoji")));


    ContactsList list;
    ContactsModel contactsModel;
    contactsModel.setList(&list);

    client.setContactsModel(&contactsModel);
//    Contact item;
//    item.nickname = "some nickename";
//    item.imageUrl = "qrc:/images/Default.png";
//    for(int i = 0; i < 5; ++i)
//    {
//        contactsModel.append(item);
//    }

    QString fileUrl = QDir::currentPath() + "/Contacts.json";
    QFile file(fileUrl);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File opened!";
        QJsonDocument js = QJsonDocument::fromJson(file.readAll());
        qDebug() << "Document parsed!";
        file.close();
        QJsonArray arr = js["data"].toVariant().toJsonArray();
        qDebug() << "Invoking loadContactsList...";
        client.loadContactsList(arr);
        qDebug() << "File closed!";
    }

    QQmlApplicationEngine engine;

    //qmlRegisterUncreatableType<ContactsList>("reden.models.contactsList",1,0,"ContactsList",QStringLiteral("ContactsList cannot be created in QML"));
    qmlRegisterType<ContactsModel>("reden.models.contactsModel",1,0,"ContactsModel");

    engine.rootContext()->setContextProperty("contactsModel", &contactsModel);

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
