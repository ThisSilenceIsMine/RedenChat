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
#include "include/imageserializer.h"
//#include "userdata.h"
//#include "contactsmodel.h"

class MessagesModel;
class ContactsModel;
class UserData;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    ContactsModel *contactsModel() const;
    void setContactsModel(ContactsModel *contactsModel);

    MessagesModel *messagesModel() const;
    void setMessagesModel(MessagesModel *messagesModel);

    UserData *getUser() const;
    void setUser(UserData *user);

    Q_INVOKABLE QString username() const;

    void start(QString hostIp = "127.0.0.1", quint16 port = 52484);

public slots:
    void registerNewUser(QString username, QString password, QString imgUrl);
    void authorize(QString username, QString password);

    void sendMessage(QString text);
    void sendImage(QString url, QString reciver);
    void sendDocument(QString url, QString reciver);

    void getContactsList();
    void getMessageHistory(int idx);

    void loadContactsList(const QStringList &json);
    void loadMessageHistory(const QStringList &json);

    void requestContact(QString username);

    void qmlNotifyUnreadMessage(QString sender);
private slots:
    void packageRecieved(net::Package package);
signals:
    void registerSuccess();
    void registerFailure();

    void authSuccsess();
    void authFailure();

    void notifyMessage(QString sender);
private:
    void addContact(const QString &contactData);
    void addMessage(QString);
    void newMessage(QString sender, QString time,QString text);
    void newMessage(QString raw);
    void newDocument(QString sender, QByteArray base64);
    void newImage(QString sender, QByteArray base64);

    void authorize(QString username, QByteArray base64);
private:
    UserData *m_user;
    net::Connection m_connection;
    ContactsModel *m_contactsModel;
    MessagesModel *m_messagesModel;
    QStringList m_toNotify;
};

#endif // CLIENT_H
