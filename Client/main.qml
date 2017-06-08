import QtQuick 2.7
import QtQuick.Controls 2.1

ApplicationWindow
{
    id: root
    visible: true
    width: 640
    height: 480
    color: "black"
    title: "telegram v. 2.0"
    property bool  authorized: false

    Authorized
    {
        id: auth
        anchors.fill: parent
        visible: root.authorized ? false : true
    }

    Item
    {
        anchors.fill: parent
        visible: root.authorized ? true : false

        Interlocutor
        {
            id:chooseInterlocutor
            width:  150
            height: parent.height
        }

        Rectangle
        {
            id: workPlace
            anchors.left: chooseInterlocutor.right
            anchors.right: parent.right
            height: parent.height
            color: "lightblue"

            Chat
            {
                id: historyOfMessage
                anchors
                {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                }

                height: parent.height * 6 / 8

            }

            MessagePanel
            {
                id: bottomPanel
                anchors.fill: parent
            }
        }
    }

    Connections
    {
        target: extern_client

        onEnd:
        {
            Qt.quit();
        }

    }

}

