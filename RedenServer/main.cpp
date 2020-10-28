#include <QCoreApplication>
#include <QSqlDatabase>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("RedenDB");
    db.setUserName("root");
    db.setPassword("");

    bool ok = db.open();

    return a.exec();
}
