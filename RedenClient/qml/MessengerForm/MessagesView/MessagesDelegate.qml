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
            RowLayout
            {
                Label
                {
                    id: senderNickname

                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: username
                }
                Label
                {
                    id: timeSpan

                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft
                    text: time
                }
            }
        }
        Label
        {

            id: messageText
            text: message
            wrapMode: Text.WordWrap
            Layout.preferredHeight: contentHeight
            Layout.preferredWidth: rowLayout.width - icon.width
            Layout.topMargin: senderNickname.contentHeight
        }
    }
}

