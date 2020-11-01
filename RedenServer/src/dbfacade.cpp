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
                  "VALUES (:null, :url)");

    query.bindValue(":null", QVariant());
    query.bindValue(":url", imageUrl);

    if(!query.exec())
    {
        qWarning() << Q_FUNC_INFO << "Inserting image failed" << query.lastError().text();
        return false;
    }
    int id = query.lastInsertId().toInt();
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
                  "WHERE nickname = :username AND password = :password");
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
                + query.value(2).toString();
    }
    return messages;
}


bool DBFacade::newConversation(const QString &user1, const QString &user2)
{
    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO conversations(title, id_creator) "
                  "SELECT CONCAT(:user1, \"$\", :user2), :null "
                  "WHERE"
                  "("
                     "SELECT COUNT(*) "
                     "FROM conversations "
                     "WHERE "
                     "(title = CONCAT(:user1, \"$\", :user2)) "
                     "OR "
                     "(title = CONCAT(:user2, \"$\", :user1))"
                     ") = 0 "
                  "AND "
                     "(:user1 IN (SELECT nickname FROM users)) "
                  "AND "
                     "(:user2 IN (SELECT nickname FROM users)) ");
    query.bindValue(":user1", user1);
    query.bindValue(":user2",user2);
    query.bindValue(":null", QVariant());

    bool ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot insert to conversations" << query.lastError().text();
        return false;
    }
    auto queryResultId = query.lastInsertId();
    if(!queryResultId.isValid()) {
        return false;
    }
    int conversationId = queryResultId.toInt();
    query.finish();
    const QString participatsIncert =
            "INSERT INTO parritcipants (id_conversation, id_user) "
            "SELECT :conversationId, u.id "
            "FROM users u "
            "WHERE u.nickname = :nickname ";
    query.prepare(participatsIncert);
    query.bindValue(":conversationId", conversationId);
    query.bindValue(":nickname", user1);
    ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot insert to parrticipants" << query.lastError().text();
        return false;
    }
    query.finish();
    query.prepare(participatsIncert);
    query.bindValue(":conversationId", conversationId);
    query.bindValue(":nickname", user2);
    ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot insert to parrticipants";
        return false;
    }
    return true;

}

QString DBFacade::userImage(QString username)
{
    QSqlQuery query(*m_db);

    query.prepare("SELECT at.url "
                  "FROM attachments at "
                  "INNER JOIN users u "
                  "ON u.id_picture = at.id "
                  "WHERE u.nickname = :username");

    qDebug() << Q_FUNC_INFO << "Getting url for " << username;
    query.bindValue(":username", username);
    bool ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << "Cannot get user url" << query.lastError().text();
    }
    if(query.next()) {
        return query.value(0).toString();
    } else {
        return {};
    }
}

void DBFacade::newMessage(const QString &sender, const QStringList &recievers, const QString &text, const QString &dateTime)
{
    QString insertMessageQuery =
            "INSERT INTO messages (id_sender, id_conversation, message, created_at, deleted_at) "
            "SELECT u.id, c.id, :text, :datetime, :deletedat"
            "FROM users u "
            "INNER JOIN parritcipants p ON u.id = p.id_user "
            "INNER JOIN conversations c ON p.id_conversation = c.id "
            "WHERE (c.title LIKE CONCAT(:sender, '$', :receiver)) "
            "OR (c.title LIKE CONCAT(:receiver, '$', :sender)) "
            "AND u.nickname = :sender";
    QSqlQuery query(*m_db);
    query.prepare(insertMessageQuery);
    query.bindValue(":text", text);
    query.bindValue(":datetime", QDateTime::fromString(dateTime));
    query.bindValue(":deletedat", QVariant());
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", recievers.first());

    bool ok = query.exec();
    if(!ok) {
        qWarning() << Q_FUNC_INFO << query.lastError().text();
    }
}

QHash<QString, QString> DBFacade::contactsList(QString user)
{
    QSqlQuery query(*m_db);
    QString queryString =
            "SELECT u.nickname, a.url "
            "FROM users u "
            "INNER JOIN attachments a ON a.id = u.id_picture "
            "INNER JOIN parritcipants p ON u.id = p.id_user "
            "INNER JOIN conversations c ON p.id_conversation = c.id "
            "WHERE u.nickname != :username";
    query.prepare(queryString);
    query.bindValue(":username", user);
    bool ok = query.exec();
    if(!ok) {
        qDebug() << Q_FUNC_INFO << query.lastError().text();
    }
    QHash<QString, QString> contacts;
    while(query.next()) {
        QString contactName = query.value(0).toString();
        QString url = query.value(1).toString();
        contacts[contactName] = url;
    }
    return contacts;
}

QSqlDatabase *DBFacade::db() const
{
    return m_db;
}

void DBFacade::setDb(QSqlDatabase *db)
{
    m_db = db;
}
