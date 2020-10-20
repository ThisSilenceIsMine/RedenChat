#include "../include/connection.h"
namespace net
{

Connection::Connection(QObject *parent)
    : QObject(parent)
    //, m_stream{&m_socket}
{
    m_serializer = new PackageJsonSerializer();
    //m_stream.setVersion(QDataStream::Qt_5_15);

    connect(&m_socket,&QTcpSocket::connected,this,&Connection::connected);
    connect(&m_socket,&QTcpSocket::disconnected,this,&Connection::disconnected);

    connect(&m_socket,&QTcpSocket::stateChanged,this,&Connection::stateChanged);
    connect(&m_socket,&QTcpSocket::readyRead,this,&Connection::readyRead);
    connect(&m_socket,qOverload<QAbstractSocket::SocketError>(&QAbstractSocket::errorOccurred),this,&Connection::error);

    connect(this, &Connection::newMessage, this, &Connection::messageReceived);
}

Connection::Connection(qintptr descriptor, QObject *parent)
    : QObject(parent)
    //, m_stream{&m_socket}
{
    m_serializer = new PackageJsonSerializer();
    //m_stream.setVersion(QDataStream::Qt_5_15);

    connect(&m_socket,&QTcpSocket::connected,this,&Connection::connected);
    connect(&m_socket,&QTcpSocket::disconnected,this,&Connection::disconnected);

    connect(&m_socket,&QTcpSocket::stateChanged,this,&Connection::stateChanged);
    connect(&m_socket,&QTcpSocket::readyRead,this,&Connection::readyRead);
    connect(&m_socket,qOverload<QAbstractSocket::SocketError>(&QAbstractSocket::errorOccurred),this,&Connection::error);

    connect(this, &Connection::newMessage, this, &Connection::messageReceived);

    setSocketDescriptor(descriptor);
}

quint16 Connection::port() const
{
    return m_socket.peerPort();
}


QHostAddress Connection::adress() const
{
    return m_socket.peerAddress();
}


IPackageSerializer *Connection::serializer() const
{
    return m_serializer;
}

void Connection::setSerializer(IPackageSerializer *serializer)
{
    m_serializer = serializer;
}

void Connection::connectToHost(QString host, quint16 port)
{
    if(m_socket.isOpen()) disconnect();

    m_socket.connectToHost(host,port);
}

void Connection::disconnect()
{
    m_socket.disconnectFromHost();
    emit disconnected();
}

void Connection::messageReceived(const Package &package)
{
    Q_UNUSED(package)
}

void Connection::connected()
{
    m_state = ConnectionState::Connected;
    emit readyForUse();
}

void Connection::disconnected()
{
    m_state = ConnectionState::Disconnected;
}

void Connection::error(QAbstractSocket::SocketError socketError)
{
    qCritical() << "Error:" << socketError << " " << m_socket.errorString();
}

void Connection::stateChanged(QAbstractSocket::SocketState socketState)
{
    Q_UNUSED(socketState)
}

void Connection::sendPackage(Package package)
{
    QByteArray block;
    QByteArray rawData = m_serializer->toBytes(package);
    QDataStream out(&block, QIODevice::WriteOnly);

    out << quint16(rawData.size()) << rawData;

    m_socket.write(block);
}

void Connection::readyRead()
{
    QDataStream in(&m_socket);

    if(m_blockSize == 0)
    {
        if(m_socket.bytesAvailable() < int(sizeof(quint16)))
        {
            return;
        }

        in >> m_blockSize;
    }

    if(m_socket.bytesAvailable() < m_blockSize)
        return;
    else
        m_blockSize = 0;

    QByteArray rawData;

    in >> rawData;

    Package message;
    bool ok;

    message = m_serializer->fromBytes(rawData, &ok);

    if(!ok)
    {
        return;
    }

    emit newPackage(message);
}

}
