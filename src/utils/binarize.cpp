#include "binarize.h"

cv::Mat utils::fixedThresh(cv::Mat& src, qint32 thresh){
    qDebug("--------------------------");
    qDebug("FIXED THRESH START");
    qint32 w = src.cols, h = src.rows;
    cv::Mat dst(h, w, CV_8UC1, cv::Scalar::all(0));
    for(qint32 i = 0; i < h; i++){
        uchar *p = src.ptr<uchar>(i);
        uchar *q = dst.ptr<uchar>(i);
        for(qint32 j = 0; j < w; j++){
            if(p[j] >= thresh){
                q[j] = 255;
            }else{
                q[j] = 0;
            }
        }
    }

    qDebug("FIXED THRESH END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat utils::ostuThresh(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    double size = static_cast<double>(w * h);
    cv::Mat dst(h, w, CV_8UC1, cv::Scalar::all(0));
    QVector<double> x(256, 0.0);
    // 直方图
    for(qint32 i = 0; i < h; i++){
        uchar *ptr = src.ptr<uchar>(i);
        for(qint32 j = 0; j < w; j++){
            x[ptr[j]]++;
        }
    }

    QVector<double> y(256, 0.0);
    QVector<double> z(256, 0.0);
    double u = 0.0, v = 0.0;
    y[0] = x[0] / size;
    u = 0 * x[0], v = x[0];
    for(qint32 i = 1; i < 256; i++){
        u += static_cast<double>(i) * x[i];
        v += x[i];
        // 直方图归一化
        y[i] = y[i - 1] + static_cast<double>(x[i]) / size;
        // 平均灰度
        z[i] = u / v;
    }

    qint32 thresh = 0.0;
    // 类间方差（哪个灰度的 sigma 最大，哪个灰度就是需要的阈值 thresh）
    double sigma = 0.0;
    for(qint32 i = 0; i < 256; i++){
        // p1 + p2 = 1
        // sigma^2 = p1(x1 - x)^2 + p2(x2 - x)^2 = p1p2(x1 - x2)^2
        double p = y[i] * (1 - y[i]);
        // 整体平均灰度等于前后两部分平均灰度分别乘以占比再相加
        double q = z[i] - (z[255] - y[i] * z[i]) / (1 - y[i]);
        double s = p * q * q;
        if(s > sigma){
            sigma = s;
            thresh = i;
        }
    }

    for(qint32 i = 0; i < h; i++){
        uchar* ptr = src.ptr<uchar>(i);
        uchar* qtr = dst.ptr<uchar>(i);
        for(qint32 j = 0; j < w; j++){
            if(ptr[j] > thresh){
                qtr[j] = 255;
            }else{
                qtr[j] = 0;
            }
        }
    }

    return dst;
}

cv::Mat utils::adaptiveThresh(cv::Mat& src, qint32 radius, qint32 c){
    qint32 w = src.cols, h = src.rows;
    double size = w * h;
    cv::Mat dst(h, w, CV_8UC1, cv::Scalar::all(0));
    cv::Mat window(1, size, CV_64F, cv::Scalar::all(0));
    double* f = window.ptr<double>(0);
    double sum = 0.0;
    double sigma = 0.3*((2.0 * static_cast<double>(radius) -1.0)*0.5-1.0)+0.8;
    for(qint32 i = 0; i < size; i++){
        double g = std::exp(-static_cast<double>(std::pow(i - radius, 2) / (2.0 * sigma * sigma)));
        f[i] = g;
        sum += g;
    }

    window = window / sum;
    for(qint32 i = 0; i < h; i++){
        uchar *ptr = src.ptr<uchar>(i);
        uchar *qtr = dst.ptr<uchar>(i);
        for(qint32 j = 0; j < w; j++){
            double t = 0;
            for(qint32 k = j - radius; k <= j + radius; k++ ){
                if(k > - 1 && k < w){
                    t += static_cast<double>(ptr[k]) * f[k - j + radius];
                }
            }

            qtr[j] = static_cast<double>(t);
        }
    }

    cv::Mat tmpMat = dst.clone();
    for(qint32 j = 0; j < w; j++){
        for(qint32 i = 0; i < h; i++){
            double t = 0;
            for(qint32 k = i - radius; k <= i + radius; k++ ){
                if(k > - 1 && k < h){
                    t += static_cast<double>(tmpMat.at<uchar>(k, j)) * f[k - i + radius];
                }
            }

            dst.at<uchar>(i, j) = std::max(0, std::min(qint32(static_cast<qint32>(t) + c), 255));
        }
    }

    for(qint32 i = 0; i < h; i++){
        uchar* ptr = src.ptr<uchar>(i);
        uchar* qtr = dst.ptr<uchar>(i);
        for(qint32 j = 0; j < w; j++){
            if(qtr[j] < ptr[j]){
                qtr[j] = 255;
            }else{
                qtr[j] = 0;
            }
        }
    }

    return dst;
}
