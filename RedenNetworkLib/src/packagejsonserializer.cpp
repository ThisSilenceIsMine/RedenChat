#include "../include/packagejsonserializer.h"
#include "package.h"
#include <QVariantMap>
#include <QStringList>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>

namespace net
{

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
    map["data"] = package.data().toByteArray().toBase64();

    return QJsonDocument::fromVariant(map).toJson();
}

Package PackageJsonSerializer::fromBytes(QByteArray bytes, bool *ok)
{
    Package package;

    QJsonParseError error;
    QJsonDocument document { QJsonDocument::fromJson(bytes, &error) };

    if(error.error != QJsonParseError::NoError)
    {
        *ok = false;
        return package;
    }

    QJsonValue sender = document["sender"].toString();
    QJsonValue destinationsList = document["destinations"];
    QJsonValue type = document["type"];
    QJsonValue data = document["data"];

    if(   sender            == QJsonValue::Undefined
       || destinationsList  == QJsonValue::Undefined
       || type              == QJsonValue::Undefined
       || data              == QJsonValue::Undefined
      )
    {
        *ok = false;
        return package;
    }

    package.setSender(sender.toString());
    package.setDestinations(qvariant_cast<QStringList>(destinationsList.toVariant()));
    package.setType(static_cast<Package::DataType>(m_types.keyToValue(type.toString().toLocal8Bit().data())));
    package.setData(QByteArray::fromBase64(data.toVariant().toByteArray()));
    *ok = true;
    return package;
}

PackageJsonSerializer::~PackageJsonSerializer()
{

}

}
