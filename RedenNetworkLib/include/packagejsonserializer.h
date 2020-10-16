#ifndef PACKAGEJSONSERIALIZER_H
#define PACKAGEJSONSERIALIZER_H
#include "RedenNetworkLib_global.h"
#include <IPackageSerializer.h>
#include <QObject>
#include <QByteArray>
#include <QMetaEnum>

namespace net
{
class REDENNETWORKLIB_EXPORT PackageJsonSerializer
        : public IPackageSerializer
{
public:
    PackageJsonSerializer();

    // IPackageSerializer interface
public:
    QByteArray toBytes(Package package) override;
    Package fromBytes(QByteArray bytes, bool *ok) override;
    ~PackageJsonSerializer() override;
private:
    static QMetaEnum m_types;
};
}
#endif // PACKAGEJSONSERIALIZER_H
