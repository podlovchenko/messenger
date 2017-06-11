import QtQuick 2.0
import QtQuick.Controls 1.4

Item
{
    id: root


    ScrollView
    {
        anchors.fill: parent
        ListView
        {
            id: listView1
            anchors.fill: parent
            spacing: 5
            delegate: Item
            {
                id: message
                property string color
                height: oneMessage.contentHeight + 20
                width: parent.width / 2
                Component.onCompleted:
                {
                    if ( whoSender == true )
                    {
                         anchors.right = parent.right
                         message.color = "lightgreen"
                    }
                    else
                    {
                        anchors.left = parent.left
                        message.color = "white"
                    }
                }

                Rectangle
                {
                    id: messageText
                    anchors.fill: parent
                    color: message.color
                    border.width: 2
                    Text
                    {
                        id: oneMessage
                        anchors.fill: parent
                        anchors.topMargin: 10
                        anchors.bottomMargin: 10
                        anchors.leftMargin: 5
                        text: idshnik
                        font.pixelSize: 18
                        wrapMode : Text.Wrap
                    }
                }


            }

            onCountChanged:
            {
               var newIndex = count - 1 // last index
               positionViewAtEnd()
               currentIndex = newIndex
            }

            model: ListModel
            {
                id: listModel
            }
        }
    }
    Connections
    {
        target: extern_client
        onMessageRecieve:
        {
            listModel.append(
                        {
                            idshnik: message, // сообщение
                            whoSender: flag   // от кого? от себя же или от собеседника
                        }
                            )
        }

        onClearChat:
        {
            listModel.clear();
        }
    }
}

