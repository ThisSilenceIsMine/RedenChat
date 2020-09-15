import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import LoginForm 1.0
import RegisterForm 1.0
ApplicationWindow {
    id:root
    //Material.theme: Material.Dark
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

        pushEnter: Transition {
            id: pushEnter

        }
        popEnter: Transition {
            id: popEnter

        }

        pushExit: Transition {
            id: pushExit

        }
        popExit: Transition {
            id: popExit
        }

        RegisterForm
        {
            id: registerForm
            onRegisterNew: {
                stackView.pop()
            }
            onBack: {
                stackView.pop()
            }
        }
        Login{
            id: loginForm
            onGotoRegister: {
                stackView.push(registerForm)
            }
        }
    }

}

