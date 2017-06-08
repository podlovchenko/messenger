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
        textTitle: 0
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
            if ( extern_client.verification(name.value) === true )
            {
                extern_client.setName(name.value);
                root.title = name.value;
                extern_client.sendString(name.value, 1);
                name.value = " ";
                name.focus = false;
                root.authorized = true;
            }
            else
                name.placeHolder = "Sorry, uncorrect name";

        }
    }

}

