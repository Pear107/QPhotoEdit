#include "sharpen_img.h"

cv::Mat algorithm::gradsOperator(cv::Mat& src){
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h - 1; i++){
            uchar *ptr = src.ptr<uchar>(i);
            uchar *qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx = std::pow(src.at<uchar>(i, j) - src.at<uchar>(i + 1, j + 1), 2);
                qint32 dy = std::pow(src.at<uchar>(i, j) - src.at<uchar>(i, j + 1), 2);
                qint32 t = cv::saturate_cast<uchar>(std::sqrt(dx + dy)) + ptr[j];
                qtr[j] = std::max(0, std::min(255, t));
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h - 1; i++){
            cv::Vec3b *ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b *qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec3b>(i, j)[0] - src.at<cv::Vec3b>(i + 1, j + 1)[0], 2);
                qint32 dx2 = std::pow(src.at<cv::Vec3b>(i, j)[1] - src.at<cv::Vec3b>(i + 1, j + 1)[1], 2);
                qint32 dx3 = std::pow(src.at<cv::Vec3b>(i, j)[2] - src.at<cv::Vec3b>(i + 1, j + 1)[2], 2);
                qint32 dy1 = std::pow(src.at<cv::Vec3b>(i, j)[0] - src.at<cv::Vec3b>(i, j + 1)[0], 2);
                qint32 dy2 = std::pow(src.at<cv::Vec3b>(i, j)[1] - src.at<cv::Vec3b>(i, j + 1)[1], 2);
                qint32 dy3 = std::pow(src.at<cv::Vec3b>(i, j)[2] - src.at<cv::Vec3b>(i, j + 1)[2], 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][1];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][2];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h - 1; i++){
            cv::Vec4b *ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b *qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec4b>(i, j)[0] - src.at<cv::Vec4b>(i + 1, j + 1)[0], 2);
                qint32 dx2 = std::pow(src.at<cv::Vec4b>(i, j)[1] - src.at<cv::Vec4b>(i + 1, j + 1)[1], 2);
                qint32 dx3 = std::pow(src.at<cv::Vec4b>(i, j)[2] - src.at<cv::Vec4b>(i + 1, j + 1)[2], 2);
                qint32 dx4 = std::pow(src.at<cv::Vec4b>(i, j)[3] - src.at<cv::Vec4b>(i + 1, j + 1)[3], 2);
                qint32 dy1 = std::pow(src.at<cv::Vec4b>(i, j)[0] - src.at<cv::Vec4b>(i, j + 1)[0], 2);
                qint32 dy2 = std::pow(src.at<cv::Vec4b>(i, j)[1] - src.at<cv::Vec4b>(i, j + 1)[1], 2);
                qint32 dy3 = std::pow(src.at<cv::Vec4b>(i, j)[2] - src.at<cv::Vec4b>(i, j + 1)[2], 2);
                qint32 dy4 = std::pow(src.at<cv::Vec4b>(i, j)[3] - src.at<cv::Vec4b>(i, j + 1)[3], 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][1];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][2];
                qint32 t4 = cv::saturate_cast<uchar>(std::sqrt(dx4 + dy4)) + ptr[j][3];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
                qtr[j][3] = std::max(0, std::min(255, t4));
            }
        }
    }

    return dst;
}

cv::Mat algorithm::laplaceOperator(cv::Mat& src){
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 1; i < h - 1; i++){
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 gray = 5 * src.at<uchar>(i, j) - src.at<uchar>(i - 1, j) - src.at<uchar>(i, j - 1) - src.at<uchar>(i + 1, j) - src.at<uchar>(i, j + 1);
                qtr[j] = std::max(0, std::min(255, gray));
            }
        }
    }else if(c == 3){
        for(qint32 i = 1; i < h - 1; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 rgb = 5 * src.at<cv::Vec3b>(i, j)[0] - src.at<cv::Vec3b>(i - 1, j)[0] - src.at<cv::Vec3b>(i, j - 1)[0] - src.at<cv::Vec3b>(i + 1, j)[0] - src.at<cv::Vec3b>(i, j + 1)[0];
                qint32 green = 5 * src.at<cv::Vec3b>(i, j)[1] - src.at<cv::Vec3b>(i - 1, j)[1] - src.at<cv::Vec3b>(i, j - 1)[1] - src.at<cv::Vec3b>(i + 1, j)[1] - src.at<cv::Vec3b>(i, j + 1)[1];
                qint32 blue = 5 * src.at<cv::Vec3b>(i, j)[2] - src.at<cv::Vec3b>(i - 1, j)[2] - src.at<cv::Vec3b>(i, j - 1)[2] - src.at<cv::Vec3b>(i + 1, j)[2] - src.at<cv::Vec3b>(i, j + 1)[2];
                qtr[j][0] = std::max(0, std::min(255, rgb));
                qtr[j][1] = std::max(0, std::min(255, green));
                qtr[j][2] = std::max(0, std::min(255, blue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 1; i < h -1; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 rgb = 5 * src.at<cv::Vec4b>(i, j)[0] - src.at<cv::Vec4b>(i - 1, j)[0] - src.at<cv::Vec4b>(i, j - 1)[0] - src.at<cv::Vec4b>(i + 1, j)[0] - src.at<cv::Vec4b>(i, j + 1)[0];
                qint32 green = 5 * src.at<cv::Vec4b>(i, j)[1] - src.at<cv::Vec4b>(i - 1, j)[1] - src.at<cv::Vec4b>(i, j - 1)[1] - src.at<cv::Vec4b>(i + 1, j)[1] - src.at<cv::Vec4b>(i, j + 1)[1];
                qint32 blue = 5 * src.at<cv::Vec4b>(i, j)[2] - src.at<cv::Vec4b>(i - 1, j)[2] - src.at<cv::Vec4b>(i, j - 1)[2] - src.at<cv::Vec4b>(i + 1, j)[2] - src.at<cv::Vec4b>(i, j + 1)[2];
                qint32 alpha = 5 * src.at<cv::Vec4b>(i, j)[3] - src.at<cv::Vec4b>(i - 1, j)[3] - src.at<cv::Vec4b>(i, j - 1)[3] - src.at<cv::Vec4b>(i + 1, j)[3] - src.at<cv::Vec4b>(i, j + 1)[3];
                qtr[j][0] = std::max(0, std::min(255, rgb));
                qtr[j][1] = std::max(0, std::min(255, green));
                qtr[j][2] = std::max(0, std::min(255, blue));
                qtr[j][3] = std::max(0, std::min(255, alpha));
            }
        }
    }

    return dst;
}

cv::Mat algorithm::robertsOperator(cv::Mat& src){
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h - 1; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx = std::pow(src.at<uchar>(i, j) - src.at<uchar>(i + 1, j + 1), 2);
                qint32 dy = std::pow(src.at<uchar>(i + 1, j) - src.at<uchar>(i, j + 1), 2);
                qint32 t = cv::saturate_cast<uchar>(std::sqrt(dx + dy)) + ptr[j];
                qtr[j] = std::max(0, std::min(255, t));
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h - 1; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec3b>(i, j)[0] - src.at<cv::Vec3b>(i + 1, j + 1)[0], 2);
                qint32 dx2 = std::pow(src.at<cv::Vec3b>(i, j)[1] - src.at<cv::Vec3b>(i + 1, j + 1)[1], 2);
                qint32 dx3 = std::pow(src.at<cv::Vec3b>(i, j)[2] - src.at<cv::Vec3b>(i + 1, j + 1)[2], 2);
                qint32 dy1 = std::pow(src.at<cv::Vec3b>(i + 1, j)[0] - src.at<cv::Vec3b>(i, j + 1)[0], 2);
                qint32 dy2 = std::pow(src.at<cv::Vec3b>(i + 1, j)[1] - src.at<cv::Vec3b>(i, j + 1)[1], 2);
                qint32 dy3 = std::pow(src.at<cv::Vec3b>(i + 1, j)[2] - src.at<cv::Vec3b>(i, j + 1)[2], 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][1];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][2];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h - 1; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec4b>(i, j)[0] - src.at<cv::Vec4b>(i + 1, j + 1)[0], 2);
                qint32 dx2 = std::pow(src.at<cv::Vec4b>(i, j)[1] - src.at<cv::Vec4b>(i + 1, j + 1)[1], 2);
                qint32 dx3 = std::pow(src.at<cv::Vec4b>(i, j)[2] - src.at<cv::Vec4b>(i + 1, j + 1)[2], 2);
                qint32 dx4 = std::pow(src.at<cv::Vec4b>(i, j)[3] - src.at<cv::Vec4b>(i + 1, j + 1)[3], 2);
                qint32 dy1 = std::pow(src.at<cv::Vec4b>(i + 1, j)[0] - src.at<cv::Vec4b>(i, j + 1)[0], 2);
                qint32 dy2 = std::pow(src.at<cv::Vec4b>(i + 1, j)[1] - src.at<cv::Vec4b>(i, j + 1)[1], 2);
                qint32 dy3 = std::pow(src.at<cv::Vec4b>(i + 1, j)[2] - src.at<cv::Vec4b>(i, j + 1)[2], 2);
                qint32 dy4 = std::pow(src.at<cv::Vec4b>(i + 1, j)[3] - src.at<cv::Vec4b>(i, j + 1)[3], 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][1];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][2];
                qint32 t4 = cv::saturate_cast<uchar>(std::sqrt(dx4 + dy4)) + ptr[j][3];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
                qtr[j][3] = std::max(0, std::min(255, t4));
            }
        }
    }

    return dst;
}

cv::Mat algorithm::sobelOperator(cv::Mat& src){
    qint32 w = src.cols, h= src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 1; i < h - 1; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 dx = std::pow(src.at<uchar>(i - 1, j + 1) + 2 * src.at<uchar>(i, j + 1) + src.at<uchar>(i + 1, j + 1) - src.at<uchar>(i - 1, j - 1) - 2 * src.at<uchar>(i, j - 1) - src.at<uchar>(i + 1, j - 1) , 2);
                qint32 dy = std::pow(src.at<uchar>(i - 1, j - 1) + 2 * src.at<uchar>(i - 1, j) + src.at<uchar>(i - 1, j + 1) - src.at<uchar>(i + 1, j - 1) - 2 * src.at<uchar>(i + 1, j) - src.at<uchar>(i + 1, j + 1) , 2);
                qint32 t = cv::saturate_cast<uchar>(std::sqrt(dx + dy)) + ptr[j];
                qtr[j] = std::max(0, std::min(255, t));
            }
        }
    }else if(c == 3){
        for(qint32 i = 1; i < h - 1; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec3b>(i - 1, j + 1)[0] + 2 * src.at<cv::Vec3b>(i, j + 1)[0] + src.at<cv::Vec3b>(i + 1, j + 1)[0] - src.at<cv::Vec3b>(i - 1, j - 1)[0] - 2 * src.at<cv::Vec3b>(i, j - 1)[0] - src.at<cv::Vec3b>(i + 1, j - 1)[0] , 2);
                qint32 dx2 = std::pow(src.at<cv::Vec3b>(i - 1, j + 1)[1] + 2 * src.at<cv::Vec3b>(i, j + 1)[1] + src.at<cv::Vec3b>(i + 1, j + 1)[1] - src.at<cv::Vec3b>(i - 1, j - 1)[1] - 2 * src.at<cv::Vec3b>(i, j - 1)[1] - src.at<cv::Vec3b>(i + 1, j - 1)[1] , 2);
                qint32 dx3 = std::pow(src.at<cv::Vec3b>(i - 1, j + 1)[2] + 2 * src.at<cv::Vec3b>(i, j + 1)[2] + src.at<cv::Vec3b>(i + 1, j + 1)[2] - src.at<cv::Vec3b>(i - 1, j - 1)[2] - 2 * src.at<cv::Vec3b>(i, j - 1)[2] - src.at<cv::Vec3b>(i + 1, j - 1)[2] , 2);
                qint32 dy1 = std::pow(src.at<cv::Vec3b>(i - 1, j - 1)[0] + 2 * src.at<cv::Vec3b>(i - 1, j)[0] + src.at<cv::Vec3b>(i - 1, j + 1)[0] - src.at<cv::Vec3b>(i + 1, j - 1)[0] - 2 * src.at<cv::Vec3b>(i + 1, j)[0] - src.at<cv::Vec3b>(i + 1, j + 1)[0] , 2);
                qint32 dy2 = std::pow(src.at<cv::Vec3b>(i - 1, j - 1)[1] + 2 * src.at<cv::Vec3b>(i - 1, j)[1] + src.at<cv::Vec3b>(i - 1, j + 1)[1] - src.at<cv::Vec3b>(i + 1, j - 1)[1] - 2 * src.at<cv::Vec3b>(i + 1, j)[1] - src.at<cv::Vec3b>(i + 1, j + 1)[1] , 2);
                qint32 dy3 = std::pow(src.at<cv::Vec3b>(i - 1, j - 1)[2] + 2 * src.at<cv::Vec3b>(i - 1, j)[2] + src.at<cv::Vec3b>(i - 1, j + 1)[2] - src.at<cv::Vec3b>(i + 1, j - 1)[2] - 2 * src.at<cv::Vec3b>(i + 1, j)[2] - src.at<cv::Vec3b>(i + 1, j + 1)[2] , 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][0];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][0];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
            }
        }
    }else if(c == 4){
        for(qint32 i = 1; i < h - 1; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 1; j < w - 1; j++){
                qint32 dx1 = std::pow(src.at<cv::Vec4b>(i - 1, j + 1)[0] + 2 * src.at<cv::Vec4b>(i, j + 1)[0] + src.at<cv::Vec4b>(i + 1, j + 1)[0] - src.at<cv::Vec4b>(i - 1, j - 1)[0] - 2 * src.at<cv::Vec4b>(i, j - 1)[0] - src.at<cv::Vec4b>(i + 1, j - 1)[0] , 2);
                qint32 dx2 = std::pow(src.at<cv::Vec4b>(i - 1, j + 1)[1] + 2 * src.at<cv::Vec4b>(i, j + 1)[1] + src.at<cv::Vec4b>(i + 1, j + 1)[1] - src.at<cv::Vec4b>(i - 1, j - 1)[1] - 2 * src.at<cv::Vec4b>(i, j - 1)[1] - src.at<cv::Vec4b>(i + 1, j - 1)[1] , 2);
                qint32 dx3 = std::pow(src.at<cv::Vec4b>(i - 1, j + 1)[2] + 2 * src.at<cv::Vec4b>(i, j + 1)[2] + src.at<cv::Vec4b>(i + 1, j + 1)[2] - src.at<cv::Vec4b>(i - 1, j - 1)[2] - 2 * src.at<cv::Vec4b>(i, j - 1)[2] - src.at<cv::Vec4b>(i + 1, j - 1)[2] , 2);
                qint32 dx4 = std::pow(src.at<cv::Vec4b>(i - 1, j + 1)[3] + 2 * src.at<cv::Vec4b>(i, j + 1)[3] + src.at<cv::Vec4b>(i + 1, j + 1)[3] - src.at<cv::Vec4b>(i - 1, j - 1)[2] - 2 * src.at<cv::Vec4b>(i, j - 1)[2] - src.at<cv::Vec4b>(i + 1, j - 1)[2] , 2);
                qint32 dy1 = std::pow(src.at<cv::Vec4b>(i - 1, j - 1)[0] + 2 * src.at<cv::Vec4b>(i - 1, j)[0] + src.at<cv::Vec4b>(i - 1, j + 1)[0] - src.at<cv::Vec4b>(i + 1, j - 1)[0] - 2 * src.at<cv::Vec4b>(i + 1, j)[0] - src.at<cv::Vec4b>(i + 1, j + 1)[0] , 2);
                qint32 dy2 = std::pow(src.at<cv::Vec4b>(i - 1, j - 1)[1] + 2 * src.at<cv::Vec4b>(i - 1, j)[1] + src.at<cv::Vec4b>(i - 1, j + 1)[1] - src.at<cv::Vec4b>(i + 1, j - 1)[1] - 2 * src.at<cv::Vec4b>(i + 1, j)[1] - src.at<cv::Vec4b>(i + 1, j + 1)[1] , 2);
                qint32 dy3 = std::pow(src.at<cv::Vec4b>(i - 1, j - 1)[2] + 2 * src.at<cv::Vec4b>(i - 1, j)[2] + src.at<cv::Vec4b>(i - 1, j + 1)[2] - src.at<cv::Vec4b>(i + 1, j - 1)[2] - 2 * src.at<cv::Vec4b>(i + 1, j)[2] - src.at<cv::Vec4b>(i + 1, j + 1)[2] , 2);
                qint32 dy4 = std::pow(src.at<cv::Vec4b>(i - 1, j - 1)[3] + 2 * src.at<cv::Vec4b>(i - 1, j)[3] + src.at<cv::Vec4b>(i - 1, j + 1)[3] - src.at<cv::Vec4b>(i + 1, j - 1)[3] - 2 * src.at<cv::Vec4b>(i + 1, j)[3] - src.at<cv::Vec4b>(i + 1, j + 1)[3] , 2);
                qint32 t1 = cv::saturate_cast<uchar>(std::sqrt(dx1 + dy1)) + ptr[j][0];
                qint32 t2 = cv::saturate_cast<uchar>(std::sqrt(dx2 + dy2)) + ptr[j][0];
                qint32 t3 = cv::saturate_cast<uchar>(std::sqrt(dx3 + dy3)) + ptr[j][0];
                qint32 t4 = cv::saturate_cast<uchar>(std::sqrt(dx4 + dy4)) + ptr[j][0];
                qtr[j][0] = std::max(0, std::min(255, t1));
                qtr[j][1] = std::max(0, std::min(255, t2));
                qtr[j][2] = std::max(0, std::min(255, t3));
                qtr[j][3] = std::max(0, std::min(255, t4));
            }
        }
    }

    return dst;
}
