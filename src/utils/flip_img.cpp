#include "flip_img.h"

cv::Mat utils::flipHorizontally(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("FLIP HORIZONTALLY START");
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar *q = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = src.at<uchar>(i, w - j - 1);
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* q = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                q[j][0] = src.at<cv::Vec3b>(i, w - j - 1)[0];
                q[j][1] = src.at<cv::Vec3b>(i, w - j - 1)[1];
                q[j][2] = src.at<cv::Vec3b>(i, w - j - 1)[2];
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* q = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                q[j][0] = src.at<cv::Vec4b>(i, w - j - 1)[0];
                q[j][1] = src.at<cv::Vec4b>(i, w - j - 1)[1];
                q[j][2] = src.at<cv::Vec4b>(i, w - j - 1)[2];
                q[j][3] = src.at<cv::Vec4b>(i, w - j - 1)[3];
            }
        }
    }

    qDebug("FLIP HORIZONTALLY END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat utils::flipVertically(cv::Mat& src){
    qDebug("--------------------------");
    qDebug("FLIP VERTICALLY START");
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar *q = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = src.at<uchar>(h - i - 1, j);
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* q = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                q[j][0] = src.at<cv::Vec3b>(h - i - 1, j)[0];
                q[j][1] = src.at<cv::Vec3b>(h - i - 1, j)[1];
                q[j][2] = src.at<cv::Vec3b>(h - i - 1, j)[2];
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* q = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                q[j][0] = src.at<cv::Vec4b>(h - i - 1, j)[0];
                q[j][1] = src.at<cv::Vec4b>(h - i - 1, j)[1];
                q[j][2] = src.at<cv::Vec4b>(h - i - 1, j)[2];
                q[j][3] = src.at<cv::Vec4b>(h - i - 1, j)[3];
            }
        }
    }

    qDebug("FLIP VERTICALLY END");
    qDebug("--------------------------");
    return dst;
}
