#include <QMetaObject>

#include "paint.h"
#include "..\algorithm\convert_color.h"
#include "..\algorithm\rotate_img.h"
#include "..\algorithm\flip_img.h"
#include "..\algorithm\blur_img.h"
#include "..\algorithm\sharpen_img.h"
#include "..\algorithm\binarize.h"
#include "..\algorithm\transfer_grayscale.h"
#include "..\algorithm\equalize_histogram.h"
#include "..\algorithm\filter.h"
#include "..\algorithm\effect.h"

QImage mat2qimage(cv::Mat& mat, Paint* paint){
    qint32 c = mat.channels();
    if(c == 1){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        img = img.scaled(paint->_w, paint->_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else if(c == 3){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        img = img.scaled(paint->_w, paint->_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else if(c == 4){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        img = img.scaled(paint->_w, paint->_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else{
        uchar arr[3][3][3] = {
            {
                {255, 0, 0},
                {0, 255, 0},
                {0, 0, 255}
            },{
                {255, 255, 0},
                {0, 255, 255},
                {255, 0, 255}
            },{
                {128, 128, 0},
                {0, 128, 128},
                {128, 0, 128}
            }
        };

        cv::Mat mat = cv::Mat(3, 3, CV_8SC3, arr);
        QImage img(mat.data, 3, 3, mat.step, QImage::Format_RGB888);
        paint->_w = 3, paint->_h = 3;
        img.bits();
        return img;
    }
}

QImage mat2qimage(cv::Mat& mat, Paint* paint, qint32 w, qint32 h){
    qint32 c = mat.channels();
    if(c == 1){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else if(c == 3){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else if(c == 4){
        QImage img((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        img.bits();
        return img;
    }else{
        uchar arr[3][3][3] = {
            {
                {255, 0, 0},
                {0, 255, 0},
                {0, 0, 255}
            },{
                {255, 255, 0},
                {0, 255, 255},
                {255, 0, 255}
            },{
                {128, 128, 0},
                {0, 128, 128},
                {128, 0, 128}
            }
        };
        cv::Mat mat = cv::Mat(3, 3, CV_8SC3, arr);
        QImage img(mat.data, 3, 3, mat.step, QImage::Format_RGB888);
        paint->_w = 3, paint->_h = 3;
        img.bits();
        return img;
    }
}

//QSGNode* Paint::updatePaintNode(QSGNode* node, UpdatePaintNodeData*){
//    QSGSimpleTextureNode *texture = static_cast<QSGSimpleTextureNode *>(node);
//    if (!texture) {
//        texture = new QSGSimpleTextureNode();
//    }

//    QImage img = mat2qimage(_mat);
//    QSGTexture *sgTexture = window()->createTextureFromImage(img.scaled(boundingRect().size().toSize()));
//    if(sgTexture){
//        QSGTexture *tt = texture->texture();
//        if(tt){
//            tt->deleteLater();
//        }

//        texture->setRect(boundingRect());
//        texture->setTexture(sgTexture);
//    }

//    return texture;
//};

Paint::Paint(QQuickItem* parent){
    setFlag(Flag::ItemHasContents,true);
    qRegisterMetaType<QImage>("QImage&");
    qRegisterMetaType<QVector<QVector<qint32>>>("QVector<QVector<qint32>>&");
}

Paint::~Paint(){
    _mat.release();
    _tmpMat.release();
    qDebug("close");
}

void Paint::paint(QPainter *painter){
    qDebug("--------------------------");
    qDebug("PAINT START");
    if (painter == nullptr){
        return;
    }

    setIsSave(false);
    painter->drawImage(0,0, _img);
    qDebug("PAINT END");
    qDebug("--------------------------");
}

qint32 Paint::colorModel() const{
    return _colorModel;
}

bool Paint::isSave() const{
    return _isSave;
}

void Paint::setColorModel(quint32 colorModel){
    if(_colorModel == colorModel){
        return;
    }

    if(_colorModel == RGB_MODEL){
        _mat = algorithm::rgb2gray(_mat);
    }else{
        _mat = algorithm::gray2rgb(_mat);
    }

    _colorModel = colorModel;
    emit colorModelChanged(_colorModel);
    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
}

void Paint::setIsSave(bool isSave){
    if(_isSave != isSave){
        _isSave = isSave;
        emit isSaveChanged(_isSave);
    }
}

void Paint::generateHistogram(){
    _histogram.clear();
    qint32 w = _mat.cols, h = _mat.rows, c = _mat.channels();
    if(_colorModel == GRAY_MODEL){
        QVector<qint32> gray(256, 0);
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = _mat.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                gray[ptr[j]]++;
            }
        }

        _histogram.push_back(gray);
    }else if(_colorModel == RGB_MODEL){
        QVector<qint32> red(256, 0);
        QVector<qint32> green(256, 0);
        QVector<qint32> blue(256, 0);
        if(c == 3){
            for(qint32 i = 0; i < h; i++){
                cv::Vec3b* ptr = _mat.ptr<cv::Vec3b>(i);
                for(qint32 j = 0; j < w; j++){
                    red[ptr[j][0]]++;
                    green[ptr[j][1]]++;
                    blue[ptr[j][2]]++;
                }
            }
        }else if(c == 4){
            for(qint32 i = 0; i < h; i++){
                cv::Vec4b* ptr = _mat.ptr<cv::Vec4b>(i);
                for(qint32 j = 0; j < w; j++){
                    red[ptr[j][0]]++;
                    green[ptr[j][1]]++;
                    blue[ptr[j][2]]++;
                }
            }
        }

        _histogram.push_back(red);
        _histogram.push_back(green);
        _histogram.push_back(blue);
    }
}

void Paint::open(const QString& src, qint32 sw, qint32 sh){
    qDebug("--------------------------");
    qDebug("SET IMG START");
    _matPath = src;
    cv::Mat mat = cv::imread(_matPath.toStdString(), -1);
    if(mat.empty()){
        uchar arr[3][3][3] = {
            {
                {255, 0, 0},
                {0, 255, 0},
                {0, 0, 255}
            },{
                {255, 255, 0},
                {0, 255, 255},
                {255, 0, 255}
            },{
                {128, 128, 0},
                {0, 128, 128},
                {128, 0, 128}
            }
        };

        mat = cv::Mat(3, 3, CV_8UC3, arr);
    }

    qint32 w = mat.cols, h = mat.rows, c = mat.channels();
    qDebug("w = %d, h = %d, c = %d", w, h, c);
    if(c == 1){
        _colorModel = GRAY_MODEL;
        _mat = mat.clone();
    }else if(c == 3){
        _colorModel = RGB_MODEL;
        cv::cvtColor(mat, _mat, cv::COLOR_BGR2RGB);
    }else if(c == 4){
        _colorModel = RGB_MODEL;
        _mat = mat.clone();
    }

    if(w <= sw && h <= sh){
        _w = w, _h = h;
        this->setSize(QSize(_w, _h));
        this->setImplicitSize(_w, _h);
        //        this->setPosition(QPoint(qint32((sw - _w)/2.0), qint32((sh - _h)/2.0)));
        qDebug("w <= _w && h <= _h");
        qDebug("w = %d h = %d", _w, _h);
        qDebug("x = %d y = %d", qint32((sw - _w)/2.0), qint32((sh - _h)/2.0));
    }else if(sw/float(sh) >= w/float(h)){
        _h = sh, _w = qint32(_h/(float)h*w);
        this->setSize(QSize(_w, _h));
        this->setImplicitSize(_w, _h);
        //        this->setPosition(QPoint(qint32((sw - _w)/2.0), 0));
        qDebug("_w/float(_h) >= w/float(h)");
        qDebug("w = %d h = %d", _w, _h);
        qDebug("x = %d y = %d", qint32((sw - _w)/2.0), 0);
    }else{
        _w = sw, _h = qint32(_w/(float)w*h);
        this->setSize(QSize(_w, _h));
        this->setImplicitSize(_w, _h);
        //        this->setPosition(QPoint(0, qint32((sh - _h)/2.0)));
        qDebug("_w/float(_h) < w/float(h)");
        qDebug("w = %d h = %d", _w, qint32(_w/(float)w*h));
        qDebug("x = %d y = %d", 0, qint32((sh - _h)/2.0));
    }

    emit colorModelChanged(_colorModel);
    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
    qDebug("SET IMG END");
    qDebug("--------------------------");
}

void Paint::save(){
    if(_isSave){
        return;
    }else{
        setIsSave(true);
        cv::imwrite(_matPath.toStdString(), _mat);
    }
}

void Paint::saveAs(const QString& matPath){
    cv::imwrite(matPath.toStdString(), _mat);
}

void Paint::rotateImg(qint32 direction, qint32 sw, qint32 sh){
    qDebug("--------------------------");
    qDebug("ROTATE IMG START");
    std::clock_t start= std::clock();
    //程序结束用时

    if(direction == LEFT){
        _mat = algorithm::rotateLeft(_mat);
    }else{
        _mat = algorithm::rotateRight(_mat);
    }

    _w = _w + _h;
    _h = _w - _h;
    _w = _w - _h;
    this->setSize(QSize(_w, _h));
    this->setImplicitSize(_w, _h);
    //    qint32 x = qint32((sw - _w)/2.0);
    //    qint32 y = qint32((sh - _h)/2.0);
    //    x = x > 0 ? x : 0;
    //    y = y > 0 ? y : 0;
    //    this->setPosition(QPoint(x, y));
    _img = mat2qimage(_mat, this);
    update();
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("--------------------------");
    qDebug("ROTATE IMG END");
}

void Paint::flipImg(qint32 axis){
    qDebug("--------------------------");
    qDebug("FLIP IMG START");
    std::clock_t start=clock();
    if(axis == HORIZONTALLY){
        _mat = algorithm::flipHorizontally(_mat);
    }else{
        _mat = algorithm::flipVertically(_mat);
    }

    _img = mat2qimage(_mat, this);
    update();
    std::clock_t end = clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("--------------------------");
    qDebug("FLIP IMG END");
}

void Paint::zoomImg(qint32 percentage){
    qDebug("--------------------------");
    qDebug("ZOOM IMG START");
    std::clock_t start=std::clock();
    qint32 w = this->_w * (percentage / 100.0);
    qint32 h = this->_h * (percentage / 100.0);
    qDebug("percentage = %d", percentage);
    qDebug("old width = %d old height = %d", this->_w, this->_h);
    qDebug("new width = %d new height = %d", w, h);
    _img = mat2qimage(_mat, this, w, h);
    this->setSize(QSize(w, h));
    this->setImplicitSize(w, h);
    update();
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("ZOOM IMG END");
    qDebug("--------------------------");
}

void Paint::equalizeHistogram(){
    qDebug("--------------------------");
    qDebug("EQUALIZE HISTOGRAM IMG START");
    std::clock_t start = std::clock();
    _mat = algorithm::equlizeHistogram(_mat);
    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("EQUALIZE HISTOGRAM IMG END");
    qDebug("--------------------------");
}

void Paint::blurImg(qint32 blurType){
    qDebug("--------------------------");
    qDebug("BLUR IMG START");
    std::clock_t start = std::clock();
    _blurType = blurType;
    if(blurType == GAUSSIN_FILTER){
        QObject* root = this->parent()->parent()->parent()->parent()->parent();
        QObject* wGaussBlur = root->findChild<QObject*>("wGaussBlur");
        QObject* miniPaint = wGaussBlur->findChild<QObject*>("cMiniPaint");
        QObject* confirmButton = wGaussBlur->findChild<QObject*>("confirmButton");
        QObject* cancelButton = wGaussBlur->findChild<QObject*>("cancelButton");
        connect(this, SIGNAL(sendImg(QImage&)), miniPaint, SLOT(receiveImg(QImage&)));
        connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
        connect(wGaussBlur, SIGNAL(sendParameter(qint32,double)), this, SLOT(receiveParameter(qint32,double)));
        receiveParameter(1, 1.0);
    }else{
        QObject* root = this->parent()->parent()->parent()->parent()->parent();
        QObject* wBlur = root->findChild<QObject*>("wBlur");
        QObject* miniPaint = wBlur->findChild<QObject*>("cMiniPaint");
        QObject* confirmButton = wBlur->findChild<QObject*>("confirmButton");
        QObject* cancelButton = wBlur->findChild<QObject*>("cancelButton");
        connect(this, SIGNAL(sendImg(QImage&)), miniPaint, SLOT(receiveImg(QImage&)));
        connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
        connect(wBlur, SIGNAL(sendRadius(qint32)), this, SLOT(receiveRadius(qint32)));
        receiveRadius(1);
    }

    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("BLUR IMG END");
    qDebug("--------------------------");
}

void Paint::sharpenImg(qint32 sharpenType){
    qDebug("--------------------------");
    qDebug("SHARP IMG START");
    std::clock_t start = std::clock();
    if(sharpenType == GRADS_OPERATOR){
        _mat = algorithm::gradsOperator(_mat);
    }else if(sharpenType == LAPLACE_OPERATOR){
        _mat = algorithm::laplaceOperator(_mat);
    }else if(sharpenType == ROBERTS_OPERATOR){
        _mat = algorithm::robertsOperator(_mat);
    }else if(sharpenType == SOBEL_OPERATOR){
        _mat = algorithm::sobelOperator(_mat);
    }

    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("SHARP IMG END");
    qDebug("--------------------------");
}

void Paint::binarizeImg(qint32 binarizeType){
    qDebug("--------------------------");
    qDebug("BINARIZATION IMG START");
    std::clock_t start = std::clock();
    if(binarizeType == OSTU_THRESH){
        _mat = algorithm::rgb2gray(_mat);
        _mat = algorithm::ostuThresh(_mat);
        _img = mat2qimage(_mat, this);
        _colorModel = GRAY_MODEL;
        update();
        generateHistogram();
        emit sendHistogram(_histogram);
        emit colorModelChanged(_colorModel);
    }else if(binarizeType == FIXED_THRESH){
        QObject* root = this->parent()->parent()->parent()->parent()->parent();
        QObject* wBinarization = root->findChild<QObject*>("wBinarization");
        QObject* paint = wBinarization->findChild<QObject*>("cMiniPaint");
        QObject* confirmButton = wBinarization->findChild<QObject*>("confirmButton");
        QObject* cancelButton = wBinarization->findChild<QObject*>("cancelButton");
        connect(this, SIGNAL(sendImg(QImage&)), paint, SLOT(receiveImg(QImage&)));
        connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
        connect(wBinarization, SIGNAL(sendThresh(qint32)), this, SLOT(receiveThresh(qint32)));
        receiveThresh(128);
    }else if(binarizeType == ADAPTIVE_THRESH){
        QObject* root = this->parent()->parent()->parent()->parent()->parent();
        QObject* wAdapatBinarization = root->findChild<QObject*>("wAdapatBinarization");
        QObject* paint = wAdapatBinarization->findChild<QObject*>("cMiniPaint");
        QObject* confirmButton = wAdapatBinarization->findChild<QObject*>("confirmButton");
        QObject* cancelButton = wAdapatBinarization->findChild<QObject*>("cancelButton");
        connect(this, SIGNAL(sendImg(QImage&)), paint, SLOT(receiveImg(QImage&)));
        connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
        connect(wAdapatBinarization, SIGNAL(sendParameter(qint32, qint32)), this, SLOT(receiveParameter(qint32, qint32)));
        receiveParameter(1, 0);
    }

    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("BINARIZATION IMG END");
    qDebug("--------------------------");
}

void Paint::transferGrayscale(){
    qDebug("--------------------------");
    qDebug("TRANSFER IMG START");
    std::clock_t start = std::clock();
    QObject* root = this->parent()->parent()->parent()->parent()->parent();
    QObject* wTransfer = root->findChild<QObject*>("wTransfer");
    QObject* paint = wTransfer->findChild<QObject*>("cMiniPaint");
    QObject* confirmButton = wTransfer->findChild<QObject*>("confirmButton");
    QObject* cancelButton = wTransfer->findChild<QObject*>("cancelButton");
    connect(this, SIGNAL(sendImg(QImage&)), paint, SLOT(receiveImg(QImage&)));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(wTransfer, SIGNAL(sendParameter(double, qint32)), this, SLOT(receiveParameter(double, qint32)));
    receiveParameter(-1.0, 255);
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("TRANSFER IMG END");
    qDebug("--------------------------");
}

void Paint::filter(qint32 filterType){
    qDebug("--------------------------");
    qDebug("FILTER IMG START");
    std::clock_t start = std::clock();
    if(filterType == INVERT_FILTER){
        _mat = algorithm::invertFilter(_mat);
    }else if(filterType == DECOLORI_FILTER){
        _mat = algorithm::decolorFilter(_mat);
    }else if(filterType == NOSTALGIZ_FILTER){
        _mat = algorithm::nostalgiaFilter(_mat);
    }else if(filterType == CAST_FILTER){
        _mat = algorithm::castFilter(_mat);
    }else if(filterType == FREEZE_FILTER){
        _mat = algorithm::freezeFilter(_mat);
    }else if(filterType == COMIC_STRIP_FILTER){
        _mat = algorithm::comicStripFilter(_mat);
    }else if(filterType == EXPOSURE_FILTER){
        _mat = algorithm::exposureFilter(_mat);
    }

    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";;
    qDebug("FILTER IMG END");
    qDebug("--------------------------");
}

void Paint::effect(qint32 effectType){
    qDebug("--------------------------");
    qDebug("EFFECT IMG START");
    std::clock_t start = std::clock();
    if(effectType == FROSTED_GLASS_EFFECT){
        _mat = algorithm::frostedGlassEffect(_mat);
    }else if(effectType == RELIEF_EFFECT){
        _mat = algorithm::reliefEffect(_mat);
    }else if(effectType == OIL_PAINTING_EFFECT){
        _mat = algorithm::oilPaintingEffect(_mat);
    }else if(effectType == MOSAIC_EFFECT){
        _mat = algorithm::mosaicEffect(_mat);
    }else if(effectType == SKETCH_EFFECT){
        _mat = algorithm::sketchEffect(_mat);
    }else if(effectType == FLEETING_TIME_EFFECT){
        _mat = algorithm::fleetingTimeEffect(_mat);
    }

    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
    std::clock_t end = std::clock();
    double endtime=(double)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"Total time:"<<endtime*1000<<"ms";
    qDebug("EFFECT IMG END");
    qDebug("--------------------------");
}

void Paint::select(){
    emit sendHistogram(_histogram);
    emit colorModelChanged(_colorModel);
}

void Paint::confirm(){
    qDebug("confrim");
    _mat = _tmpMat.clone();
    _tmpMat.release();
    _img = mat2qimage(_mat, this);
    update();
    generateHistogram();
    emit sendHistogram(_histogram);
}

void Paint::cancel(){
    qDebug("cancel");
}

void Paint::receiveRadius(qint32 radius){
    if(_blurType == LINEAR_MEAN_FILTER){
        _tmpMat = algorithm::linearMeanFilter(_mat, radius);
    }else if(_blurType == MAXIUM_FILTER){
        _tmpMat = algorithm::maximumFilter(_mat, radius);
    }else if(_blurType == MEDIAN_FILTER){
        _tmpMat = algorithm::medianFilter(_mat, radius);
    }else if(_blurType == MINIMUM_FILTER){
        _tmpMat = algorithm::minimumFilter(_mat, radius);
    }

    QImage img = mat2qimage(_tmpMat , this);
    emit sendImg(img);
}

void Paint::receiveParameter(qint32 radius, double sigma){
    _tmpMat = algorithm::gaussianFilter(_mat, radius, sigma);
    QImage img = mat2qimage(_tmpMat, this);
    emit sendImg(img);
}

void Paint::receiveThresh(qint32 thresh){
    if(_colorModel == RGB_MODEL){
        _tmpMat = algorithm::rgb2gray(_mat);
    }

    qDebug("_tmpMat.channels() = %d", _tmpMat.channels());
    qDebug("w = %d, h = %d", _tmpMat.cols, _tmpMat.rows);
    cv::Mat tmpImg = algorithm::fixedThresh( _tmpMat, thresh);
    qDebug("w = %d, h = %d", tmpImg.cols, tmpImg.rows);
    QImage img = mat2qimage(_tmpMat, this);
    emit sendImg(img);
}

void Paint::receiveParameter(double a, qint32 b){
    _tmpMat = algorithm::linearGrayTransfer(_mat, a, b);
    QImage img = mat2qimage(_tmpMat, this);
    emit sendImg(img);
}

void Paint::receiveParameter(qint32 radius, qint32 c){
    if(_colorModel == RGB_MODEL){
        _tmpMat = algorithm::rgb2gray(_mat);
    }

    cv::Mat tmpMat = algorithm::adaptiveThresh(_tmpMat, radius, c);
    QImage img = mat2qimage(tmpMat, this);
    emit sendImg(img);
}
