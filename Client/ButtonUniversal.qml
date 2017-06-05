import QtQuick 2.0

Rectangle
{
    id: root
    property alias textfont: hint.font.pixelSize
    property string nonactiveColor: "green" // переменная, содержащая текст, который будет отображаться в кнопке
    property string text: "button" // переменная, содержащая текст, который будет отображаться в кнопке
    width: 100 // ширина
    height: 62 // высота
    color: marea.pressed ?  "orange" : nonactiveColor // зависимость цвета кнопки состояния нажатия MouseArea
    radius: 3
    signal clicked()

    Text
    {
        id: hint
        verticalAlignment: Text.AlignVCenter // выравнивание текста по вертикали внутри поля TEXT
        horizontalAlignment: Text.AlignHCenter // выравнивание текста по горизонтали внутри поля TEXT
        anchors.fill: parent // растягиваем птекстовое поле во всю ширину родительского объекта (т.е. во весь прямоугольник/кнопку)
        text: parent.text
    }
    MouseArea
    {
        id: marea // id для работы с этим полем (как имя объекта в С++)
        anchors.fill: parent // и поле тоже растягиваем на всю кнопку
        onClicked:  root.clicked()
    }
}

