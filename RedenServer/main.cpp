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

        server.start();
    }

    return a.exec();
}
