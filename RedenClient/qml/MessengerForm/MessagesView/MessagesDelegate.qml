import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import GlobalQmlSettings 1.0

Rectangle
{
    id: root

    //property alias imageSource: optionalContentImage.source
    property alias avatarSource: avatar.source
    property alias username: senderNickname.text
    property alias time: timeSpan.text
    property alias messageText: messageText.text


    RowLayout
    {
        id: rowLayout
        spacing: 10
        anchors.fill: parent
        Image
        {
            id: avatar
            Layout.preferredWidth: 50
            Layout.preferredHeight: 50
            Layout.alignment: Qt.AlignLeft
            property bool rounded: true
            property bool adapt: true
            clip: true
            fillMode: Image.PreserveAspectFit
            layer.enabled: rounded
                layer.effect: OpacityMask {
                    maskSource: Item {
                        width: avatar.width
                        height: avatar.height
                        Rectangle {
                            anchors.centerIn: parent
                            width: avatar.adapt ? avatar.width : Math.min(avatar.width, avatar.height)
                            height: avatar.adapt ? avatar.height : width
                            radius: Math.min(width, height)
                        }
                    }
                }
        }

        Rectangle
        {
            id: messageContent
            anchors.left: avatar.right
            anchors.leftMargin: 5
            Layout.alignment: Qt.AlignLeft
            //Layout.leftMargin: 5
            Label
            {
                id: senderNickname
                anchors.top: parent.top
                anchors.left: parent.left
            }
            Label
            {
                id: timeSpan
                anchors.top: parent.top
                anchors.left: senderNickname.right
                anchors.leftMargin: 15
            }
            Text
            {
                id: messageText
                anchors.fill: parent
                anchors.topMargin: (timeSpan.height + senderNickname.height) / 1.5
                color: "#ffffff"
            }
            Image
            {
                id: optionalContentImage
            }
        }
    }
}
