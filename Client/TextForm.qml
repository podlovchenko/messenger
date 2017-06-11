import QtQuick 2.7
import QtQuick.Controls 2.1

FocusScope
{
    id: focusScope;
    width: 192
    height: 324*0.9

    property alias  fontSize     : textInput.font.pointSize;
    property alias  value        : textInput.text;
    property alias  placeHolder  : typeSomething.text;

    property int textTitle: 1

    signal  send()

    Rectangle
    {
        id: background;
        anchors.fill: parent
        color: "#CEECF5"
        radius: 5
        border
        {
            width: 3;
            color: (focusScope.activeFocus ? "tomato" : "#2E9AFE");
        }
    }

    Flickable
    {
        id: flickable
        anchors.fill: parent
        focus: true

        TextArea.flickable: TextArea
            {
                id: textInput
                focus: true
                font.pointSize: 10;
                wrapMode: TextEdit.Wrap
                selectByMouse: true

                Component.onCompleted:
                {
                        if ( focusScope.textTitle === 0)
                        {
                            textInput.font.bold = true;
                            textInput.verticalAlignment   = TextInput.AlignVCenter;
                            textInput.horizontalAlignment = TextInput.AlignHCenter;
                        }


                }

                Keys.onPressed:
                {
                    if(event.key === 16777220)
                    {
                       focusScope.send();
                    }
                }



            }

        ScrollBar.vertical: ScrollBar
        {
            id : scrollBar
        }
    }

    Text
    {
        id: typeSomething;
        text: "Type something...";
        color: "gray";
        opacity: (value === "" ? 1.0 : 0.0);
        font
        {
            italic: true
            pointSize: fontSize;
        }

        anchors
        {
            left: focusScope.left;
            right: focusScope.right;
            leftMargin: 10;
            rightMargin: 10;
            verticalCenter: focusScope.verticalCenter;
        }


        Behavior on opacity { NumberAnimation { duration: 300; } }
    }

    MouseArea
    {
        visible: ( focusScope.activeFocus === false ) // для разблокировки возможности выделения слова
        anchors.fill: parent
        onClicked:
        {
            textInput.forceActiveFocus(); // устанавливает фокус на элементе
        }
        onCanceled: focusScope.focus = false;

    }

    Text
    {
        id: clear;
        text: "\u2716"                      //"\u2713" "\u2717" крестик
        color: 'steelblue';
        font.pixelSize: 30;
        opacity: (value === "" ? 0.0 : 1.0); // прозрачность [0;1]
        anchors
        {
            right: parent.right;
            bottom: parent.bottom;
        }

        Component.onCompleted:
        {
                if ( focusScope.textTitle === 0)
                {
                    clear.anchors.margins = 0;
                    clear.font.pixelSize= 20;
                }
                else if ( focusScope.textTitle === 1 )
                {
                    clear.anchors.margins = 5;
                    clear.font.pixelSize= 30;
                }
        }

        Behavior on opacity { NumberAnimation { duration: 300; } } // изменение

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                focusScope.value = "";
                focusScope.focus = false;
                if ( focusScope.placeHolder === "Sorry, uncorrect name")
                    focusScope.placeHolder = "enter your name";
            }
        }
    }

}
