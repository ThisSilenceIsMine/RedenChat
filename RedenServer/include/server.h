#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QVariant>
#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#include "include/RedenNetworkLib_global.h"
#include "include/connection.h"
#include "include/package.h"

class DBFacade;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void setDatabase(DBFacade *database);
    void start();
private slots:
    void newConnection();
    void newPackage(const net::Package &package);

    void registerUser(net::Package package, net::Connection *connection);
    void authorize(net::Package package, net::Connection *connection);
    void sendMessageHistory(QStringList conversants);
    void sendContactsList(QString user);

private:
    QTcpServer m_server;
    QHash<QString, net::Connection*> m_clients;
    DBFacade *m_database;
};

#endif // SERVER_H
