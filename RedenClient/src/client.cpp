#include "../include/client.h"
#include <QImage>
#include <QBuffer>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QTime>

#include "../include/globals.h"

#include "../include/contactslist.h"
#include "../include/contactsmodel.h"

#include "../include/messageslist.h"
#include "../include/messagesmodel.h"

#include "../include/userdata.h"

Client::Client(QObject *parent) : QObject(parent),
    m_user{nullptr},
    m_contactsModel{nullptr},
    m_messagesModel{nullptr}

{
    connect(&m_connection, &net::Connection::newPackage, this, &Client::packageRecieved);

}

void Client::registerNewUser(QString username, QString password, QString imgUrl)
{
    net::Package package;
    QString fixedUrl = imgUrl.remove(0,8); // Удаляем "file:///" с начала пути

    QString delim = net::Package::delimiter();
    package.setSender(username);
    package.setType(net::Package::DataType::REGISTRATION_REQUEST);
    package.setDestinations({password});
    bool ok = false;

    QImage avatar;
    ok = avatar.load(fixedUrl);
    if(!ok)
    {
        qDebug() << Q_FUNC_INFO << "Can't load image from " << fixedUrl;
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

    package.setData(avatarBase64);


    qDebug() << Q_FUNC_INFO << username << password << fixedUrl;
    qDebug() << Q_FUNC_INFO << package.data().toByteArray();
    m_connection.sendPackage(package);
}

void Client::authorize(QString username, QString password)
{
    net::Package package;

    package.setType(net::Package::DataType::AUTH_REQUEST);
    package.setSender(username);
    package.setDestinations({});

    package.setData(password);

    m_connection.sendPackage(package);
}

void Client::sendMessage(QString text)
{
    net::Package package;
    QString delim = net::Package::delimiter();
    QString currentTime = QTime::currentTime().toString();
    package.setType(net::Package::DataType::TEXT_MESSAGE);
    package.setSender(m_user->username());
    package.setDestinations({m_contactsModel->currentDialog()});
    package.setData(currentTime + delim + text);

    qDebug() << Q_FUNC_INFO << "sending " << text << " to " << m_contactsModel->currentDialog() << " from " << package.sender();

    m_connection.sendPackage(package);
    //m_messagesModel->append(Message{m_user->username(), text, currentTime});
    newMessage(package.sender(),currentTime,text);
}

void Client::sendImage(QString url, QString reciver)
{

    net::Package package;
    QString delim = net::Package::delimiter();

    package.setType(net::Package::DataType::IMAGE);
    package.setSender(m_user->username());
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
    package.setSender(m_user->username());
    package.setDestinations({""});
    package.setType(net::Package::DataType::CONTACTS_LIST);
    package.setData({""}); //Don't need any data here. Placeholder for furher rework

    m_connection.sendPackage(package);
}

void Client::getMessageHistory(int idx)
{
    Q_UNUSED(idx) //Лень менять
    QString user = m_contactsModel->currentDialog();
    net::Package package;
    package.setSender(m_user->username());
    package.setDestinations({user});
    package.setType(net::Package::DataType::MESSAGE_HISTORY);
    package.setData({});

    m_connection.sendPackage(package);
}

void Client::loadMessageHistory(QJsonArray json)
{

    if(!m_messagesModel)
    {
        return;
    }
    m_messagesModel->reset();
    foreach(QJsonValue val, json)
    {
        newMessage(val.toString());
    }

}

void Client::addContact(const QString &contactData)
{
    Contact item;
    QStringList data = contactData.split(net::Package::delimiter());

    item.nickname = data.first();
    qDebug() << contactData;
    //QString path = *Globals::imagesPath + QDir::separator() + item.nickname + "_avatar.png";
    QString path = QDir::currentPath()
            //+ QDir::separator()
            + QLatin1String("/images/")
            //+ QDir::separator()
            + item.nickname + "_avatar.png";
    item.imageUrl = path;

    QImage avatar;
    QByteArray imgRaw = data.last().toLocal8Bit();

    ImageSerializer::fromBase64(imgRaw,path);

    contactsModel()->append(item);
}

void Client::newMessage(QString sender, QString time, QString text)
{
    if(sender == m_contactsModel->currentDialog() || sender == m_user->username())
//    if(sender == QLatin1String("Dias") || sender == m_user->username())
    {
        Message item;
        item.sender = sender;
        item.data = text;
        item.timeStamp = time;
        m_messagesModel->append(item);
    }
    else
    {
        //Уведомить о новом сообщении из другого диалога
    }

}

void Client::newMessage(QString raw)
{
    //"nickname$time$text$
    QStringList data = raw.split(net::Package::delimiter());
    QString sender = data.at(0);
    QString time = data.at(1);
    QString text = data.at(2);

    newMessage(sender,time,text);
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

void Client::requestContact(QString username)
{
    qDebug() << Q_FUNC_INFO << "GIVE ME " << username;
    if(m_contactsModel->list()->exists(username)) {
        return;
    }
    net::Package item;
    item.setSender(m_user->username());
    item.setType(net::Package::USER_DATA);
    item.setDestinations({username});
    item.setData("");

    m_connection.sendPackage(item);
}

void Client::authorize(QString username, QByteArray base64)
{

    QString path = QDir::currentPath()
            //+ QDir::separator()
            + QLatin1String("/images/")
            //+ QDir::separator()
            + username + "_avatar.png";

    QImage avatar;

    QFile file{path};
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << Q_FUNC_INFO << "Can't create file";
    }
    if(!avatar.loadFromData(QByteArray::fromBase64(base64)))
    {
        qDebug() << Q_FUNC_INFO << " Can't load image from base64";
    }
    if(!avatar.save(&file, "PNG"))
    {
        qDebug() << Q_FUNC_INFO << " Can't save image to file";
    }

    file.close();
    m_user->setUsername(username);
    m_user->setImageUrl(path);
}

UserData *Client::getUser() const
{
    return m_user;
}

void Client::setUser(UserData *user)
{
    m_user = user;
}

void Client::start()
{
    m_connection.createSocket();
    m_connection.connectToHost("127.0.0.1", 52484);
    qDebug() << "Client connected?";
}

MessagesModel *Client::messagesModel() const
{
    return m_messagesModel;
}

void Client::setMessagesModel(MessagesModel *messagesModel)
{
    if(m_messagesModel)
        m_messagesModel->disconnect(this);
    m_messagesModel = messagesModel;
}

ContactsModel *Client::contactsModel() const
{
    return m_contactsModel;
}

void Client::setContactsModel(ContactsModel *contactsModel)
{
    if(m_contactsModel)
        m_contactsModel->disconnect(this);

    m_contactsModel = contactsModel;
    connect(m_contactsModel, &ContactsModel::selectedChanged, this, &Client::getMessageHistory);
}


void Client::packageRecieved(net::Package package)
{
    QByteArray data = package.data().toByteArray();
    qDebug() << "Recieved package of type" << package.type();
    switch(package.type())
    {
    case net::Package::CONTACTS_LIST:
        qDebug() << package.data();

        loadContactsList(package.data().toStringList());
        break;
    case net::Package::REGISTRATION_REQUEST:
        if(data.startsWith("S"))
            emit registerSuccess();
        else
            emit registerFailure();
        break;

    case net::Package::AUTH_REQUEST: //Ответ на авторизацию Данные пустые = фейл
        if(!data.isEmpty() && !package.destinations().empty() && package.sender() == "")
        {
            authorize(package.destinations().first(), data);
            emit authSuccsess();
            getContactsList();
        }
        else
            emit authFailure();
        break;
    case net::Package::MESSAGE_HISTORY: //Переписка с контактом. Загружем при переключении на другой диалог
        loadMessageHistory(package.data().toJsonArray());
        break;
    case net::Package::USER_DATA: //Добавляем 1 контакт
        addContact(data);
        break;
    case net::Package::TEXT_MESSAGE: //Текстовое сообщение
        newMessage(package.sender() + net::Package::delimiter() + data); //никнейм$время$текст
        break;
    case net::Package::IMAGE:
        newImage(package.sender(), data);
        break;
    case net::Package::DOCUMENT:
        newDocument(package.sender(), data);
        break;
    }
}

void Client::loadContactsList(const QStringList &json)
{
    if(json.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Array is empty";
        return;
    }
    foreach(QString contact, json)
    {
        qDebug() << Q_FUNC_INFO << "Invoking addContact";
        addContact(contact);
    }
}
