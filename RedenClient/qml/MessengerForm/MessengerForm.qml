import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0

Rectangle
{
    id: root
    height: GlobalSettings.defaultFormHeight
    width: GlobalSettings.defaultFormWidth
    SplitView {
        id: splitView
        anchors.fill: parent

        handle: Rectangle {
            implicitWidth: 2
            implicitHeight: 4
            color: SplitHandle.pressed ? Material.color(Material.DeepOrange)//"#81e889"
                                       : (SplitHandle.hovered ?
                                              Qt.lighter(Material.color(Material.Orange), 1.1)
                                                :        Material.color(Material.Orange))
        }
        Rectangle {
            implicitWidth: 150
            color: Material.backgroundColor
        }
        Rectangle {
            implicitWidth: 50
            color: Qt.lighter(Material.backgroundColor)
        }
    }
}
