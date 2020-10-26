import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import GlobalQmlSettings 1.0
import MessengerForm.RoundImage 1.0

Rectangle
{
    id: root

    //property alias imageSource: optionalContentImage.source
    property string avatarSource
    property string username
    property string time
    property string message
//    height: rowLayout.height + 21
//    Rectangle
//    {
//        id: delimiter
//        height: 1
//        width: rowLayout.width
//        color: Qt.lighter(Material.backgroundColor)
//        anchors.bottom: rowLayout.top
//        anchors.bottomMargin: 20
//    }

    RowLayout
    {
        id: rowLayout
        spacing: 10
        anchors.fill: parent
        RoundImage
        {
            id: avatar
            source: avatarSource
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignLeft
        }

        Item
        {
            id: messageContent

            //anchors.left: avatar.right

            //anchors.leftMargin: 5
            //Layout.fillWidth: true

            Layout.alignment: Qt.AlignLeft
            Layout.leftMargin: 5
            Layout.fillWidth: true
            Layout.fillHeight: true
            //Layout.leftMargin: 5
            Label
            {
                id: senderNickname
                anchors.top: parent.top
                anchors.left: parent.left
                text: username
            }
            Label
            {
                id: timeSpan
                anchors.top: parent.top
                anchors.left: senderNickname.right
                anchors.leftMargin: 15
                text: time
            }
            Text
            {
                id: messageText
                anchors.fill: parent
                anchors.topMargin: (timeSpan.height + senderNickname.height) / 1.5
                color: "#ffffff"
                text: message
                wrapMode: Text.Wrap
            }
            Image
            {
                id: optionalContentImage
            }
        }
    }
}
