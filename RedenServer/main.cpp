#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "server.h"
#include "dbfacade.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("RedenDB");
    db.setUserName("root");
    db.setPassword("");
    Server server;
    bool ok = db.open();
    if(!ok) {
        qInfo() << "Can't connect to database";
    } else {
        qInfo() << "Database connected!";

        DBFacade databaseWrapper;
        databaseWrapper.setDb(&db);

        server.setDatabase(&databaseWrapper);
        QFile conf("config.json");
        QByteArray configBytes;
        if(!conf.open(QIODevice::ReadOnly))
            server.start();
        else {
            qDebug() << "Getting settings from config.json...";
            QJsonParseError err;
            QJsonDocument config = QJsonDocument::fromJson(conf.readAll(), &err);
            qDebug() << err.errorString();
            QString hostAdress = config["host_adress"].toString();
            quint16 port = quint16(config["port"].toInt());
            server.start(hostAdress,port);
        }
    }

    return a.exec();
}
