#ifndef MINI_PAINT_H
#define MINI_PAINT_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QImage>

class MiniPaint:public QQuickPaintedItem
{
    Q_OBJECT

private:
    QImage _img;

public:
    MiniPaint(QQuickItem *parent = 0);
    virtual ~MiniPaint();
    virtual void paint(QPainter *painter);

public slots:
    void receiveImg(QImage&);
};

#endif // MINI_PAINT_H
