import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1 as Labs
import QtQuick.Dialogs 1.3
import QtCharts 2.15

import Custom.App 1.0
import Custom.Paint 1.0

ApplicationWindow {
    id: root
    visible: true
    visibility: "Maximized"
    width: 640
    height: 480
    title: qsTr("QPhotoEdit")
    property int _paintNums: -1
    property var _paintMap: ({})
    property var _channelMap: ({})
    property int _colorModel: -1
    property int _depth: -1
    property string checkMark: "qrc:/assets/icon/checkMark.png"
    property string empty: "qrc:/assets/icon/empty.png"
    CApp{
        id: cApp
    }
    WBlur{
        id: wBlur
        objectName: "wBlur"
        visible: false
        modality: Qt.WindowModal
    }
    WGaussBlur{
        id: wGaussBlur
        objectName: "wGaussBlur"
        visible: false
        modality: Qt.WindowModal
    }
    WBinarize{
        id: wBinarization
        objectName: "wBinarization"
        visible: false
        modality: Qt.WindowModal
    }
    WAdapatBinarize{
        id: wAdapatBinarization
        objectName: "wAdapatBinarization"
        visible: false
        modality: Qt.WindowModal
    }
    WTransfer{
        id: wTransfer
        objectName: "wTransfer"
        visible: false
        modality: Qt.WindowModal
    }
    header: MenuBar {
        id: menuBar
        width: parent.width
        Menu {
            title: qsTr("文件(F)")
            MenuItem{
                text: qsTr("打开")
                icon.source: "qrc:/assets/icon/open.png"
                icon.color: "transparent"
                onClicked: {
                    open.open()
                }
                Labs.FileDialog{
                    title: qsTr("打开图片")
                    id: open
                    nameFilters: ["image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)", "*.pgm", "*.jpg", "*.bmp","*.pbm", "*.png", "*.ppm", "*.xbm", "*.xpm"]
                    acceptLabel: qsTr("确定")
                    rejectLabel: qsTr("取消")
                    fileMode: Labs.FileDialog.OpenFile
                    onAccepted: {
                        const file = open.files[0].replace("file:///", "")
                        const fileSplit = file.split("/");
                        const fileLength = fileSplit.length;
                        const fileName = fileSplit[fileLength - 1];
                        const tabItem = tabButton.createObject(tabBar, {text: fileName})
                        const paintItem = paintView.createObject(paintStack)
                        tabBar.addItem(tabItem)
                        _paintMap[tabItem] = paintItem
                        _paintNums++
                        tabBar.setCurrentIndex(_paintNums)
                        paintItem.children[0].children[0].children[0].open(file, paintStack.width - 20, paintStack.height - 20);
                    }
                }
            }
            MenuSeparator{ }
            MenuItem{
                text: qsTr("保存")
                enabled: _paintNums !== -1
                icon.source: "qrc:/assets/icon/save.png"
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].save()
                }
            }
            MenuItem{
                text: qsTr("另存为")
                enabled: _paintNums !== -1
                icon.source: "qrc:/assets/icon/save.png"
                onClicked: {
                    saveAs.open()
                }
                Labs.FileDialog{
                    id: saveAs
                    title: qsTr("另存为")
                    nameFilters: ["image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)", "*.pgm", "*.jpg", "*.bmp","*.pbm", "*.png", "*.ppm", "*.xbm", "*.xpm"]
                    acceptLabel: qsTr("确定")
                    rejectLabel: qsTr("取消")
                    fileMode: Labs.FileDialog.SaveFile
                    onAccepted: {
                        const file = saveAs.files[0].replace("file:///", "")
                        console.debug(file)
                        const i = tabBar.currentIndex
                        paintStack.children[i].children[0].children[0].children[0].saveAs(file)
                    }
                }
            }
        }
        Menu{
            title: qsTr("模式(M)")
            enabled: _paintNums !== -1
            MenuItem{
                text: qsTr("RGB 颜色(R)")
                icon.source: _colorModel === 0 ? checkMark : empty
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].colorModel = 0
                }
            }
            MenuItem{
                text: qsTr("灰度(G)")
                icon.source: _colorModel === 1 ? checkMark : empty
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].colorModel = 1
                }
            }
            MenuSeparator{}
            MenuItem{
                text: qsTr("8位/通道(R)")
                icon.source: "qrc:/assets/icon/checkMark.png"
            }
        }
        Menu{
            title: qsTr("编辑(E)")
            enabled: _paintNums !== -1
            Menu{
                title: qsTr("灰度变换")
                Repeater{
                    model: [qsTr("线性灰度变换"), qsTr("分段线性灰度变换"), qsTr("对数变换"), qsTr("伽玛变换")]
                    delegate: MenuItem{
                        text: modelData
                        onClicked:{
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].transferGrayscale();
                            wTransfer.visible = true
                        }
                    }
                }
            }
            MenuItem{
                text: qsTr("直方图均衡化")
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].equalizeHistogram()
                }
            }
            Menu{
                title: qsTr("模糊")
                Repeater{
                    model: [qsTr("高斯滤波"), qsTr("线性均值滤波"), qsTr("最大值滤波"), qsTr("中值滤波"), qsTr("最小值滤波"), qsTr("双边滤波")]
                    delegate: MenuItem{
                        text: modelData
                        onClicked:{
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].blurImg(index);
                            if(index === 0){
                                wGaussBlur.visible = true
                            }else{
                                wBlur.visible = true
                            }
                        }
                    }
                }
            }
            Menu{
                title: qsTr("锐化")
                Repeater{
                    model: [qsTr("梯度锐化"), qsTr("Laplace算子"), qsTr("Roberts算子"), qsTr("Sobel算子")]
                    delegate: MenuItem{
                        text: modelData
                        onClicked:{
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].sharpenImg(index);
                        }
                    }
                }
            }
            MenuSeparator{ }
            Menu{
                title: qsTr("图像分割")
                Repeater{
                    model: [qsTr("固定阈值分割"), qsTr("最优/OTSU阈值分割"), qsTr("自适应阈值分割")]
                    delegate: MenuItem{
                        text: modelData
                        enabled: _paintNums !== -1
                        onClicked: {
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].binarizeImg(index);
                            if(index === 0){
                                wBinarization.visible = true
                            }else if(index === 2){
                                wAdapatBinarization.visible = true
                            }
                        }
                    }
                }
            }
            MenuSeparator{ }
            Menu{
                title: qsTr("滤镜")
                Repeater{
                    model: [qsTr("反向滤镜"), qsTr("去色滤镜"), qsTr("怀旧滤镜"), qsTr("熔铸滤镜"), qsTr("冰冻滤镜"), qsTr("连环画滤镜"), qsTr("曝光滤镜")]
                    delegate: MenuItem{
                        text: modelData
                        onClicked: {
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].filter(index);
                        }
                    }
                }
            }
            Menu{
                title: qsTr("特效")
                Repeater{
                    model: [qsTr("毛玻璃特效"), qsTr("浮雕特效"), qsTr("油画特效"), qsTr("马赛克特效"), qsTr("素描特效"), qsTr("流年特效")]
                    delegate: MenuItem{
                        text: modelData
                        onClicked: {
                            const i = tabBar.currentIndex
                            paintStack.children[i].children[0].children[0].children[0].effect(index);
                        }
                    }
                }
            }
        }
        Menu {
            title: qsTr("帮助(H)")
            MessageDialog {
                id: messageDialog
                title: qsTr("关于")
                function show(caption) {
                    messageDialog.text = caption;
                    messageDialog.open();
                }
            }
            MenuItem{
                text: qsTr("关于")
                icon.source: "qrc:/assets/icon/about.png"
                icon.color: "transparent"
                onClicked: messageDialog.visible = true
            }
            MenuItem{
                text: qsTr("网站")
                icon.source: "qrc:/assets/icon/website.png"
                icon.color: "transparent"
                onClicked: Qt.openUrlExternally("http://www.baidu.com")
            }
        }
    }
    ToolBar {
        id: toolBar
        z: 1
        width: parent.width
        background: Rectangle{
            color: "#4A4A4A"
        }
        enabled: _paintNums !== -1
        Row{
            anchors.fill: parent
            ToolButton{
                icon.source: "qrc:/assets/icon/rotateLeft.png"
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].rotateImg(0, paintStack.width, paintStack.height)
                }
            }
            ToolButton{
                icon.source: "qrc:/assets/icon/rotateRight.png"
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].rotateImg(1, paintStack.width, paintStack.height)
                }
            }
            ToolButton{
                icon.source: "qrc:/assets/icon/flipHorizontally.png"
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].flipImg(0)
                }
            }
            ToolButton{
                icon.source: "qrc:/assets/icon/flipVertically.png"
                onClicked: {
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].flipImg(1)
                }
            }
            ToolButton{
                icon.source: "qrc:/assets/icon/clipboard.png"
                onClicked: {

                }
            }
            SpinBox{
                from: 10
                value: 100
                to: 200
                stepSize: 10
                onValueChanged: function(){
                    const i = tabBar.currentIndex
                    paintStack.children[i].children[0].children[0].children[0].zoomImg(value)
                }
            }
        }
    }
    Row{
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        ToolBar{
            id: toolBox
            width: implicitContentWidth
            height: parent.height
            background: Rectangle{
                color: "#535353"
            }
            Grid{
                rows: 2
                columns: 2
                ToolButton{
                    width: 32
                    height: 32
                    icon.source: "qrc:/assets/icon/pencil.png"
                    onClicked: {
                        const i = tabBar.currentIndex
                        paintStack.children[i].children[0].children[0].children[0].flipImg(1)
                    }
                }
                ToolButton{
                    width: 32
                    height: 32
                    icon.source: "qrc:/assets/icon/platte.png"
                    onClicked: {
                        platte.open()
                    }
                    ColorDialog{
                        id: platte
                    }
                }
            }

        }
        Rectangle{
            width: parent.width - toolBox.width - 400
            height: parent.height
            color: "#282828"
            TabBar {
                id: tabBar
                width: parent.width
                clip: true
            }
            Component{
                id: tabButton
                TabButton {
                    id: tabBtn
                    width: 200
                    rightPadding : 30
                    RoundButton{
                        x: 175
                        anchors.verticalCenter: parent.verticalCenter
                        width: 20
                        height: 20
                        Image{
                            anchors.fill: parent
                            source: "qrc:/assets/icon/close.png"
                        }
                        onClicked: {
                            _paintNums--
                            _paintMap[this.parent].destroy()
                            delete _paintMap[this.parent]
                            channelLoader.setSource("")
                            this.parent.destroy()
                            if(_paintNums === -1){
                                _colorModel = -1
                                grayChannel.clear();
                                redChannel.clear()
                                greenChannel.clear()
                                blueChannel.clear()
                                histogramPlot.series(0).axisY.max = 255
                                histogramPlot.series(0).axisX.max = 255
                            }
                        }
                    }
                    onClicked: {
                        const index = tabBar.currentIndex
                        paintStack.children[index].children[0].children[0].children[0].select()
                    }
                }
            }
            StackLayout {
                id: paintStack
                anchors.top: tabBar.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                currentIndex: tabBar.currentIndex
            }
            Component{
                id: paintView
                ScrollView{
                    id: scrollView
                    width: parent.width
                    height: parent.height
                    clip: true
//                    ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
//                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    contentWidth: parent.width > cPaint.width ? parent.width : cPaint.width + 20
                    contentHeight: parent.height > cPaint.height ? parent.height : cPaint.height + 20
                    CPaint{
                        id: cPaint
                        z: 1
                        anchors.centerIn: parent
                        onColorModelChanged: function(colorModel){
                            _colorModel = colorModel
                            if(_colorModel === 0){
                                console.debug("rgb")
                                console.debug(tabBar.currentIndex)
                                channelLoader.setSource("qrc:/view/channel/RgbChannel.qml")
                            }else{
                                console.debug("gray")
                                console.debug(tabBar.currentIndex)
                                channelLoader.setSource("qrc:/view/channel/GrayChannel.qml")
                            }
                        }
                        onSendHistogram: function(hp){
                            grayChannel.clear();
                            redChannel.clear()
                            greenChannel.clear()
                            blueChannel.clear()
                            let h = 255;
                            if(hp.length === 1){
                                for(let i = 0; i < hp[0].length; i++){
                                    grayChannel.append(i, hp[0][i])
                                    h = Math.max(h, hp[0][i])
                                }
                            }else if(hp.length === 3){
                                for(let i = 0; i < hp[0].length; i++){
                                    redChannel.append(i, hp[0][i]);
                                    greenChannel.append(i, hp[1][i])
                                    blueChannel.append(i, hp[2][i])
                                    h = Math.max(h, hp[0][i], hp[1][i], hp[2][i])
                                }
                            }

                            histogramPlot.series(0).axisY.max = h + 255
                        }
                    }
                    Rectangle{
                        id: transparentBackground
                        x: cPaint.x
                        y: cPaint.y
                        width: cPaint.width
                        height: cPaint.height
                        clip: true
                        color: "#55FFFFFF"
                    }
                }
            }
        }
        Rectangle{
            width: 400
            height: parent.height
            color: "#535353"
            TabBar{
                id: miniTab1
                width: parent.width
                background: Rectangle{
                    color:"#6B6B6B"
                }
                TabButton{
                    width: implicitWidth
                    text: qsTr("图层")
                }
                TabButton{
                    width: implicitWidth
                    text: qsTr("属性")
                }
            }
            StackLayout{
                currentIndex: miniTab1.currentIndex
                id: miniStack1
                width: parent.width
                height: 360
                anchors.top: miniTab1.bottom
                Item {
                    Loader{
                        id: channelLoader
                        anchors.topMargin: 2
                        anchors.fill: parent
                    }
                }
                Item{
                    GridLayout{
                        y: 20
                        rows: 2
                        columns: 4
                        rowSpacing: 20
                        columnSpacing: 20
                        width: parent.width
                        Label{
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("宽度")
                        }
                        Rectangle{
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 30
                            radius: 4
                            Text {
                                x: 4
                                id: width
                                height: parent.height
                                text: "深度"
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Label{
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("高度")
                        }
                        Rectangle{
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 30
                            radius: 4
                            Text {
                                x: 4
                                id: height
                                height: parent.height
                                text: "深度"
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                        Label{
                            Layout.alignment: Qt.AlignRight
                            text: qsTr("深度")
                        }
                        Rectangle{
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 30
                            radius: 4
                            Text {
                                x: 4
                                id: depth
                                height: parent.height
                                text: "0"
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }
            TabBar{
                id: miniTab2
                anchors.top: miniStack1.bottom
                width: parent.width
                background: Rectangle{
                    color:"#6B6B6B"
                }
                TabButton{
                    width: implicitWidth
                    text: qsTr("直方图")
                }
            }
            StackLayout{
                id: miniStack2
                currentIndex: miniTab2.currentIndex
                anchors.top: miniTab2.bottom
                anchors.bottom: parent.bottom
                width: parent.width
                Item{
                    ChartView{
                        id: histogramPlot
                        anchors.fill: parent
                        backgroundRoundness: 0
                        backgroundColor: "#535353"
                        theme: ChartView.ChartThemeDark
                        Component.onCompleted: {
                            this.series(0).axisY.max = 255
                            this.series(0).axisX.max = 255
                        }
                        LineSeries{
                            id: redChannel;
                            color: "#FF0000"
                        }
                        LineSeries{
                            id: greenChannel;
                            color: "#00FF00"
                        }
                        LineSeries{
                            id: blueChannel;
                            color: "#0000FF"
                        }
                        LineSeries{
                            id: grayChannel;
                            color: "#000000"
                        }
                    }
                }
            }
        }
    }
}
