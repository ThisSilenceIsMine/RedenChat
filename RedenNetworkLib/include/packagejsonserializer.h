#ifndef PACKAGEJSONSERIALIZER_H
#define PACKAGEJSONSERIALIZER_H

#include <IPackageSerializer.h>
#include <QObject>
#include <QByteArray>
#include <QMetaEnum>


class PackageJsonSerializer : public IPackageSerializer
{
public:
    PackageJsonSerializer();

    // IPackageSerializer interface
public:
    QByteArray toBytes(Package package) override;
    Package fromBytes(QByteArray bytes) override;
    ~PackageJsonSerializer() override;
private:
    static QMetaEnum m_types;
};

#endif // PACKAGEJSONSERIALIZER_H
