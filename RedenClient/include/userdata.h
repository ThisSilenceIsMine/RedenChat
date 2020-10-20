#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);

signals:

private:
    QString m_username;
    QString m_imageUrl;

};

#endif // USERDATA_H
