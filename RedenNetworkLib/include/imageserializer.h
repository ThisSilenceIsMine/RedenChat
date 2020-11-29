#ifndef IMAGESERIALIZER_H
#define IMAGESERIALIZER_H

#include <QObject>
#include <QBuffer>
#include <QByteArray>
#include <QImage>
#include <QStringView>
#include <QDebug>
#include <QFile>

class ImageSerializer
{
public:
    ImageSerializer() = delete;
    ImageSerializer(const ImageSerializer&) = delete;
    ImageSerializer(ImageSerializer&&) = delete;
    ~ImageSerializer() = delete;

//    QByteArray toBase64(const QString &path, const QString &format)
//    {
//        QImage avatar;
//        bool ok = avatar.load(path, format.toStdString().c_str());
//        if(!ok)
//        {
//            qDebug() << Q_FUNC_INFO << "Can't load image from " << path;
//        }
//        QByteArray imgRaw;
//        QBuffer buff(&imgRaw);

//        buff.open(QIODevice::WriteOnly | QIODevice::Truncate);
//        ok = avatar.save(&buff, format.toStdString().c_str());
//        if(!ok)
//        {
//            qDebug() << "Can't save image to buffer";
//        }
//        buff.close();
//        return imgRaw.toBase64();
//    }

    static QByteArray toBytes(const QString &path)
    {
        QImage avatar;
        bool ok = avatar.load(path);
        if(!ok)
        {
            qDebug() << Q_FUNC_INFO << "Can't load image from " << path;
        }
        QByteArray imgRaw;
        QBuffer buff(&imgRaw);

        buff.open(QIODevice::WriteOnly | QIODevice::Truncate);
        ok = avatar.save(&buff);
        if(!ok)
        {
            qDebug() << "Can't save image to buffer";
        }
        buff.close();
        return imgRaw;
    }

//    static void fromBase64(const QByteArray &raw, const QString &path, const QString &format = "PNG")
//    {

//        QImage avatar;
//        QByteArray imgRaw = QByteArray::fromBase64(raw);

//        QFile file{path};
//        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
//        {
//            qDebug() << Q_FUNC_INFO << "Can't create file";
//            return;
//        }
//        if(!avatar.loadFromData(imgRaw, format.toStdString().c_str()))
//        {
//            qDebug() << Q_FUNC_INFO << " Can't load image from base64";
//            return;
//        }
//        if(!avatar.save(&file, format.toStdString().c_str()))
//        {
//            qDebug() << Q_FUNC_INFO << " Can't save image to file";
//            return;
//        }
//        file.close();
//    }

    static void fromBytes(const QByteArray &raw, const QString &path)
    {

        QImage avatar;

        QFile file{path};
        if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << Q_FUNC_INFO << "Can't create file";
            return;
        }
        if(!avatar.loadFromData(raw))
        {
            qDebug() << Q_FUNC_INFO << " Can't load image";
            return;
        }
        if(!avatar.save(&file))
        {
            qDebug() << Q_FUNC_INFO << " Can't save image to file";
            return;
        }
        file.close();
    }
};


#endif // IMAGESERIALIZER_H
