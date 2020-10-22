#include "../include/client.h"
#include <QImage>
#include <QBuffer>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "../include/globals.h"

#include "../include/contactslist.h"
#include "../include/contactsmodel.h"

#include "../include/messageslist.h"
#include "../include/messagesmodel.h"

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
    buff.open(QIODevice::WriteOnly | QIODevice::Truncate);
    avatar.save(&buff);
    buff.close();
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
    QByteArray imageBase64 = imgRaw.toBase64();
    package.setData(imageBase64);


    m_connection.sendPackage(package);
}

void Client::sendDocument(QString url, QString reciver)
{
    Q_UNUSED(url)
    Q_UNUSED(reciver)
}

void Client::getContactsList()
{
    net::Package package;
    package.setSender(m_username);
    package.setDestinations({});
    package.setType(net::Package::DataType::CONTACTS_LIST);
    package.setData({}); //Don't need any data here. Placeholder for furher rework

    m_connection.sendPackage(package);
}

void Client::getMessageHistory(int idx)
{
    QString user = m_contactsModel->data(m_contactsModel->index(idx), ContactsModel::Roles::NicknameRole).toString();
    qDebug() << Q_FUNC_INFO << "getting history woth user: " << user;
    net::Package package;
    package.setSender(m_username);
    package.setDestinations({user});
    package.setType(net::Package::DataType::MESSAGE_HISTORY);
    package.setData({});

    m_connection.sendPackage(package);

}

void Client::loadMessageHistory(QJsonArray json)
{
    foreach(QJsonValue val, json)
    {
        QStringList data = val.toString().split(net::Package::delimiter());
        Message item;
        item.sender = data.first();
        item.text = data.last();
        m_messagesModel->append(item);
    }
}

void Client::addContact(QString contactData)
{
    Contact item;
    QStringList data = contactData.split(net::Package::delimiter());

    item.nickname = data.first();
    //QString path = *Globals::imagesPath + QDir::separator() + item.nickname + "_avatar.png";
    QString path = QDir::currentPath()
                 //+ QDir::separator()
                 + QLatin1String("/images/")
                 //+ QDir::separator()
                 + item.nickname + "_avatar.png";
    item.imageUrl = path;

    QImage avatar;
    QByteArray imgRaw = QByteArray::fromBase64(data.last().toLocal8Bit());

    QFile file{path};
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << Q_FUNC_INFO << "Can't create file";
    }
    if(!avatar.loadFromData(imgRaw))
    {
        qDebug() << Q_FUNC_INFO << " Can't load image from base64";
    }
    if(!avatar.save(&file, "PNG"))
    {
        qDebug() << Q_FUNC_INFO << " Can't save image to file";
    }

    file.close();

    contactsModel()->append(item);
}

void Client::newMessage(QString sender, QByteArray text)
{
    Message item;
    item.sender = sender;
    item.text = text;
}

void Client::newDocument(QString sender, QByteArray base64)
{
    Q_UNUSED(sender)
    Q_UNUSED(base64)
}

void Client::newImage(QString sender, QByteArray base64)
{
    Q_UNUSED(sender)
    Q_UNUSED(base64)
}

MessagesModel *Client::messagesModel() const
{
    return m_messagesModel;
}

void Client::setMessagesModel(MessagesModel *messagesModel)
{
    m_messagesModel = messagesModel;
}

ContactsModel *Client::contactsModel() const
{
    return m_contactsModel;
}

void Client::setContactsModel(ContactsModel *contactsModel)
{
//    if(m_contactsModel)
//    {
//        disconnect(m_contactsModel, &ContactsModel::indexChanged, this, &Client::getMessageHistory);
//    }
    m_contactsModel = contactsModel;
    connect(m_contactsModel, &ContactsModel::selectedChanged, this, &Client::getMessageHistory);
}


void Client::packageRecieved(net::Package package)
{
    QByteArray data = package.data().toByteArray();

    switch(package.type())
    {
    case net::Package::CONTACTS_LIST:
        loadContactsList(package.data().toJsonArray());
        break;
    case net::Package::REGISTRATION_REQUEST:
        emit registerResponded(data.startsWith("S") );
        break;

    case net::Package::AUTH_REQUEST:
        emit authResponded( data.startsWith("S") );
        break;
    case net::Package::MESSAGE_HISTORY:
        loadMessageHistory(package.data().toJsonArray());
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

void Client::loadContactsList(QJsonArray json)
{
    foreach(QJsonValue contact, json)
    {
        qDebug() << Q_FUNC_INFO << "Invoking addContact";
        addContact(contact.toString());
    }
}