import QtQuick 2.0

Item
{
    id: root

    // ListView для представления данных в виде списка
    ListView
    {
        id: listView1      
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        spacing: 5
        delegate: Item
        {
            id: message
            //anchors.left: parent.left
            //anchors.right: parent.right
            height: oneMessage.contentHeight
            width: parent.width / 2
            Component.onCompleted:
            {
                if ( whoSender == true )
                {
                     anchors.right = parent.right
                }
                else
                {
                    anchors.left = parent.left
                }
            }
            Rectangle
            {
                id: a
                anchors.fill: parent
                color: "transparent"
                Text
                {
                    id: oneMessage
                    anchors.fill: parent
                    text: idshnik
                    anchors.topMargin: 15
                    //verticalAlignment:   Text.AlignVCenter
                    //horizontalAlignment: Text.AlignHCenter
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

