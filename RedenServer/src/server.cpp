#include "../include/server.h"

Server::Server(QObject *parent) : QObject(parent)
{

}

void Server::newConnection()
{
    QTcpSocket *socket = m_server.nextPendingConnection();
    net::Connection *connection = new net::Connection(this);
    connection->setSocket(socket);

    connect(connection, &net::Connection::newPackage, this, &Server::newPackage);
}

void Server::newPackage(const net::Package &package)
{
    switch(package.type())
    {
    case net::Package::CONTACTS_LIST: //Спислк контактов. Получаем сразе после входа в аккаунт
        qWarning() << "Why the fuck you sent me contacts list";
        break;
    case net::Package::REGISTRATION_REQUEST:

        break;
    case net::Package::AUTH_REQUEST: //Ответ на авторизацию Данные пустые = фейл

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

void Server::registerUser(net::Package package)
{

}

void Server::authorize(net::Package package)
{

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
