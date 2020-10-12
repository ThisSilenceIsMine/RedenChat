import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import GlobalQmlSettings 1.0
import Authentication.LoginForm 1.0
import Authentication.RegisterForm 1.0
import MessengerForm 1.0

ApplicationWindow {
    id:root
    property int bw: 5
    background: Rectangle {
        anchors.fill: parent
        color: Material.backgroundColor
    }

//    flags: Qt.Window | Qt.FramelessWindowHint
//    function toggleMaximized() {
//        if (root.visibility === Window.Maximized) {
//            root.showNormal();
//        } else {
//            root.showMaximized();
//        }
//    }
//    MouseArea {
//        anchors.fill: parent
//        hoverEnabled: true
//        cursorShape: {
//            const p = Qt.point(mouseX, mouseY);
//            const b = bw + 10; // Increase the corner size slightly
//            if (p.x < b && p.y < b) return Qt.SizeFDiagCursor;
//            if (p.x >= width - b && p.y >= height - b) return Qt.SizeFDiagCursor;
//            if (p.x >= width - b && p.y < b) return Qt.SizeBDiagCursor;
//            if (p.x < b && p.y >= height - b) return Qt.SizeBDiagCursor;
//            if (p.x < b || p.x >= width - b) return Qt.SizeHorCursor;
//            if (p.y < b || p.y >= height - b) return Qt.SizeVerCursor;
//        }
//        acceptedButtons: Qt.NoButton // don't handle actual events
//    }
//    DragHandler {
//        id: resizeHandler
//        grabPermissions: TapHandler.TakeOverForbidden
//        target: null
//        onActiveChanged: if (active) {
//                             const p = resizeHandler.centroid.position;
//                             const b = bw + 10; // Increase the corner size slightly
//                             var e = 0;
//                             if (p.x < b) { e |= Qt.LeftEdge }
//                             if (p.x >= width - b) { e |= Qt.RightEdge }
//                             if (p.y < b) { e |= Qt.TopEdge }
//                             if (p.y >= height - b) { e |= Qt.BottomEdge }
//                             root.startSystemResize(e);

//                         }
//    }

//    Rectangle
//    {
//        anchors.top: parent.top
//        width: root.width
//        color: Qt.darker(Material.backgroundColor)
//        RowLayout
//        {
//            spacing: 0
//            Item {
//                Layout.fillWidth: true
//            }
//            ToolButton {
//                Layout.alignment: Qt.AlignRight
//                Layout.preferredHeight: 10
//                Layout.preferredWidth: 10
//                contentItem: Image
//                {
//                    source: "qrc:/qml/icons/minimize-white"
//                }

//                onClicked: root.showMinimized();

//            }
//            ToolButton {
//                Layout.alignment: Qt.AlignRight
//                Layout.preferredHeight: 10
//                Layout.preferredWidth: 10
//                contentItem: Image
//                {
//                    source: root.visibility === Window.Maximized ? "qrc:/qml/icons/fullscreen-white" : "qrc:/qml/icons/fullscreen_exit-white"
//                }
//                onClicked: root.toggleMaximized()
//            }
//            ToolButton {
//                Layout.alignment: Qt.AlignRight
//                Layout.preferredHeight: 10
//                Layout.preferredWidth: 10
//                contentItem: Image
//                {
//                    source: "qrc:/qml/icons/close-white"
//                }
//                onClicked: root.close()
//            }

//        }
//    }


    width: GlobalSettings.defaultFormWidth
    height: GlobalSettings.defaultFormHeight
    visible: true
    title: qsTr("Reden")

    StackView
    {
        id: stackView
        anchors.fill: parent
        initialItem: loginFormStackComponent
        property real offset: 10
        Component
        {
            id: mainFormStackComponent
            MessengerForm
            {
                id: mainForm
            }
        }
        Component
        {
            id: registerFormStackComponent
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
        }
        Component
        {
            id: loginFormStackComponent
            Login
            {
                id: loginForm
                onGotoRegister: {
                    stackView.push(registerFormStackComponent)
                }
                onAuth: {
                    if(stackView.depth > 1)
                        stackView.pop()
                    stackView.push(mainFormStackComponent)
                }
            }
        }
    }


}

