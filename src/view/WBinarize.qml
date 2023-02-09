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
    title: "二值化"
    onVisibleChanged: {
        if(!root.visible){
            threshLabel.text = qsTr("阈值 ") + 128
            threshSlider.value = 128
            timer.stop()
        }
    }
    signal sendThresh(int value);
    Timer{
        id: timer
        interval: 2000
        repeat: false
        onTriggered: function(){
            console.debug("send value")
            root.sendThresh(slider.value)
        }
    }
    RowLayout{
        width: 640
        height: 480
        Rectangle{
            Layout.preferredWidth: 540
            Layout.fillHeight: true
            clip: true
            CMiniPaint{
                objectName: "cMiniPaint"
                anchors.centerIn: parent
            }
        }
        ColumnLayout{
            Layout.preferredWidth: 100
            Layout.fillHeight: true
            Label{
                id: threshLabel
                text: qsTr("阈值 ") + 128
                Layout.alignment: Qt.AlignHCenter
            }
            Slider{
                id: threshSlider
                stepSize: 1;
                from: 0
                to: 255
                value: 128
                orientation:Qt.Vertical
                Layout.alignment: Qt.AlignHCenter
                onValueChanged: function(){
                    timer.start()
                    threshLabel.text = qsTr("阈值 ") + threshSlider.value
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
