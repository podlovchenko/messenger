import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle
{
    id: root
    width:  150
    height: 480
    color: "#F5F5DC"

    ScrollView
    {
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff // visible false!
        anchors.fill: parent
        ListView
        {
            id: listView1
            // Размещаем его в оставшейся части окна приложения
            anchors.fill: parent
            spacing: 10
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
                    anchors.leftMargin: 5
                    anchors.top: parent.top
                    anchors.topMargin: parent.height / 4
                    width: root.width - anchors.leftMargin - message.width - 5
                    height: 20
                    onClicked:
                    {
                        if ( name !==  extern_client.getInterlocutor() )
                        {
                            extern_client.setInterlocutor(name); // имя собеседника
                            extern_client.sendString(name,2);
                            nonactiveColor = "red"
                        }

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

