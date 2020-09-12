import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import LoginForm 1.0
Window {
    id:root
    //Material.theme: Material.Dark
    width: GlobalSettings.loginFormWidth
    height: GlobalSettings.loginFormHeight
    visible: true
//    title: qsTr("Hello World")

    Login
    {
        anchors.fill: parent

    }
}
