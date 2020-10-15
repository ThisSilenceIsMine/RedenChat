#ifndef PACKAGE_H
#define PACKAGE_H

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>

class Package
{
public:
    enum DataType : int
    {
        REGISTRATION_REQUEST = 0,
        AUTH_REQUEST = 1,
        USER_DATA = 2,
        TEXT_MESSAGE = 3,
        IMAGE = 4,
        DOCUMENT = 5
    };
public:
    Package() = default;
    Package(const Package&) = default;
    Package(Package&&) = default;
    QString sender() const;
    void setSender(const QString &sender);

    QStringList destinations() const;
    void setDestinations(const QStringList &destinations);

    DataType type() const;
    void setType(const DataType &type);

    QVariant data() const;
    void setData(const QVariant &data);

private:
    QString m_sender;
    QStringList m_destinations;
    DataType m_type;
    QVariant m_data;
};

#endif // PACKAGE_H
