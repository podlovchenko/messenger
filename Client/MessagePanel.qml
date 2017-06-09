import QtQuick 2.2
import QtQuick.Dialogs 1.0

Item
{
    id: root
    anchors.fill: parent
    property bool  choose: false
    ButtonUniversal
    {
        id: addFiles
        height: parent.height / 8
        width:  parent.width / 8
        radius: parent.height / 8
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        nonactiveColor: "red"
        visible: root.choose ? false : true
        text: "Send"

        onClicked:
        {
            //extern_client.sendFile("/home/seva/Pictures/qtcreator.png");
            root.choose = true;
        }
    }

    FileDialog
    {
        id: file
        visible: root.choose ? true : false
        title: "Please choose a file"
        folder: shortcuts.home
        width: parent.width
        height: parent.height
        onAccepted:
        {
            extern_client.sendFile(file.fileUrls);
            close();
            root.choose = false;
        }

        onRejected:
        {
            close();
            root.choose = false;
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
            textTitle: 1
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

