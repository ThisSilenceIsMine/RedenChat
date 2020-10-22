#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QVariant>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#include "include/RedenNetworkLib_global.h"
#include "include/connection.h"
#include "include/package.h"

//#include "contactsmodel.h"

class MessagesModel;
class ContactsModel;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);


    ContactsModel *contactsModel() const;
    void setContactsModel(ContactsModel *contactsModel);

    MessagesModel *messagesModel() const;
    void setMessagesModel(MessagesModel *messagesModel);

public slots:
    void registerNewUser(QString username, QString password, QString imgUrl);
    void authorize(QString username, QString password);

    void sendMessage(QString text, QString reciver);
    void sendImage(QString url, QString reciver);
    void sendDocument(QString url, QString reciver);


    void getContactsList();
    void getMessageHistory(int idx);

    void loadContactsList(QJsonArray json);
    void loadMessageHistory(QJsonArray json);

private slots:
    void packageRecieved(net::Package package);
signals:
    void registerResponded(bool status);
    void authResponded(bool status);
private:

    void addContact(QString contactData);
    void newMessage(QString sender, QByteArray text);
    void newDocument(QString sender, QByteArray base64);
    void newImage(QString sender, QByteArray base64);

private:
    net::Connection m_connection;
    QString m_username;
    ContactsModel *m_contactsModel;
    MessagesModel *m_messagesModel;


};

#endif // CLIENT_H
