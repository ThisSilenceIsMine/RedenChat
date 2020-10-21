#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>

#include "contactslist.h"

class ContactsModel : public QAbstractListModel
{
    Q_OBJECT
//    Q_PROPERTY(ContactsList m_list READ list)
public:
    enum Roles
    {
        NicknameRole = Qt::UserRole + 1,
        ImageRole
    };
    ContactsModel(QObject *parent = nullptr);
    ContactsList *list() const;
    void setList(ContactsList *list);

    void append(const Contact &item);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    ContactsList *m_list;
};

#endif // CONTACTSMODEL_H
