import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import Authentication.LoginForm 1.0
import Authentication.RegisterForm 1.0
import MessengerForm 1.0

ApplicationWindow {
    id:root
//    flags: Qt.FramelessWindowHint //Quite complex shit. Implement later
    background: Rectangle {
        anchors.fill: parent
        color: Material.backgroundColor
    }

    width: GlobalSettings.defaultFormWidth
    height: GlobalSettings.defaultFormHeight
    visible: true
    title: qsTr("Reden")

    StackView
    {
        id: stackView
        anchors.fill: parent
        initialItem: loginForm
        property real offset: 10

//        RegisterForm
//        {
//            id: registerForm
//            onRegisterNew: {
//                stackView.pop()
//            }
//            onBack: {
//                stackView.pop()
//            }
//        }
//        Login
//        {
//            id: loginForm
//            onGotoRegister: {
//                stackView.push(registerForm)
//            }
//        }
        MessengerForm
        {
            id: mainForm
        }
    }

}

