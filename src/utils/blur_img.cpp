#include "blur_img.h"

cv::Mat utils::gaussianFilter(cv::Mat& src, qint32 radius, double sigma){
    qDebug("--------------------------");
    qDebug("GAUSS FILTER START");
    qint32 w = src.cols, h = src.rows, c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    qint32 size = 2 * radius + 1;
    cv::Mat window(1, size, CV_64F, cv::Scalar::all(0));
    double* f = window.ptr<double>(0);
    double sum = 0;
    for(qint32 i = 0; i < size; i++){
        double g = std::exp(-static_cast<double>(std::pow(i - radius, 2) / (2 * sigma * sigma)));
        f[i] = g;
        sum += g;
    }

    // 归一化
    window = window / sum;

//    for(qint32 i = 0; i < size; i++){
//        qDebug()<<window.at<float>(0, i);
//    }

    if(c == 1){
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

                qtr[j] = static_cast<uchar>(t);
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

                dst.at<uchar>(i, j) = static_cast<uchar>(t);
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b *ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b *qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                double t1 = 0, t2 = 0, t3 = 0;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        t1 += static_cast<double>(ptr[k][0]) * f[k - j + radius];
                        t2 += static_cast<double>(ptr[k][1]) * f[k - j + radius];
                        t3 += static_cast<double>(ptr[k][2]) * f[k - j + radius];
                    }
                }

                qtr[j][0] = static_cast<uchar>(t1);
                qtr[j][1] = static_cast<uchar>(t2);
                qtr[j][2] = static_cast<uchar>(t3);
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 j = 0; j < w; j++){
            for(qint32 i = 0; i < h; i++){
                double t1 = 0, t2 = 0, t3 = 0;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        t1 += static_cast<double>(tmpMat.at<cv::Vec3b>(k, j)[0]) * f[k - i + radius];
                        t2 += static_cast<double>(tmpMat.at<cv::Vec3b>(k, j)[1]) * f[k - i + radius];
                        t3 += static_cast<double>(tmpMat.at<cv::Vec3b>(k, j)[2]) * f[k - i + radius];
                    }
                }

                dst.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(t1);
                dst.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(t2);
                dst.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(t3);
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b *ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b *qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        t1 += static_cast<double>(ptr[k][0]) * f[k - j + radius];
                        t2 += static_cast<double>(ptr[k][1]) * f[k - j + radius];
                        t3 += static_cast<double>(ptr[k][2]) * f[k - j + radius];
                        t4 += static_cast<double>(ptr[k][3]) * f[k - j + radius];
                    }
                }

                qtr[j][0] = t1;
                qtr[j][1] = t2;
                qtr[j][2] = t3;
                qtr[j][3] = t4;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 j = 0; j < w; j++){
            for(qint32 i = 0; i < h; i++){
                double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        t1 += static_cast<double>(tmpMat.at<cv::Vec4b>(k, j)[0]) * f[k - i + radius];
                        t2 += static_cast<double>(tmpMat.at<cv::Vec4b>(k, j)[1]) * f[k - i + radius];
                        t3 += static_cast<double>(tmpMat.at<cv::Vec4b>(k, j)[2]) * f[k - i + radius];
                        t4 += static_cast<double>(tmpMat.at<cv::Vec4b>(k, j)[3]) * f[k - i + radius];
                    }
                }

                dst.at<cv::Vec4b>(i, j)[0] = static_cast<uchar>(t1);
                dst.at<cv::Vec4b>(i, j)[1] = static_cast<uchar>(t2);
                dst.at<cv::Vec4b>(i, j)[2] = static_cast<uchar>(t3);
                dst.at<cv::Vec4b>(i, j)[3] = static_cast<uchar>(t4);
            }
        }
    }

    qDebug("GAUSS FILTER END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat utils::linearMeanFilter(cv::Mat& src, qint32 radius){
    qDebug("--------------------------");
    qDebug("LINEAR MEAN FILTER START");
    qint32 w = src.cols, h = src.rows;
    double size = std::pow(2 * radius + 1, 2);
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    cv::Mat srcIntegral;
    cv::integral(src, srcIntegral, CV_64F);
    qDebug("c = %d", c);
    qDebug()<<srcIntegral.channels();
    qDebug("radius = %d", radius);
    if (c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* qtr = dst.ptr<uchar>(i);
            qint32 x1 = std::max(1, i - radius + 1);
            qint32 x2 = std::min(h, i + radius + 1);
            for(qint32 j = 0; j < w; j++){
                qint32 y1 = std::max(1, j - radius + 1);
                qint32 y2 = std::min(w, j + radius + 1);
                double sum = srcIntegral.at<double>(x2, y2) - srcIntegral.at<double>(x1, y2) - srcIntegral.at<double>(x2, y1) + srcIntegral.at<double>(x1, y1);
                qtr[j] = static_cast<uchar>(sum / size);
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            qint32 x1 = std::max(1, i - radius + 1);
            qint32 x2 = std::min(h, i + radius + 1);
            for(qint32 j = 0; j < w; j++){
                qint32 y1 = std::max(1, j - radius + 1);
                qint32 y2 = std::min(w, j + radius + 1);
                double sum1 = srcIntegral.at<cv::Vec3d>(x2, y2)[0] - srcIntegral.at<cv::Vec3d>(x1, y2)[0] - srcIntegral.at<cv::Vec3d>(x2, y1)[0] + srcIntegral.at<cv::Vec3d>(x1, y1)[0];
                double sum2 = srcIntegral.at<cv::Vec3d>(x2, y2)[1] - srcIntegral.at<cv::Vec3d>(x1, y2)[1] - srcIntegral.at<cv::Vec3d>(x2, y1)[1] + srcIntegral.at<cv::Vec3d>(x1, y1)[1];
                double sum3 = srcIntegral.at<cv::Vec3d>(x2, y2)[2] - srcIntegral.at<cv::Vec3d>(x1, y2)[2] - srcIntegral.at<cv::Vec3d>(x2, y1)[2] + srcIntegral.at<cv::Vec3d>(x1, y1)[2];
                qtr[j][0] = static_cast<uchar>(sum1 / size);
                qtr[j][1] = static_cast<uchar>(sum2 / size);
                qtr[j][2] = static_cast<uchar>(sum3 / size);
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            qint32 x1 = std::max(1, i - radius + 1);
            qint32 x2 = std::min(h, i + radius + 1);
            for(qint32 j = 0; j < w; j++){
                qint32 y1 = std::max(1, j - radius + 1);
                qint32 y2 = std::min(w, j + radius + 1);
                double sum1 = srcIntegral.at<cv::Vec4d>(x2, y2)[0] - srcIntegral.at<cv::Vec4d>(x1, y2)[0] - srcIntegral.at<cv::Vec4d>(x2, y1)[0] + srcIntegral.at<cv::Vec4d>(x1, y1)[0];
                double sum2 = srcIntegral.at<cv::Vec4d>(x2, y2)[1] - srcIntegral.at<cv::Vec4d>(x1, y2)[1] - srcIntegral.at<cv::Vec4d>(x2, y1)[1] + srcIntegral.at<cv::Vec4d>(x1, y1)[1];
                double sum3 = srcIntegral.at<cv::Vec4d>(x2, y2)[2] - srcIntegral.at<cv::Vec4d>(x1, y2)[2] - srcIntegral.at<cv::Vec4d>(x2, y1)[2] + srcIntegral.at<cv::Vec4d>(x1, y1)[2];
                double sum4 = srcIntegral.at<cv::Vec4d>(x2, y2)[3] - srcIntegral.at<cv::Vec4d>(x1, y2)[3] - srcIntegral.at<cv::Vec4d>(x2, y1)[3] + srcIntegral.at<cv::Vec4d>(x1, y1)[3];
                qtr[j][0] = static_cast<uchar>(sum1 / size);
                qtr[j][1] = static_cast<uchar>(sum2 / size);
                qtr[j][2] = static_cast<uchar>(sum3 / size);
                qtr[j][3] = static_cast<uchar>(sum4 / size);
            }
        }
    }

    qDebug("LINEAR MEAN FILTER END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat utils::maximumFilter(cv::Mat& src, qint32 radius){
    qDebug("--------------------------");
    qDebug("MAXIMUM FILTER START");
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    qint32 size = 2 * radius + 1;
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    qDebug("radius = %d", radius);
    qDebug("size = %d", size);
    qDebug("channels = %d", c);
    if (c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max = 0;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t = ptr[k];
                        max = std::max(max, t);
                    }
                }

                qtr[j] = max;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max = 0;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t = tmpMat.at<uchar>(k, j);
                        max = std::max(max, t);
                    }
                }

                qtr[j] = max;
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max1 = 0, max2 = 0, max3 = 0;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t1 = ptr[k][0];
                        qint32 t2 = ptr[k][1];
                        qint32 t3 = ptr[k][2];
                        max1 = std::max(max1, t1);
                        max2 = std::max(max2, t2);
                        max3 = std::max(max3, t3);
                    }
                }

                qtr[j][0] = max1;
                qtr[j][1] = max2;
                qtr[j][2] = max3;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max1 = 0, max2 = 0, max3 = 0;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t1 = tmpMat.at<cv::Vec3b>(k, j)[0];
                        qint32 t2 = tmpMat.at<cv::Vec3b>(k, j)[1];
                        qint32 t3 = tmpMat.at<cv::Vec3b>(k, j)[2];
                        max1 = std::max(max1, t1);
                        max2 = std::max(max2, t2);
                        max3 = std::max(max3, t3);
                    }
                }

                qtr[j][0] = max1;
                qtr[j][1] = max2;
                qtr[j][2] = max3;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max1 = 0, max2 = 0, max3 = 0, max4 = 0;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t1 = ptr[k][0];
                        qint32 t2 = ptr[k][1];
                        qint32 t3 = ptr[k][2];
                        qint32 t4 = ptr[k][3];
                        max1 = std::max(max1, t1);
                        max2 = std::max(max2, t2);
                        max3 = std::max(max3, t3);
                        max4 = std::max(max4, t4);
                    }
                }

                qtr[j][0] = max1;
                qtr[j][1] = max2;
                qtr[j][2] = max3;
                qtr[j][3] = max4;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 max1 = 0, max2 = 0, max3 = 0, max4 = 0;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t1 = tmpMat.at<cv::Vec4b>(k, j)[0];
                        qint32 t2 = tmpMat.at<cv::Vec4b>(k, j)[1];
                        qint32 t3 = tmpMat.at<cv::Vec4b>(k, j)[2];
                        qint32 t4 = tmpMat.at<cv::Vec4b>(k, j)[3];
                        max1 = std::max(max1, t1);
                        max2 = std::max(max2, t2);
                        max3 = std::max(max3, t3);
                        max4 = std::max(max4, t4);
                    }
                }

                qtr[j][0] = max1;
                qtr[j][1] = max2;
                qtr[j][2] = max3;
                qtr[j][3] = max4;
            }
        }
    }

    qDebug("MAXIMUM FILTER END");
    qDebug("--------------------------");
    return dst;
}

cv::Mat utils::medianFilter(cv::Mat& src, qint32 radius){
    return src;
}

cv::Mat utils::minimumFilter(cv::Mat& src, qint32 radius){
    qDebug("--------------------------");
    qDebug("MINIMUM FILTER START");
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(w, h, CV_8UC(c), cv::Scalar::all(0));
    if (c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min = 255;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t = ptr[k];
                        min = std::min(min, t);
                    }
                }

                qtr[j] = min;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min = 255;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t = tmpMat.at<uchar>(k, j);
                        min = std::min(min, t);
                    }
                }

                qtr[j] = min;
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min1 = 255, min2 = 255, min3 = 255;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t1 = ptr[k][0];
                        qint32 t2 = ptr[k][1];
                        qint32 t3 = ptr[k][2];
                        min1 = std::min(min1, t1);
                        min2 = std::min(min2, t2);
                        min3 = std::min(min3, t3);
                    }
                }

                qtr[j][0] = min1;
                qtr[j][1] = min2;
                qtr[j][2] = min3;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min1 = 255, min2 = 255, min3 = 255;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t1 = tmpMat.at<cv::Vec3b>(k, j)[0];
                        qint32 t2 = tmpMat.at<cv::Vec3b>(k, j)[1];
                        qint32 t3 = tmpMat.at<cv::Vec3b>(k, j)[2];
                        min1 = std::min(min1, t1);
                        min2 = std::min(min2, t2);
                        min3 = std::min(min3, t3);
                    }
                }

                qtr[j][0] = min1;
                qtr[j][1] = min2;
                qtr[j][2] = min3;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min1 = 255, min2 = 255, min3 = 255, min4 = 255;
                for(qint32 k = j - radius; k <= j + radius; k++ ){
                    if(k > - 1 && k < w){
                        qint32 t1 = ptr[k][0];
                        qint32 t2 = ptr[k][1];
                        qint32 t3 = ptr[k][2];
                        qint32 t4 = ptr[k][3];
                        min1 = std::min(min1, t1);
                        min2 = std::min(min2, t2);
                        min3 = std::min(min3, t3);
                        min4 = std::min(min4, t4);
                    }
                }

                qtr[j][0] = min1;
                qtr[j][1] = min2;
                qtr[j][2] = min3;
                qtr[j][3] = min4;
            }
        }

        cv::Mat tmpMat = dst.clone();
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 min1 = 255, min2 = 255, min3 = 255, min4 = 255;
                for(qint32 k = i - radius; k <= i + radius; k++ ){
                    if(k > - 1 && k < h){
                        qint32 t1 = tmpMat.at<cv::Vec4b>(k, j)[0];
                        qint32 t2 = tmpMat.at<cv::Vec4b>(k, j)[1];
                        qint32 t3 = tmpMat.at<cv::Vec4b>(k, j)[2];
                        qint32 t4 = tmpMat.at<cv::Vec4b>(k, j)[3];
                        min1 = std::min(min1, t1);
                        min2 = std::min(min2, t2);
                        min3 = std::min(min3, t3);
                        min4 = std::min(min4, t4);
                    }
                }

                qtr[j][0] = min1;
                qtr[j][1] = min2;
                qtr[j][2] = min3;
                qtr[j][3] = min4;
            }
        }
    }

    qDebug("MINIMUM FILTER END");
    qDebug("--------------------------");
    return dst;
}
