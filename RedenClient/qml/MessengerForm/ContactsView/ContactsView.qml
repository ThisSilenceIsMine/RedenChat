import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import GlobalQmlSettings 1.0

ListView
{
    id: list
    focus: true
    clip: true
    highlightFollowsCurrentItem: false
    spacing: 10
    highlight: delegateHighlight

    Component
    {
        id: delegateHighlight
        Rectangle
        {
            id: highlightImpl
            width: parent.width
            height: 50//contactsDelegate.height + 1
            color: "transparent"
            y: list.currentItem.y
            border.width: 2
            border.color: Material.color(Material.DeepOrange)
            z: 5
            Behavior on y
            {
                PropertyAnimation
                {
                    //easing.type: Easing.bezierCurve
                    duration: 250
                }
            }
        }
    }

    delegate: ContactsDelegate
    {
        id: contactsDelegate
        width: list.width
        //height: 40
        avatarSource: model.avatar
        username: model.nickname
        z: 3
//        MouseArea
//        {
//            anchors.fill: parent
//            //z: 10
//            onClicked: {
//                list.currentIndex = index
//                console.log("selected delegate #" + index)
//            }
//        }
        onClick: {
            list.currentIndex = index
            console.log("selected delegate #" + index)
        }
    }
    Component.onCompleted: console.log("idx = " + list.currentIndex)
    //onCurrentItemChanged: console.log(model.get(list.currentIndex).nickname + ' selected')

}
