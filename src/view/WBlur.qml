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
        if(root.visible){
            radiusLabel.text = qsTr("半径 ") + 1
            radiusSlider.value = 1
            timer.stop()
        }
    }
    signal sendRadius(int value);
    Timer{
        id: timer
        interval: 2000
        repeat: false
        onTriggered: function(){
            console.debug("send value")
            root.sendRadius(radiusSlider.value)
        }
    }
    RowLayout{
        width: 640
        height: 480
        Rectangle{
            Layout.preferredWidth: 540
            Layout.fillHeight: true
            clip: true
            color: "#535353"
            CMiniPaint{
                objectName: "cMiniPaint"
                anchors.centerIn: parent
            }
        }
        ColumnLayout{
            Layout.preferredWidth: 100
            Layout.fillHeight: true
            Label{
                id: radiusLabel
                text: qsTr("半径 ") + 1
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
