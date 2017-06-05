import QtQuick 2.0

Rectangle
{
    id: root
    width:  150
    height: 480
    color: "#FFA07A"

    // ListView для представления данных в виде списка
    ListView
    {
        id: listView1
        // Размещаем его в оставшейся части окна приложения
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        delegate: Rectangle
        {
            id: message
            anchors.left: parent.left
            height: 60
            width: 60
            radius: 60
            // сюда загрузить аватарку

            ButtonUniversal
            {
                id: writeHim
                text: name
                anchors.left: parent.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: parent.height / 4
                height: 20
                onClicked:
                {
                    extern_client.setInterlocutor(name); // имя собеседника
                    extern_client.sendString(name,2);                 
                    nonactiveColor = "red"
                }
            }

            Connections
            {
                target: extern_client

                onCurrentInterlocutor:
                {
                    if ( name == interlocutor ) // текущий собеседник
                    {
                        writeHim.nonactiveColor = "green";
                    }
                }
            }
        }

        model: ListModel
        {
            id: listModel
        }
    }

    Connections
    {
        target: extern_client

        onNewClientConnected:
        {
            listModel.append({ name: client }) // новый собеседник
        }

        onClientDisconnected:
        {
            listModel.remove(client);   // собеседник вышел

        }
    }
}

