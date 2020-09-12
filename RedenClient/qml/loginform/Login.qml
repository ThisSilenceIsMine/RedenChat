import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import QtQuick.Layouts 1.12
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
            color: Material.color(Material.DeepOrange)
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
            color: Material.color(Material.DeepOrange)
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
            id: login_input
            property var accent: Material.color(Material.Teal)
            text: "login@mail.ru"
            Layout.minimumHeight: 40
            Layout.minimumWidth: 150
            Layout.fillHeight: false
            Layout.fillWidth: false
            anchors.horizontalCenter: parent.horizontalCenter
            Material.accent: accent
            width: 150
        }

            TextField
            {
                id: password_input
                property var accent: Material.color(Material.Teal)
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("password line")
                Layout.minimumHeight: 40
                Layout.minimumWidth: 150
                echoMode: "Password"
                width: 150
                Material.accent: accent
            }
            CheckBox
            {
                id: show_password_checkbox
                anchors.left: password_input.right
                text: qsTr("Показывать пароль")
            }

        ColumnLayout
        {
            Layout.fillHeight: false
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: 15
            Button
            {
                id: confirm_login
                text: qsTr("Вход")
                Layout.preferredWidth: parent.width
                Material.accent: Material.color(Material.DeepOrange)
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    opacity: enabled ? 1.0 : 0.3
                    color: parent.down ? "#FA8072" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                onClicked: {
                    if(login_input.text == "")
                        login_input.accent = Material.color(Material.Red)
                    if(password_input.text == "")
                        password_input.accent = Material.color(Material.Red)
                }
            }
            Button
            {
                id: start_register
                text: qsTr("Регистрация")
                contentItem: Text {
                    text: parent.text
                    font: parent.font
                    opacity: enabled ? 1.0 : 0.3
                    color: parent.down ? "#FA8072" : "#FFFFFF"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
            }
        }
    }

}
