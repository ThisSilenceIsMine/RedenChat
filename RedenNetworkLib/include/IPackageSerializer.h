#ifndef IPACKAGESERIALIZER_H
#define IPACKAGESERIALIZER_H

#include <QString>
#include "package.h"

class IPackageSerializer
{
    virtual QByteArray toBytes(Package package) = 0;
    virtual Package fromBytes(QByteArray bytes) = 0;
    virtual ~IPackageSerializer() = 0;
};

#endif // IPACKAGESERIALIZER_H
