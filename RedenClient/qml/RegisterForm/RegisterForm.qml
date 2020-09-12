import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

Rectangle
{
    id: root
    //color: Material.backgroundColor
    implicitWidth:  GlobalSettings.loginFormWidth
    implicitHeight: GlobalSettings.loginFormHeight
    visible: true
    FontLoader { id: starsetFont; source: "../fonts/jaapokkisubtract-regular.ttf" }
    Rectangle
    {
        id: background
        z: 0
        color: Material.backgroundColor
        anchors.fill: parent

        Rectangle
        {
            color: Material.color(Material.Red)
            width: 450
            height: 200
            anchors.right: background.right
            anchors.rightMargin: -150
            anchors.top: background.top
            anchors.topMargin: -150
            rotation: 45
        }

        Label {
            id: logo_text
            color: Material.color(Material.Red)
            text: "R E D E N"
            font.family: starsetFont.name
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            font.pointSize: 32
            anchors.topMargin: 65
        }
    }


    ColumnLayout {
        id: fields_layout
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 150
        anchors.bottomMargin: 120

        width: parent.width / 2 + parent.width / 4
        spacing: 2

        TextField
        {
            id: inputLogin
        }
        TextField
        {
            id: inputPassword
        }
        TextField
        {
            id: confirmPassword
        }

        TextField
        {
            id: inputNickname
        }
    }
}
