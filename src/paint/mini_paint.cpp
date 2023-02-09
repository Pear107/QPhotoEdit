#include "mini_paint.h"

MiniPaint::MiniPaint(QQuickItem *parent)
    : QQuickPaintedItem(parent){
}

MiniPaint::~MiniPaint(){
    qDebug("destory");
}

void MiniPaint::paint(QPainter *painter){
    qDebug("--------------------------");
    qDebug("PAINT START");
    if (painter == nullptr){
        return;
    }

    painter->drawImage(0,0, _img);
    qDebug("PAINT END");
    qDebug("--------------------------");
}

void MiniPaint::receiveImg(QImage& img){
    qDebug("--------------------------");
    qDebug("RECEIVE IMG START");
    _img = img;
    qDebug(" width = %d, height = %d", _img.width(), _img.height());
    this->setWidth(_img.width());
    this->setHeight(_img.height());
    this->update();
    qDebug("RECEIVE IMG END");
    qDebug("--------------------------");
}
