#include "../include/client.h"
#include <QImage>
#include <QBuffer>
#include "globals.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&m_connection, &net::Connection::newPackage, this, &Client::packageRecieved);
}

void Client::registerNewUser(QString username, QString password, QString imgUrl)
{
    net::Package package;
    QString delim = net::Package::delimiter();
    package.setType(net::Package::DataType::REGISTRATION_REQUEST);
    package.setSender(m_username);
    package.setDestinations({});

    QImage avatar;
    avatar.load(imgUrl);
    QByteArray imgRaw;
    QBuffer buff(&imgRaw);

    avatar.save(&buff);

    QString avatarBase64 = imgRaw.toBase64();

    package.setData(username + delim +
                    password + delim +
                    avatarBase64);

    m_connection.sendPackage(package);
}

void Client::authorize(QString username, QString password)
{
    net::Package package;
    QString delim = net::Package::delimiter();

    package.setType(net::Package::DataType::AUTH_REQUEST);
    package.setSender(m_username);
    package.setDestinations({});

    package.setData(username + delim +
                    password);

    m_connection.sendPackage(package);
}

void Client::sendMessage(QString text, QString to)
{
    net::Package package;
    QString delim = net::Package::delimiter();

    package.setType(net::Package::DataType::TEXT_MESSAGE);
    package.setSender(m_username);
    package.setDestinations({to});
    package.setData(text);

    m_connection.sendPackage(package);
}

void Client::sendImage(QString url, QString reciver)
{

    net::Package package;
    QString delim = net::Package::delimiter();

    package.setType(net::Package::DataType::IMAGE);
    package.setSender(m_username);
    package.setDestinations({reciver});

    QImage image;
    image.load(url);
    QByteArray imgRaw;
    QBuffer buff(&imgRaw);

    image.save(&buff);
    QString imageBase64 = imgRaw.toBase64();
    package.setData(imageBase64);


    m_connection.sendPackage(package);
}

void Client::sendDocument(QString url, QString reciver)
{
    Q_UNUSED(url)
    Q_UNUSED(reciver)
}

void Client::loadMessageHistory(QString json)
{
    Q_UNUSED(json)
}

void Client::addContact(QString contactData)
{
    Contact item;

    QString path = *Globals::imagesPath + QDir::separator() + item.nickname + "_avatar.png";
    QStringList data = contactData.split("$");

    item.nickname = contactData.at(0);
    item.imageUrl = path;

    QImage avatar;
    QByteArray imgRaw = QByteArray::fromBase64(data.last().toLocal8Bit());
    QBuffer buff(&imgRaw);

    avatar.load(&buff, "PNG");
    avatar.save(path, "PNG");

    model()->append(item);
}

void Client::newMessage(QString sender, QString text)
{
    Q_UNUSED(sender)
    Q_UNUSED(text)
    //!!!!!!!!!!!!!!!!!!!!
    //!!! IMPLEMENT ME !!!
    //!!!!!!!!!!!!!!!!!!!!
}

ContactsModel *Client::model() const
{
    return m_model;
}

void Client::setModel(ContactsModel *model)
{
    m_model = model;
}

void Client::packageRecieved(net::Package package)
{
    QString data = package.data().toString();

    switch(package.type())
    {
    case net::Package::REGISTRATION_REQUEST:
        emit registerResponded(data.startsWith("S") );
        break;

    case net::Package::AUTH_REQUEST:
        emit authResponded( data.startsWith("S") );
        break;
    case net::Package::MESSAGE_HISTORY:
        loadMessageHistory(data);
        break;
    case net::Package::USER_DATA:
        addContact(data);
        break;
    case net::Package::TEXT_MESSAGE:
        newMessage(package.sender(), data);
        break;
    case net::Package::IMAGE:
        newImage(package.sender(), data);
        break;
    case net::Package::DOCUMENT:
        newDocument(package.sender(), data);
        break;
    }
}
