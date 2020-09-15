import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0
import MessengerForm.MessageInputField 1.0

Rectangle
{
    id: root
    height: GlobalSettings.defaultFormHeight
    width: GlobalSettings.defaultFormWidth
    SplitView {
        id: splitView
        anchors.fill: parent

        handle: Rectangle {
            implicitWidth: 3
            implicitHeight: 4
            color: SplitHandle.pressed ? Material.color(Material.Grey)//"#81e889"
                                       : (SplitHandle.hovered ?
                                              Qt.lighter(Material.color(Material.Grey), 1.1)
                                                :        "555555")
        }
        Rectangle {
            id: contactsField
            implicitWidth: 300
            color: Material.backgroundColor
        }
        Rectangle {
            id: chatField
            implicitWidth: 50
            color: Qt.lighter(Material.backgroundColor)
            MessageInputField
            {
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                anchors.bottomMargin: 10
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }
}
