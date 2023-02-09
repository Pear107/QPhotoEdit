import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import Custom.MiniPaint 1.0

Window{
    id: root
    width: 640
    height: 480
    color: "#535353"
    title: qsTr("二值化")
    onVisibleChanged: {
        if(root.visible){
            radiusLabel.text = qsTr("a ") + 1
            cLabel.text = qsTr("b ") + 0
            radiusSlider.value = 1
            cSlider.value = 0
            timer.stop()
        }
    }
    signal sendParameter(int value, int value);
    Timer{
        id: timer
        interval: 2000
        repeat: false
        onTriggered: function(){
            console.debug("send value")
            const a = radiusSlider.value
            const b = cSlider.value;
            console.debug(a)
            root.sendParameter(a, b)
        }
    }
    RowLayout{
        width: 640
        height: 480
        Rectangle{
            Layout.preferredWidth: 490
            Layout.fillHeight: true
            clip: true
            color: "#535353"
            CMiniPaint{
                objectName: "cMiniPaint"
                anchors.centerIn: parent
            }
        }
        GridLayout{
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            columns: 2
            rows: 3
            Label{
                id: radiusLabel
                text: qsTr("半径 ") + 1
                Layout.alignment: Qt.AlignHCenter
            }
            Label{
                id: cLabel
                text: qsTr("c ") + 0
                Layout.alignment: Qt.AlignHCenter
            }
            Slider{
                id: radiusSlider
                objectName: "radius"
                stepSize: 1;
                from: 1
                to: 100
                value: 1
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    radiusLabel.text = qsTr("半径 ") + radiusSlider.value
                    timer.start()
                }
            }
            Slider{
                id: cSlider
                objectName: "bSlider"
                stepSize: 1;
                from: 0
                to: 255
                value: 255
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    cLabel.text = qsTr("b ") + cSlider.value
                    timer.start()
                }
            }
            Button{
                id: test
                objectName: "confirmButton"
                text: qsTr("确认")
                Layout.alignment: Qt.AlignHCenter
                onClicked: function(){
                    root.visible = false
                }
            }
            Button{
                objectName: "cancelButton"
                text: qsTr("取消")
                Layout.alignment: Qt.AlignHCenter
                onClicked: function(){
                    root.visible = false
                }
            }
        }
    }
}
