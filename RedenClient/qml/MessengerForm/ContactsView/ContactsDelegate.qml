import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import MessengerForm.RoundImage 1.0
import GlobalQmlSettings 1.0

Rectangle
{
    id: root
    property string avatarSource
    property string username
    Rectangle
    {
        id: delimiter
        height: 1
        width: rowLayout.width
        color: Qt.lighter(Material.backgroundColor)
        anchors.bottom: rowLayout.top
        anchors.bottomMargin: 20
    }
    RowLayout
    {
        id: rowLayout
        anchors.fill: parent
        RoundImage
        {
            id: avatar
            source: avatarSource
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            Layout.leftMargin: 5
            //Layout.alignment: Qt.AlignLeft
        }
        Label
        {
            id: usernameLabel
            text: username

        }
    }
}
