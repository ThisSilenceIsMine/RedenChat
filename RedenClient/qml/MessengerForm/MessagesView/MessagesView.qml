import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
/*
 *
 * U N U S E D
 *
 */
ListView
{
    id: root
    property alias delegateColor: messagesDelegate.color

    delegate: MessagesDelegate
    {
        id: messagesDelegate
    }

}
