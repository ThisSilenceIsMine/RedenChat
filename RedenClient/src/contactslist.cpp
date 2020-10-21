#include "../include/contactslist.h"

ContactsList::ContactsList(QObject *parent) : QObject(parent)
{

}

bool ContactsList::setItemAt(int index, const Contact &item)
{
    if(index < 0 || index >= m_items.size())
        return false;

    const Contact &oldItem = m_items.at(index);

    if(item.nickname == oldItem.nickname && item.imageUrl == oldItem.imageUrl)
        return false;

    m_items[index] = item;
    return true;
}

QList<Contact> &ContactsList::items()
{
    return m_items;
}

void ContactsList::appendItem()
{
    emit preItemAppended();

    m_items.append(Contact{});

    emit postItemAppended();
}
