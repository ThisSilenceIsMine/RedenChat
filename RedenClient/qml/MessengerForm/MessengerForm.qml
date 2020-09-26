import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import GlobalQmlSettings 1.0
import MessengerForm.MessageInputField 1.0
import MessengerForm.MessagesView 1.0

Rectangle
{
    id: root
    height: GlobalSettings.defaultFormHeight
    width: GlobalSettings.defaultFormWidth
    SplitView {
        id: splitView
        anchors.fill: parent

        handle: Rectangle {
            implicitWidth: 3
            implicitHeight: 4
            color: SplitHandle.pressed ? Material.color(Material.Grey)//"#81e889"
                                       : (SplitHandle.hovered ?
                                              Qt.lighter(Material.color(Material.Grey), 1.1)
                                            :        "555555")
        }
        Rectangle {
            id: contactsField
            implicitWidth: 300
            color: Material.backgroundColor
        }
        Rectangle {
            id: chatField
            implicitWidth: 50
            color: Material.backgroundColor
            ListModel
            {
                id: sampleMessageModel

                ListElement
                {
                    // @disable-check M16
                    nickname: "Vasya"
                    // @disable-check M16
                    timeStamp: "22:15"
                    // @disable-check M16
                    text: "Hail 2 U, my very best friend, this is quite a long debugging text"
                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"

                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Raiden"
                    // @disable-check M16
                    timeStamp: "22:33"
                    // @disable-check M16
                    text: "Hail 2 U, my very best friend, this is quite a very very very very very very very very very very very long debugging text"
                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Raiden"
                    // @disable-check M16
                    timeStamp: "22:13"
                    // @disable-check M16
                    text: "Heloo, ma friend"
                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }

            }

            ListView
            {
                id: messagesView
                anchors.fill: parent
                anchors.bottomMargin: messageInput.height + 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                model: sampleMessageModel
                spacing: 10
                verticalLayoutDirection: ListView.BottomToTop
                delegate: MessagesDelegate
                    {
                        width: ListView.view.width
                        time: model.timeStamp
                        username: model.nickname
                        messageText: model.text
                        avatarSource: model.avatar
                    }

            }

            MessageInputField
            {
                id: messageInput
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }
}
