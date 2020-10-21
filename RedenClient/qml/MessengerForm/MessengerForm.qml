import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import GlobalQmlSettings 1.0
import MessengerForm.MessageInputField 1.0
import MessengerForm.MessagesView 1.0
import MessengerForm.ContactsView 1.0

import reden.models.contactsModel 1.0

Rectangle
{
    id: root
    height: GlobalSettings.defaultFormHeight
    width: GlobalSettings.defaultFormWidth
    FontLoader { id: starsetFont; source: "../fonts/jaapokkisubtract-regular.ttf" }
    FontLoader { id: emojiFont; source: "../fonts/OpenSansEmoji.ttf" }
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
        Rectangle
        {
            id: contactsField
            implicitWidth: 300
            color: Material.backgroundColor
            Label
            {
                id: logo_text
                color: Material.color(Material.Red)
                text: "R E D E N"
                font.family: starsetFont.name
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 10
                //Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                font.pointSize: 32
                //Layout.topMargin: 10
            }
            ListModel
            {
                id: sampleContactsModel

                ListElement
                {
                    // @disable-check M16
                    nickname: "Vasya"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"

                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Anton"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "$a$h@"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Alex"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Ivan"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "SuperCatGirlLover1337"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
                ListElement
                {
                    // @disable-check M16
                    nickname: "Some decnly long nickname"

                    // @disable-check M16
                    avatar: "qrc:/qml/Images/Default"
                }
            }

            ContactsView
            {
                id: contactsView
                model: contactsModel
                anchors.fill: parent
                anchors.top: logo_text.bottom
                anchors.topMargin: logo_text.height
                Component.onCompleted:
                {
//                    for(var i = 0; i < 20; ++i)
//                    {
//                        sampleContactsModel.append({"nickname":"Some decent nickname", "avatar":"qrc:/qml/Images/Default"})
//                    }
                }
            }

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
                anchors.bottomMargin: messageInput.height + 75
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                model: sampleMessageModel
                spacing: 75
                verticalLayoutDirection: ListView.BottomToTop
                delegate: MessagesDelegate
                {
                    width: ListView.view.width
                    time: model.timeStamp
                    username: model.nickname
                    message: model.text
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
