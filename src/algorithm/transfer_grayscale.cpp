#include "transfer_grayscale.h"

cv::Mat algorithm::linearGrayTransfer(cv::Mat& src, double a, qint32 b){
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* q = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 gray = static_cast<qint32>(a * static_cast<double>(src.at<uchar>(i, j)) + b);
                q[j] = std::max(0, std::min(255, gray));
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* q = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec3b>(i, j)[0])) + b;
                qint32 green = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec3b>(i, j)[1])) + b;
                qint32 blue = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec3b>(i, j)[2])) + b;
                q[j][0] = std::max(0, std::min(255, red));
                q[j][1] = std::max(0, std::min(255, green));
                q[j][2] = std::max(0, std::min(255, blue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* q = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec4b>(i, j)[0])) + b;
                qint32 green = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec4b>(i, j)[1])) + b;
                qint32 blue = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec4b>(i, j)[2])) + b;
                qint32 alpha = static_cast<qint32>(a * static_cast<double>(src.at<cv::Vec4b>(i, j)[2])) + b;
                q[j][0] = std::max(0, std::min(255, red));
                q[j][1] = std::max(0, std::min(255, green));
                q[j][2] = std::max(0, std::min(255, blue));
                q[j][3] = std::max(0, std::min(255, alpha));
            }
        }
    }

    return dst;
}
