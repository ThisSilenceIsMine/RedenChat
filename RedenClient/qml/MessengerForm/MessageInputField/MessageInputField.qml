import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0

Rectangle
{
    id: root
    color:  Material.backgroundColor
    height: textArea.contentHeight + 25

    Flickable
    {
        id: scrollView
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        TextArea.flickable: TextArea
        {
            id: textArea
            selectionColor: Material.color(Material.LightBlue)
            selectedTextColor: "white"
            wrapMode: Text.WordWrap
            background: Rectangle {
                color: Qt.darker(Material.backgroundColor)
                border.color: Material.backgroundColor
            }
        }

    }
}
