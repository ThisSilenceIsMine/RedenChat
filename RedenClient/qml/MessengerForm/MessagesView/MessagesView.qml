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
    id: messagesView
    anchors.fill: parent
    anchors.bottomMargin: messageInput.height + 75
    anchors.leftMargin: 5
    anchors.rightMargin: 5
    model: messagesModel
    spacing: 25//75

    verticalLayoutDirection: ListView.BottomToTop
    delegate: MessagesDelegate
    {
        width: ListView.view.width
        time: model.timeStamp
        username: model.nickname
        message: model.text
        avatarSource: model.nickname == contactsModel.currentDialog() ?
                          Qt.resolvedUrl("file:///" + contactsModel.currentAvatar())
                        : Qt.resolvedUrl("file:///" + applicationDirPath + "/../images/" + client.username() + "_avatar.png")
                          //"qrc:/qml/Images/Default"//model.avatar
        ListView.onAdd:
        {
            messagesView.positionViewAtBeginning()
        }
    }
}
