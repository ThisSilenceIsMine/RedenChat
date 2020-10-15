#include "../include/packagejsonserializer.h"
#include <QVariantMap>
#include <QStringList>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

PackageJsonSerializer::PackageJsonSerializer()
{
    m_types = QMetaEnum::fromType<Package::DataType>();
}


QByteArray PackageJsonSerializer::toBytes(Package package)
{

    QVariantMap map;
    map["sender"] = package.sender();
    map["destinations"] = QVariant(package.destinations());
    map["type"] = QVariant( m_types.valueToKey(package.type()) );
    map["data"] = package.data();

    return QJsonDocument::fromVariant(map).toJson();
}

Package PackageJsonSerializer::fromBytes(QByteArray bytes)
{
    QJsonDocument document { QJsonDocument::fromJson(bytes) };

    Package package;
    QString sender = document["sender"].toString();
    QStringList destinationsList = qvariant_cast<QStringList>(document["destinations"].toVariant());
    Package::DataType type = static_cast<Package::DataType>(
                                                            m_types.keyToValue(document["type"].toString().toLocal8Bit().data())
                                                           );
    QVariant data = document["data"].toVariant();
    package.setSender(sender);
    package.setDestinations(destinationsList);
    package.setType(type);
    package.setData(data);

    return package;
}
