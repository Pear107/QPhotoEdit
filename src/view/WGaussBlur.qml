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
    title: "模糊"
    onVisibleChanged: {
        if(!root.visible){
            radiusLabel.text = qsTr("半径 ") + 1
            sigmaLabel.text = qsTr("σ ") + 1
            radiusSlider.value = 1
            sigmaSlider.value = 100
            timer.stop()
        }
    }
    signal sendParameter(int value, double value);
    Timer{
        id: timer
        interval: 2000
        repeat: false
        onTriggered: function(){
            console.debug("send value")
            const a = radiusSlider.value;
            const b = Math.floor(sigmaSlider.value / 100 * 100) / 100;
            console.debug(a, b)
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
                id: sigmaLabel
                text: qsTr("σ ") + 1
                Layout.alignment: Qt.AlignHCenter
            }
            Slider{
                id: radiusSlider
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
                id: sigmaSlider
                stepSize: 1;
                from: 1
                to: 2000
                value: 100
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    const b = Math.floor(sigmaSlider.value / 100 * 100) / 100;
                    sigmaLabel.text = qsTr("σ ") + b
                    timer.start()
                }
            }
            Button{
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
