#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QString>
#include <QMetaEnum>
#include <QDataStream>

#include "packagejsonserializer.h"
#include "RedenNetworkLib_global.h"
#include "package.h"
namespace net
{

class REDENNETWORKLIB_EXPORT Connection : public QObject
{
    Q_OBJECT
    enum ConnectionState
    {
        Connected,
        Disconnected
    };
    Q_ENUM(ConnectionState)
public:
    explicit Connection(QObject *parent = nullptr);
    Connection(qintptr handle, QObject *parent = nullptr);

    quint16 port() const;
    QHostAddress adress() const;

    IPackageSerializer *serializer() const;
    void setSerializer(IPackageSerializer *serializer);

    void setSocketDescriptor(qintptr descriptor);

    void sendPackage(Package package);
public slots:
    void connectToHost(QString host, quint16 port);
    void disconnect();

    void messageReceived(const Package &package);
signals:
    void readyForUse();
    void newPackage(const Package &package);

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();
private:
    //QDataStream m_stream;
    QTcpSocket m_socket;
    IPackageSerializer *m_serializer;
    ConnectionState m_state;
    quint16 m_blockSize;

}; //class Connection

} //namespace net
#endif // CONNECTION_H
