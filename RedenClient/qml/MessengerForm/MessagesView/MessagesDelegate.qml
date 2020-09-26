import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0

Rectangle
{
    id: root
    radius: 3
    color: Qt.lighter(Material.color(Material.Teal))
    property alias imageSource: optionalContentImage.source
    property alias messageBgColor: messageBackground.color
    property alias username: senderNickname.text
    property alias time: timeSpan.text
    property alias messageText: messageText.text
    implicitWidth: messageText.width
    implicitHeight: messageText.height + senderNickname.height + 25
//    property alias document
    Rectangle
    {
        id: messageBackground
        anchors.fill: parent
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
            anchors.topMargin: (timeSpan.height + senderNickname.height) / 2
            color: "#ffffff"
        }
        Image
        {
            id: optionalContentImage

        }
    }
}
