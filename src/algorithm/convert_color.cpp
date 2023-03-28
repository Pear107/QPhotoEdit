#include "convert_color.h"

cv::Mat algorithm::rgb2hsi(cv::Mat& src){
    return src;
}

cv::Mat algorithm::rgb2cmyk(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("RGB CONVERT CMYK START");
    qint32 w = src.cols, h = src.rows;
    cv::Mat dst(h, w, CV_8UC4, cv::Scalar::all(0));
    for(qint32 i = 0; i < h; i++){
        cv::Vec3b* p = src.ptr<cv::Vec3b>(i);
        cv::Vec4b* q = dst.ptr<cv::Vec4b>(i);
        for(qint32 j = 0; j < w; j++){
            uchar cyan = 255 - p[j][0];
            uchar magenta = 255 - p[j][1];
            uchar yellow = 255 - p[j][2];
            uchar black = std::min(cyan, std::min(magenta, yellow));
            if (black == 255){
                q[j] = cv::Vec<uchar, 4>(0, 0, 0, 0);
            }else{
                q[j][0] = (cyan - black)*255.0 / (255 - black);
                q[j][1] = (magenta - black)*255.0 / (255 - black);
                q[j][2] = (yellow - black)*255.0 / (255 - black);
                q[j][3] = black;
            }
        }
    }

    qDebug("RGB CONVERT CMYK END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat algorithm::rgb2gray(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("RGB CONVERT GRAY START");
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC1, cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* p = src.ptr<cv::Vec3b>(i);
            uchar* q = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = (p[j][0] * 28 + p[j][1] * 151 + p[j][2] * 77) >> 8;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* p = src.ptr<cv::Vec4b>(i);
            uchar* q = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = (p[j][0] * 28 + p[j][1] * 151 + p[j][2] * 77) >> 8;
            }
        }
    }

    qDebug("RGB CONVERT GRAY END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat algorithm::hsi2rgb(cv::Mat& src){
    return src;
}

cv::Mat algorithm::hsi2cmyk(cv::Mat& src){
    return src;
}

cv::Mat algorithm::hsi2gray(cv::Mat& src){
    return src;
}

cv::Mat algorithm::cmyk2Rgb(cv::Mat& src){
    qDebug("CMYK CONVERT RGB START");
    qDebug("--------------------------");
    qint32 w = src.cols, h = src.rows;
    cv::Mat dst(h, w, CV_8UC3, cv::Scalar::all(0));
    for(qint32 i = 0; i < h; i++){
        cv::Vec4b* p = src.ptr<cv::Vec4b>(i);
        cv::Vec3b* q = dst.ptr<cv::Vec3b>(i);
        for(qint32 j = 0; j < w; j++){
            uchar cyan = p[j][0];
            uchar magenta = p[j][1];
            uchar yellow = p[j][2];
            uchar black = p[j][3];
            cyan = cyan * ((255 - black) / 255.0) + black;
            magenta = magenta * ((255 - black) / 255.0) + black;
            yellow = yellow * ((255 - black) / 255.0) + black;
            q[j][0] = 255 - cyan;
            q[j][1] = 255 - magenta;
            q[j][2] = 255 - yellow;
        }
    }

    qDebug("--------------------------");
    qDebug("CMYK CONVERT RGB END");
    return dst;
}
cv::Mat algorithm::cmyk2Hsi(cv::Mat& src){
    return src;
}

cv::Mat algorithm::cmyk2Gray(cv::Mat& src){
    return src;
}

cv::Mat algorithm::gray2rgb(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("GRAY CONVERT RGB START");
    qint32 w = src.cols, h = src.rows;
    cv::Mat dst(h, w, CV_8UC3, cv::Scalar::all(0));
    for(qint32 i = 0; i < h; i++){
        uchar* p = src.ptr<uchar>(i);
        cv::Vec3b* q = dst.ptr<cv::Vec3b>(i);
        for(qint32 j = 0; j < w; j++){
            q[j][0] = p[j];
            q[j][1] = p[j];
            q[j][2] = p[j];
        }
    }

    qDebug("GRAY CONVERT RGB END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat algorithm::gray2hsi(cv::Mat& src){
    return src;
}

cv::Mat algorithm::gray2cmyk(cv::Mat& src){
    return src;
}
