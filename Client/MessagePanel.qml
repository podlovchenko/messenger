import QtQuick 2.0

Item
{
    id: bottomPanel
    anchors.fill: parent
    ButtonUniversal
    {
        id: addFiles
        height: parent.height / 8
        width:  parent.width / 8
        radius: parent.height / 8
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        nonactiveColor: "red"

        text: "Send"
        onClicked:
        {
            extern_client.sendString(extern_client.file, 100);
        }
    }

    Rectangle
    {
        id: addMessege
        height: parent.height / 8
        width: parent.width * 5 / 8
        anchors.bottom: parent.bottom
        anchors.left: addFiles.right
        color: "orange"

        TextForm
        {
            id: message
            anchors.fill: parent
            placeHolder: "your mind..."
        }
    }

    ButtonUniversal
    {
        id: sendMessege
        height: parent.height / 14
        width: parent.width / 6
        y: addFiles.y + addFiles.height / 4
        anchors.left: addMessege.right
        anchors.leftMargin: 10

        text: "Send"
        onClicked:
        {
            extern_client.sendString(message.value, 0);
            message.value = " ";
            message.focus = false;
        }
    }
}

