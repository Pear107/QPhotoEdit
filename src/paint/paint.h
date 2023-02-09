#ifndef PAINT_H
#define PAINT_H

//#include <QQuickItem>
//#include <QQuickWindow>
//#include <QSGSimpleTextureNode>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QQuickView>
#include <QDebug>
#include <opencv2/opencv.hpp>

#define RGB_MODEL 0
#define GRAY_MODEL 1

class Paint : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool colorModel READ colorModel WRITE setColorModel NOTIFY colorModelChanged FINAL)
    Q_PROPERTY(bool isSave READ isSave WRITE setIsSave NOTIFY isSaveChanged FINAL)

private:
    QImage _img;
    QString _matPath;
    cv::Mat _mat;
    cv::Mat _tmpMat;
    qint32 _w;
    qint32 _h;
    qint32 _colorModel;
    bool _isSave;
    QVector<QVector<qint32>> _histogram;
    qint32 _blurType;

//protected:
//    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*) override;

public:
    Paint(QQuickItem *parent = nullptr);
    ~Paint();
    virtual void paint(QPainter *painter);
    friend QImage mat2qimage(cv::Mat&, Paint*);
    friend QImage mat2qimage(cv::Mat&, Paint*, qint32, qint32);
    qint32 colorModel() const;
    bool isSave() const;
    void setColorModel(quint32);
    void setIsSave(bool);
    void generateHistogram();
    Q_INVOKABLE void open(const QString&, qint32, qint32);
    Q_INVOKABLE void save();
    Q_INVOKABLE void saveAs(const QString&);
    Q_INVOKABLE void rotateImg(qint32, qint32, qint32);
    Q_INVOKABLE void flipImg(qint32);
    Q_INVOKABLE void zoomImg(qint32);
    Q_INVOKABLE void equalizeHistogram();
    Q_INVOKABLE void blurImg(qint32);
    Q_INVOKABLE void sharpenImg(qint32);
    Q_INVOKABLE void binarizeImg(qint32);
    Q_INVOKABLE void transferGrayscale();
    Q_INVOKABLE void filter(qint32);
    Q_INVOKABLE void effect(qint32);
    Q_INVOKABLE void select();

public slots:
    void confirm();
    void cancel();
    void receiveRadius(qint32);
    void receiveParameter(qint32, double);
    void receiveThresh(qint32);
    void receiveParameter(double, qint32);
    void receiveParameter(qint32, qint32);

signals:
    void colorModelChanged(qint32);
    void isSaveChanged(bool);
    void sendHistogram(QVector<QVector<qint32>>&);
    void sendImg(QImage&);
};

#endif // PAINT_H
