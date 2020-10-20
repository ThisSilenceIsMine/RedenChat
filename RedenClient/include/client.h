#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QVariant>
#include <QDebug>

#include "include/RedenNetworkLib_global.h"
#include "include/connection.h"
#include "include/package.h"
#include "contactsmodel.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    ContactsList *contacts() const;
    void setContacts(ContactsList *contacts);

public slots:
    void registerNewUser(QString username, QString password, QString imgUrl);
    void authorize(QString username, QString password);

    void sendMessage(QString text, QString reciver);
    void sendImage(QString url, QString reciver);
    void sendDocument(QString url, QString reciver);
private slots:
    void packageRecieved(net::Package package);
signals:
    void registerResponded(bool status);
    void authResponded(bool status);
private:
    void loadMessageHistory(QString json);
    void addContact(QString contactData);
    void newMessage(QString sender, QString text);
    void newDocument(QString sender, QString base64);
    void newImage(QString sender, QString base64);

private:
    net::Connection m_connection;
    QString m_username;
    ContactsList *m_contacts;


};

#endif // CLIENT_H
