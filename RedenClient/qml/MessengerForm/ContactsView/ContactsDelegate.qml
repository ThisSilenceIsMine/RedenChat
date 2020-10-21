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
    //implicitHeight: rowLayout.height
    height: 50
    signal click()
    color: Material.backgroundColor
    Rectangle
    {
        id: delimiter
        height: 1
        width: rowLayout.width
        color: Qt.lighter(Material.backgroundColor)
        anchors.bottom: rowLayout.top
        anchors.bottomMargin: 10
    }
    RowLayout
    {
        id: rowLayout
        anchors.fill: parent
        RoundImage
        {
            id: avatar
            source: "file:///" + avatarSource
            Layout.preferredWidth: 40
            Layout.preferredHeight: 40
            Layout.leftMargin: 5
            Layout.alignment: Qt.AlignLeft
            Component.onCompleted: {
                console.log("Avatar source = " + avatarSource)
            }
        }
        Label
        {
            id: usernameLabel
            text: username
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

        }
    }
    MouseArea
    {
        id: area
        anchors.fill: parent
        z: 5

    }
    Component.onCompleted: {
        area.clicked.connect(click)
    }
}
