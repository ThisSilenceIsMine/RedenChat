import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import GlobalQmlSettings 1.0
import MessengerForm.RoundImage 1.0

RowLayout
{
    id: rowLayout

    property string avatarSource
    property string username
    property string time
    property string message

    spacing: 10
    RoundImage
    {
        id: icon
        source: avatarSource
        Layout.preferredWidth: 40
        Layout.preferredHeight: 40
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
    }

    ColumnLayout
    {
        Item
        {
            id: messageContent

            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.leftMargin: 5
            Layout.fillWidth: true
            //            Layout.fillHeight: true
            RowLayout
            {
                Label
                {
                    id: senderNickname
                    //            anchors.top: parent.top
                    //            anchors.left: parent.left
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: username
                }
                Label
                {
                    id: timeSpan
                    //            anchors.top: parent.top
                    //            anchors.left: senderNickname.right
                    //            anchors.leftMargin: 15
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: time
                }
            }
        }
        Label
        {

            id: messageText
            //            anchors.fill: parent
            //            anchors.topMargin: (timeSpan.height + senderNickname.height) / 1.5
            text: message
            wrapMode: Text.Wrap
            height: contentHeight
            width: rowLayout.width - icon.width
            Layout.topMargin: senderNickname.contentHeight
        }
    }
}

