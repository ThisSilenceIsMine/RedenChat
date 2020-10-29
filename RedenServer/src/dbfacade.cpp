#include "../include/dbfacade.h"
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include "include/package.h"
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

void DBFacade::addMessage(QString sender, QString receiver, QString messageText)
{
    QSqlQuery query(*m_db);

    auto queryFailure = [](){
            qWarning() << Q_FUNC_INFO << "Cannot execute query";
    };

    query.prepare("SELECT :id"
                  "FROM conversations"
                  "WHERE (title = CONCAT(:name1, \"$\", :name2))"
                  "OR"
                  "(title = CONCAT(:name2, \"$\", :name1))");
    query.bindValue(":name1", sender);
    query.bindValue(":name2", receiver);
    int conversationId;
    if(!query.exec())
    {
        queryFailure();
    }
    if(query.next())
    {
        conversationId = query.value(0).toInt();
    }
    else
    {
        qWarning() << "Conversation between" << sender << "and" << receiver << "doesn't exist";
        return;
    }
    query.finish();
    query.prepare("SELECT id"
                  "FROM users"
                  "WHERE nickname = :sender");
    query.bindValue(":sender",sender);
    int senderId;
    if(!query.exec())
    {
        queryFailure();
    }
    if(query.next())
    {
        senderId = query.value(0).toInt();
    } else {
        qWarning() << "User " << sender << "not registered";
        return;
    }
    query.finish();
    query.prepare("INSERT INTO messages(id_sender, id_conversation, created_at"
                  "VALUES(:senderId, :convId, :message, :createdAt)");
    query.bindValue(":senderId", senderId);
    query.bindValue(":convId", conversationId);
    query.bindValue(":message",messageText);
    query.bindValue(":createdAt",QDateTime::currentDateTime());
    if(!query.exec())
    {
        queryFailure();
    }
}

QStringList DBFacade::messageHistory(QString user1, QString user2)
{
    QSqlQuery query(*m_db);
    QString messagesSelect = "SELECT u.name, m.created_at, m.message"
                             "FROM messages AS m"
                             "INNER JOIN users AS u"
                             "ON u.id = m.id_sender"
                             "WHERE id_conversation IN"
                             "("
                             "SELECT id "
                             "FROM conversations"
                             "WHERE (title = CONCAT(:name1, \"$\", :name2))"
                             "OR"
                             "(title = CONCAT(:name2, \"$\", :name1))"
                             ")"
                             "ORDER BY created_at ASC";
    query.prepare(messagesSelect);
    query.bindValue(":name1",user1);
    query.bindValue(":name2",user2);
    bool ok = query.exec();
    if(!ok){
        qWarning() << Q_FUNC_INFO << "Cannot execute messages select";
    }
    QStringList messages;
    while(query.next()) {
        messages << query.value(0).toString() + net::Package::delimiter()
                + query.value(1).toDateTime().toString() + net::Package::delimiter()
                + query.value(3).toString();
    }
    return messages;
}


void DBFacade::newConversation(QString user1, QString user2)
{
     QString conversationInsert =
             "INSERT INTO conversations(title, id_creator)"
             "SELECT CONCAT(:user1, \"$\", :user2)"
             "WHERE"
             "("
                "SELECT COUNT(*)"
                "FROM conversations"
                "WHERE ("
                "title = CONCAT(:user1, \"$\", :user2))"
                "OR"
                "(title = CONCAT(:user2, \"$\", :user1)"
                ") = 0"
             "AND"
                "(:user1 IN (SELECT nickname FROM users))"
             "AND"
                "(:user2 IN (SELECT nickname FROM users))";
    QSqlQuery query(*m_db);
    query.bindValue(":user1", user1);
    query.bindValue(":user2",user2);

    bool ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot execute query";
    }
}

QString DBFacade::userImage(QString username)
{
    QString selectQuery =
            "SELECT url FROM attachments AS at"
            "WHERE at.id IN "
            "("
                "SELECT id_picture"
                "FROM users"
                "WHERE nickname = :username"
            ")";
    QSqlQuery query(*m_db);
    query.prepare(selectQuery);
    query.bindValue(":username", username);
    bool ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot get user url";
    }
    if(query.next()) {
        return query.value(0).toString();
    } else {
        return {};
    }
}

QSqlDatabase *DBFacade::db() const
{
    return m_db;
}

void DBFacade::setDb(QSqlDatabase *db)
{
    m_db = db;
}
