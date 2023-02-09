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
    title: qsTr("线性灰度变换")
    onVisibleChanged: {
        if(root.visible){
            aLabel.text = qsTr("a ") + -1
            bLabel.text = qsTr("b ") + 255
            aSlider.value = -100
            bSlider.value = 255
            timer.stop()
        }
    }
    signal sendParameter(double value, int value);
    Timer{
        id: timer
        interval: 2000
        repeat: false
        onTriggered: function(){
            console.debug("send value")
            const a = Math.floor(aSlider.value / 100 * 100) / 100;
            const b = bSlider.value;
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
                id: aLabel
                text: qsTr("a ") + -1
                Layout.alignment: Qt.AlignHCenter
            }
            Label{
                id: bLabel
                text: qsTr("b ") + 255
                Layout.alignment: Qt.AlignHCenter
            }
            Slider{
                id: aSlider
                objectName: "aSlider"
                stepSize: 1;
                from: -2000
                to: 2000
                value: -100
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    const a = Math.floor(aSlider.value / 100 * 100) / 100;
                    aLabel.text = qsTr("a ") + a
                    timer.start()
                }
            }
            Slider{
                id: bSlider
                stepSize: 1;
                from: 0
                to: 255
                value: 255
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    bLabel.text = qsTr("b ") + bSlider.value
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
