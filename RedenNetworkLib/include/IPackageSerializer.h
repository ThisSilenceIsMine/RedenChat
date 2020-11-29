#ifndef IPACKAGESERIALIZER_H
#define IPACKAGESERIALIZER_H

#include <QString>
#include "package.h"
namespace net
{
class IPackageSerializer
{
public:
    virtual QByteArray toBytes(const Package &package) = 0;
    virtual Package fromBytes(const QByteArray &bytes, bool* ok) = 0;
    virtual ~IPackageSerializer() {};
};
}
#endif // IPACKAGESERIALIZER_H
