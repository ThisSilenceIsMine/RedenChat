#ifndef DBFACADE_H
#define DBFACADE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class DBFacade : public QObject
{
    Q_OBJECT
public:
    explicit DBFacade(QObject *parent = nullptr);

    QSqlDatabase *db() const;
    void setDb(QSqlDatabase *db);

    bool registerUser(QString username, QString password, QString imageUrl);
    bool authorizeUser(QString username, QString password);
    void addMessage(QString sender, QString receiver, QString messageText, QString timestamp);
//    QStringList messageHistory(QStringList conversants);
//    bool getUserData(QStringView username, QString* imageUrl);

signals:
    void error();

private:
    QSqlDatabase *m_db;
};

#endif // DBFACADE_H
