import QtQuick 2.15
import QtQuick.Controls 2.15

Column{
    spacing: 2
    CheckBox {
        height: 40
        width: parent.width
        text: "灰色";
        checked: true
        background: Rectangle{
            color: "#6B6B6B"
        }
    }
}
