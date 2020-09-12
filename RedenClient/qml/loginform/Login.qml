import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import ErrorString 1.0
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
            id: login_input
            property var accent: Material.color(Material.Teal)
            text: "login@mail.ru"
            Layout.minimumHeight: 40
            Layout.minimumWidth: 150
            Layout.fillHeight: false
            Layout.fillWidth: false
            //            anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignHCenter
            Material.accent: accent
            width: 150
            ErrorString
            {
                id: loginErrorString
                anchors.top: login_input.bottom
                visible: false
                text: qsTr("Логин обязателен")
            }
            //            Row
            //            {
            //                id: loginErrorString
            //                anchors.top: login_input.bottom
            //                visible: false
            //                spacing: 7
            //                Image
            //                {
            //                    source: "../icons/warning-red.svg"
            //                }

            //                Label
            //                {
            //                    text: qsTr("Логин обязателен")
            //                    color: Material.color(Material.Red)
            //                }
            //            }
            //            onTextChanged: {
            //                loginErrorString.visible = false
            //                login_input.accent = Material.color(Material.Teal)
            //            }
            //        }

        }
        TextField
        {
            id: password_input
            property var accent: Material.color(Material.Teal)
            //anchors.horizontalCenter: parent.horizontalCenter
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("password line")
            Layout.minimumHeight: 40
            Layout.minimumWidth: 150
            echoMode: show_password_checkbox.checked ? TextInput.Normal : TextInput.Password
            width: 150
            Material.accent: accent

            CheckBox
            {
                id: show_password_checkbox
                anchors.top: password_input.top
                anchors.left: password_input.right
                anchors.topMargin: 10
                //text: qsTr("Показывать пароль")
                Material.accent: Material.color(Material.DeepOrange)

                indicator: Image {
                    id: checkBoxImage
                    source: show_password_checkbox.checked ? "../icons/visibility-white.svg" : "../icons/visibility_off-white.svg"
                }

            }

            Row
            {
                id: pwErrorString
                anchors.top: password_input.bottom
                visible: false
                spacing: 7
                Image
                {
                    source: "../icons/warning-red.svg"
                }

                Label
                {
                    text: qsTr("Пароль обязателен")
                    color: Material.color(Material.Red)
                }
            }
            onTextChanged: {
                pwErrorString.visible = false
                password_input.accent = Material.color(Material.Teal)
            }
        }

        ColumnLayout
        {
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignHCenter

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
                    {
                        login_input.accent = Material.color(Material.Red)
                        loginErrorString.visible = true
                    }
                    if(password_input.text == "")
                    {
                        password_input.accent = Material.color(Material.Red)
                        pwErrorString.visible = true
                    }
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
