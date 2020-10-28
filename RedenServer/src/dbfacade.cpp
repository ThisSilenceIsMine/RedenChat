#include "../include/dbfacade.h"
#include <QDebug>
#include <QSqlError>
DBFacade::DBFacade(QObject *parent) : QObject(parent)
{

}


bool DBFacade::registerUser(QString username, QString password, QString imageUrl)
{
    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO attachments (id_message, url)"
                  "VALUES (:null, :url);"
                  "SELECT LAST_INSERT_ID();");

    query.bindValue(":null", QVariant());
    query.bindValue(":url", imageUrl);

    if(!query.exec())
    {
        qWarning() << Q_FUNC_INFO << "Inserting image failed" << query.lastError().text();
        return false;
    }
    int id = 0;
    while(query.next())
    {
        id = query.value(0).toInt();
    }
    query.finish();

    query.prepare("INSERT INTO users (nickname, password, id_picture)"
                  "VALUES (:nickname, :password, :id)");
    query.bindValue(":nickname", username);
    query.bindValue(":password", password);
    query.bindValue(":id", id);
    if(!query.exec())
    {
        qWarning() << Q_FUNC_INFO << "Inserting user failed" << query.lastError().text();
    }
    return true;
}

bool DBFacade::authorizeUser(QString username, QString password)
{
    QSqlQuery query(*m_db);
    query.prepare("SELECT COUNT(*)"
                  "FROM users "
                  "WHERE nickname = :nickname AND password = :password");
    query.bindValue(":username",username);
    query.bindValue(":password", password);
    if(query.exec() && query.next())
    {
        bool isRegistered = query.value(0).toInt() != 0;
        return isRegistered;
    }
    else
    {
        qWarning() << Q_FUNC_INFO << "Cannot execute query" << query.lastError().text();
        return false;
    }
}

void DBFacade::addMessage(QString sender, QString receiver, QString messageText, QString timestamp)
{
    QSqlQuery query(*m_db);
}

QSqlDatabase *DBFacade::db() const
{
    return m_db;
}

void DBFacade::setDb(QSqlDatabase *db)
{
    m_db = db;
}
