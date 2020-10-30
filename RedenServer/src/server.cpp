#include "../include/server.h"
#include "../include/dbfacade.h"
#include <QImage>
#include <QBuffer>
#include <QDir>
Server::Server(QObject *parent)
    : QObject(parent)
{
    qInfo() << connect(&m_server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::newConnection()
{
    qInfo() << "Connecting...";
    QTcpSocket *socket = m_server.nextPendingConnection();

    net::Connection *connection = new net::Connection(this);
    connection->setSocket(socket);

    qInfo() << "Connected" << socket->socketDescriptor();
    qInfo() << connect(connection, &net::Connection::newPackage, this, &Server::newPackage);
}

void Server::newPackage(const net::Package &package)
{
    qInfo() << Q_FUNC_INFO << "Package recieved successfully!";
    net::Connection *connection = qobject_cast<net::Connection *>(sender());

    switch(package.type())
    {
    case net::Package::CONTACTS_LIST: //Спислк контактов. Получаем сразе после входа в аккаунт
        qWarning() << "Why the fuck you sent me contacts list";
        break;
    case net::Package::REGISTRATION_REQUEST:
        registerUser(package,connection);
        break;
    case net::Package::AUTH_REQUEST:
        authorize(package, connection);
        break;
    case net::Package::MESSAGE_HISTORY: //Переписка с контактом. Загружем при переключении на другой диалог

        break;
    case net::Package::USER_DATA: //Добавляем 1 контакт

        break;
    case net::Package::TEXT_MESSAGE: //Текстовое сообщение

        break;
    case net::Package::IMAGE:

        break;
    case net::Package::DOCUMENT:

        break;
    }
}

void Server::registerUser(net::Package package, net::Connection *connection)
{
    qInfo() << Q_FUNC_INFO;
    //QList<QByteArray> data = package.data().toByteArray().split('$');
//    if(data.size() < 2) {
//        qDebug() << "Can't split data";
//        return;
//    }
    QString username = package.sender();
    QString password = package.destinations().toVector().first();
    qDebug() << "PW: " << password;
//    qDebug() << "DATA: " << data.last();
    QString path = QDir::currentPath()
            //+ QDir::separator()
            + QLatin1String("/images/")
            //+ QDir::separator()
            + username + "_avatar.png";

    QImage avatar;
    QByteArray imgRaw = QByteArray::fromBase64(package.data().toByteArray());

    QFile file{path};
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << Q_FUNC_INFO << "Can't create file";
        return;
    }
    if(!avatar.loadFromData(imgRaw, "PNG"))
    {
        qDebug() << Q_FUNC_INFO << " Can't load image from base64";
        return;
    }
    if(!avatar.save(&file, "PNG"))
    {
        qDebug() << Q_FUNC_INFO << " Can't save image to file";
        return;
    }
    file.close();

    //Отправляем клиенту результат регистрации
    net::Package responce;
    responce.setSender("");
    responce.setDestinations({username});
    responce.setType(net::Package::DataType::REGISTRATION_REQUEST);
    if(m_database->registerUser(username, password, path))
    {
        responce.setData(QStringLiteral("S"));
    } else {
        responce.setData(QStringLiteral("F"));
    }
    connection->sendPackage(responce);
}

void Server::authorize(net::Package package, net::Connection *connection)
{
    qInfo() << Q_FUNC_INFO;
    QString username = package.sender();
    QString password = package.data().toString();
    if(m_database->authorizeUser(username,password))
    {
        m_clients[username] = connection;
        net::Package item;
        item.setSender("");
        item.setDestinations({username});
        item.setType(net::Package::DataType::AUTH_REQUEST);
        QString url = m_database->userImage(username);
        QImage avatar;
        bool ok = avatar.load(url);
        if(!ok)
        {
            qDebug() << Q_FUNC_INFO << "Can't load image from " << url;
        }
        QByteArray imgRaw;
        QBuffer buff(&imgRaw);

        buff.open(QIODevice::WriteOnly | QIODevice::Truncate);
        ok = avatar.save(&buff, "PNG");
        if(!ok)
        {
            qDebug() << "Can't save image to buffer";
        }
        buff.close();
        QString avatarBase64 = imgRaw.toBase64();
        item.setData(avatarBase64);

        connection->sendPackage(item);
    } else {
        qDebug() << "User not registered";
        net::Package item;
        item.setSender("");
        item.setDestinations({});
        item.setType(net::Package::DataType::AUTH_REQUEST);
        item.setData(QVariant(""));
        connection->sendPackage(item);
    }
}

void Server::sendMessageHistory(QStringList conversants)
{

}

void Server::sendContactsList(QString user)
{

}

void Server::setDatabase(DBFacade *database)
{
    m_database = database;
}

void Server::start()
{
    if(m_server.listen(QHostAddress::Any, 52484))
        qInfo() << "Listening on " << m_server.serverAddress().toString() << ":" << m_server.serverPort();
    else
        qInfo() << "Server not started!";
}
