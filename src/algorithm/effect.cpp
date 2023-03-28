#include "effect.h"

cv::Mat algorithm::frostedGlassEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    std::srand(time(0));
    qDebug("random = %d", std::rand() % 8);
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 rand = std::rand() % 8;
                qint32 newGray = src.at<uchar>(i + rand, j + rand);
                qtr[j] = newGray;
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h - 8; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w - 8; j++){
                qint32 rand = std::rand() % 8;
                qint32 newRed = src.at<cv::Vec3b>(i + rand, j + rand)[0];
                qint32 newGreen = src.at<cv::Vec3b>(i + rand, j + rand)[1];
                qint32 newBlue = src.at<cv::Vec3b>(i + rand, j + rand)[2];
                qtr[j][0] = newRed;
                qtr[j][1] = newGreen;
                qtr[j][2] = newBlue;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 rand = std::rand() % 8;
                qint32 newRed = src.at<cv::Vec4b>(i + rand, j + rand)[0];
                qint32 newGreen = src.at<cv::Vec4b>(i + rand, j + rand)[1];
                qint32 newBlue = src.at<cv::Vec4b>(i + rand, j + rand)[2];
                qtr[j][0] = newRed;
                qtr[j][1] = newGreen;
                qtr[j][2] = newBlue;
            }
        }
    }

    return dst;
}

cv::Mat algorithm::reliefEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 1; i < h; i++){
            uchar* qtr = dst.ptr(i);
            for(qint32 j = 1; j < w; j++){
                qint32 value = src.at<uchar>(i, j) - src.at<uchar>(i - 1, j);
                value = std::max(0, std::min(255, value));
                qtr[j] = value;
            }
        }
    }else if(c == 3){
        for(qint32 i = 1; i < h; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 1; j < w; j++){
                qint32 value = src.at<cv::Vec3b>(i, j)[0] - src.at<cv::Vec3b>(i - 1, j)[0] + 128;
                value = std::max(0, std::min(255, value));
                qtr[j][0] = value;
                qtr[j][1] = value;
                qtr[j][2] = value;
            }
        }
    }else if(c == 4){
        for(qint32 i = 1; i < h; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 1; j < w; j++){
                qint32 value = src.at<cv::Vec4b>(i, j)[0] - src.at<cv::Vec4b>(i - 1, j)[0] + 128;
                qtr[j][0] = std::max(0, std::min(255, value));
                qtr[j][1] = std::max(0, std::min(255, value));
                qtr[j][2] = std::max(0, std::min(255, value));
            }
        }
    }

    return dst;
}

cv::Mat algorithm::oilPaintingEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));

    return dst;
}

cv::Mat algorithm::mosaicEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i += 10){
            for(qint32 j = 0; j < w; j += 10){
                if(h - i < 10 && w - j < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<uchar>(i + m, j + n) = src.at<uchar>(i, j);
                        }
                    }
                }else if(h - i < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<uchar>(i + m, j + n) = src.at<uchar>(i, j);
                        }
                    }
                }else if(w - j < 10){
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<uchar>(i + m, j + n) = src.at<uchar>(i, j);
                        }
                    }
                }else{
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<uchar>(i + m, j + n) = src.at<uchar>(i, j);
                        }
                    }
                }
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i += 10){
            for(qint32 j = 0; j < w; j += 10){
                if(h - i < 10 && w - j < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<cv::Vec3b>(i + m, j + n)[0] = src.at<cv::Vec3b>(i, j)[0];
                            dst.at<cv::Vec3b>(i + m, j + n)[1] = src.at<cv::Vec3b>(i, j)[1];
                            dst.at<cv::Vec3b>(i + m, j + n)[2] = src.at<cv::Vec3b>(i, j)[2];
                        }
                    }
                }else if(h - i < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<cv::Vec3b>(i + m, j + n)[0] = src.at<cv::Vec3b>(i, j)[0];
                            dst.at<cv::Vec3b>(i + m, j + n)[1] = src.at<cv::Vec3b>(i, j)[1];
                            dst.at<cv::Vec3b>(i + m, j + n)[2] = src.at<cv::Vec3b>(i, j)[2];
                        }
                    }
                }else if(w - j < 10){
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<cv::Vec3b>(i + m, j + n)[0] = src.at<cv::Vec3b>(i, j)[0];
                            dst.at<cv::Vec3b>(i + m, j + n)[1] = src.at<cv::Vec3b>(i, j)[1];
                            dst.at<cv::Vec3b>(i + m, j + n)[2] = src.at<cv::Vec3b>(i, j)[2];
                        }
                    }
                }else{
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<cv::Vec3b>(i + m, j + n)[0] = src.at<cv::Vec3b>(i, j)[0];
                            dst.at<cv::Vec3b>(i + m, j + n)[1] = src.at<cv::Vec3b>(i, j)[1];
                            dst.at<cv::Vec3b>(i + m, j + n)[2] = src.at<cv::Vec3b>(i, j)[2];
                        }
                    }
                }
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i += 10){
            for(qint32 j = 0; j < w; j += 10){
                if(h - i < 10 && w - j < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<cv::Vec4b>(i + m, j + n)[0] = src.at<cv::Vec4b>(i, j)[0];
                            dst.at<cv::Vec4b>(i + m, j + n)[1] = src.at<cv::Vec4b>(i, j)[1];
                            dst.at<cv::Vec4b>(i + m, j + n)[2] = src.at<cv::Vec4b>(i, j)[2];
                        }
                    }
                }else if(h - i < 10){
                    for(qint32 m = 0; m < h - i; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<cv::Vec4b>(i + m, j + n)[0] = src.at<cv::Vec4b>(i, j)[0];
                            dst.at<cv::Vec4b>(i + m, j + n)[1] = src.at<cv::Vec4b>(i, j)[1];
                            dst.at<cv::Vec4b>(i + m, j + n)[2] = src.at<cv::Vec4b>(i, j)[2];
                        }
                    }
                }else if(w - j < 10){
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < w - j; n++){
                            dst.at<cv::Vec4b>(i + m, j + n)[0] = src.at<cv::Vec4b>(i, j)[0];
                            dst.at<cv::Vec4b>(i + m, j + n)[1] = src.at<cv::Vec4b>(i, j)[1];
                            dst.at<cv::Vec4b>(i + m, j + n)[2] = src.at<cv::Vec4b>(i, j)[2];
                        }
                    }
                }else{
                    for(qint32 m = 0; m < 10; m++){
                        for(qint32 n = 0; n < 10; n++){
                            dst.at<cv::Vec4b>(i + m, j + n)[0] = src.at<cv::Vec4b>(i, j)[0];
                            dst.at<cv::Vec4b>(i + m, j + n)[1] = src.at<cv::Vec4b>(i, j)[1];
                            dst.at<cv::Vec4b>(i + m, j + n)[2] = src.at<cv::Vec4b>(i, j)[2];
                        }
                    }
                }
            }
        }
    }

    return dst;
}

cv::Mat algorithm::sketchEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    for(qint32 i = 0; i < h; i++){
        for(qint32 j = 0; j < w; j++){

        }
    }

    return dst;
}

cv::Mat algorithm::fleetingTimeEffect(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    cv::Mat grayMat(h, w, CV_8UC1, cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* p = src.ptr<cv::Vec3b>(i);
            uchar* q = grayMat.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = (p[j][0] * 28 + p[j][1] * 151 + p[j][2] * 77) >> 8;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* p = src.ptr<cv::Vec4b>(i);
            uchar* q = grayMat.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                q[j] = (p[j][0] * 28 + p[j][1] * 151 + p[j][2] * 77) >> 8;
            }
        }
    }

    return dst;
}
