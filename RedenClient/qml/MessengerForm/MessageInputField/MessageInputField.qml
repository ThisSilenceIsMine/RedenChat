import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import GlobalQmlSettings 1.0

Rectangle
{
    id: root
    color: Qt.lighter(Material.backgroundColor)
    height: textArea.contentHeight + 25
    border.color: Material.backgroundColor
    radius: 8
    RowLayout
    {
        id: rowLayout
        spacing: 5
        anchors.fill: parent
        readonly property int btnSize: 32
        Flickable
        {
            id: scrollView

            Layout.preferredWidth: root.width - rowLayout.btnSize * 2 - rowLayout.spacing * 2
            Layout.fillHeight: true
            flickableDirection: Flickable.VerticalFlick
            TextArea.flickable: TextArea
            {
                property var accent: Material.color(Material.Teal)
                id: textArea
                selectionColor: Material.color(Material.LightBlue)
                selectedTextColor: "white"
                wrapMode: Text.WordWrap
                Material.accent: accent
                //text: "\u2601"
                placeholderText: qsTr("Написать сообщение...")
            }

        }
        Rectangle
        {
            id: emojiBtn

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            Layout.preferredWidth: rowLayout.btnSize
            Layout.preferredHeight: rowLayout.btnSize
            color: Qt.lighter(Material.backgroundColor)

            Image
            {
                id: emojiBtnImage
                width: rowLayout.btnSize
                height: rowLayout.btnSize
                anchors.centerIn: parent
                source: "qrc:/qml/icons/insert_emoticon-white-48dp"

                MouseArea
                {
                    id: emojiBtnArea
                    anchors.fill: parent
                }
            }
        }
        Rectangle
        {
            id: sendBtn

            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            Layout.preferredWidth: rowLayout.btnSize
            Layout.preferredHeight: rowLayout.btnSize
            color: Qt.lighter(Material.backgroundColor)

            Image
            {
                anchors.centerIn: parent
                source: "qrc:/qml/icons/send-white-48dp"
                width: rowLayout.btnSize //parent.width / 2 + parent.width / 4
                height: rowLayout.btnSize //parent.height / 2 + parent.height / 4
                MouseArea
                {
                    id: sendBtnArea
                    anchors.fill: parent
                    hoverEnabled: true
                    onHoveredChanged: {

                    }
                    onClicked: {

                    }
                }

            }
        }
    }
}

