import QtQuick 2.15
import QtQuick.Controls 2.15

Column{
    spacing: 2
    property int r: 1
    property int g: 1
    property int b: 1
    CheckBox {
        height: 40
        width: parent.width
        text: "R";
        checked: parent.r === 1
        background: Rectangle{
            color: "#6B6B6B"
        }
    }
    CheckBox {
        height: 40
        width: parent.width
        text: "G";
        checked: parent.g === 1
        background: Rectangle{
            color: "#6B6B6B"
        }
    }
    CheckBox {
        height: 40
        width: parent.width
        text: "B";
        checked: parent.b === 1
        background: Rectangle{
            color: "#6B6B6B"
        }
    }
}
