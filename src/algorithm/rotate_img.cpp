#include "rotate_img.h"

cv::Mat algorithm::rotateLeft(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("ROTATE LEFT START");
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(w, h, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(quint32 i = 0; i < w; i++){
            uchar *q = dst.ptr<uchar>(i);
            for(quint32 j = 0; j < h; j++){
                q[j] = src.at<uchar>(j, w - i - 1);
            }
        }
    }else if(c == 3){
        for(quint32 i = 0; i < w; i++){
            cv::Vec3b *q = dst.ptr<cv::Vec3b>(i);
            auto test = cv::Vec<uchar, 3>(0, 0, 0);
            for(quint32 j = 0; j < h; j++){
                q[j][0] = src.at<cv::Vec3b>(j, w - i - 1)[0];
                q[j][1] = src.at<cv::Vec3b>(j, w - i - 1)[1];
                q[j][2] = src.at<cv::Vec3b>(j, w - i - 1)[2];
            }
        }
    }else if(c == 4){
        for(quint32 i = 0; i < w; i++){
            cv::Vec4b *q = dst.ptr<cv::Vec4b>(i);
            for(quint32 j = 0; j < h; j++){
                q[j][0] = src.at<cv::Vec4b>(j, w - i - 1)[0];
                q[j][1] = src.at<cv::Vec4b>(j, w - i - 1)[1];
                q[j][2] = src.at<cv::Vec4b>(j, w - i - 1)[2];
                q[j][3] = src.at<cv::Vec4b>(j, w - i - 1)[3];
            }
        }
    }

    qDebug("ROTATE LEFT END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat algorithm::rotateRight(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("ROTATE RIGHT START");
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(w, h, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(quint32 i = 0; i < w; i++){
            uchar *q = dst.ptr<uchar>(i);
            for(quint32 j = 0; j < h; j++){
                q[j] = src.at<uchar>(h - j - 1, i);
            }
        }
    }else if(c == 3){
        for(quint32 i = 0; i < w; i++){
            cv::Vec3b *q = dst.ptr<cv::Vec3b>(i);
            auto test = cv::Vec<uchar, 3>(0, 0, 0);
            for(quint32 j = 0; j < h; j++){
                q[j][0] = src.at<cv::Vec3b>(h - j - 1, i)[0];
                q[j][1] = src.at<cv::Vec3b>(h - j - 1, i)[1];
                q[j][2] = src.at<cv::Vec3b>(h - j - 1, i)[2];
            }
        }
    }else if(c == 4){
        for(quint32 i = 0; i < w; i++){
            cv::Vec4b *q = dst.ptr<cv::Vec4b>(i);
            for(quint32 j = 0; j < h; j++){
                q[j][0] = src.at<cv::Vec4b>(h - j - 1, i)[0];
                q[j][1] = src.at<cv::Vec4b>(h - j - 1, i)[1];
                q[j][2] = src.at<cv::Vec4b>(h - j - 1, i)[2];
                q[j][3] = src.at<cv::Vec4b>(h - j - 1, i)[3];
            }
        }
    }

    qDebug("ROTATE RIGHT END");
    qDebug("--------------------------");
    return dst;
}
