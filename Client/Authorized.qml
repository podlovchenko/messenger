import QtQuick 2.0

Rectangle
{
    id: authorized
    anchors.fill: parent
    visible: root.authorized ? false : true
    color: "black"

    TextForm
    {
        id: name
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        width: parent.width / 4
        height: parent.height / 16
        placeHolder: "enter your name"
    }

    ButtonUniversal
    {
        id: sendname
        anchors.top: name.bottom
        anchors.topMargin: 20
        anchors.left: name.left
        anchors.right: name.right
        text: "Authorized"
        onClicked:
        {
            // сделать проверку корректности имени: не пустое, не повторяющееся
            if ( extern_client.verification(name.value) === true )
            {
                extern_client.setName(name.value);
                extern_client.sendString(name.value, 1);
                name.value = " ";
                name.focus = false;
                root.authorized = true;
            }

        }
    }

}

