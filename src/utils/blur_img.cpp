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
    }else if(c == 3 || c == 4){
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
    }else if(c == 3 || c == 4){
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
    std::list<qint32> Q;
    qDebug("radius = %d", radius);
    qDebug("size = %d", size);
    qDebug("channels = %d", c);
    if (c == 1){
        cv::Mat tmp;
        cv::copyMakeBorder(src, tmp, radius, radius, radius, radius, cv::BORDER_REPLICATE);
        for(qint32 i = 0; i < h; i++){
            Q.clear();
            for(qint32 j = 0; j < w + 2 * radius; j++){
                if (j >= size){
                    dst.at<uchar>(i, j - size) = tmp.at<uchar>(i + radius, Q.front());
                }

                while (!Q.empty()) {
                    const auto tail = tmp.at<uchar>(i + radius, Q.back());
                    if (tmp.at<uchar>(i + radius, j) > tail){
                        Q.pop_back();
                    }else{
                        break;
                    }
                }

                Q.emplace_back(j);
                if (j - Q.front() == size){
                    Q.pop_front();
                }
            }

            dst.at<uchar>(i, w - 1) = tmp.at<uchar>(i + radius, Q.front());
        }

        cv::copyMakeBorder(dst, tmp, radius, radius, radius, radius, cv::BORDER_REPLICATE);
        for(qint32 j = 0; j < w; j++){
            Q.clear();
            for(qint32 i = 0; i < h + 2 * radius; i++){
                if (i >= size){
                    dst.at<uchar>(i - size, j) = tmp.at<uchar>(Q.front(), j + radius);
                }

                while (!Q.empty()) {
                    const auto tail = tmp.at<uchar>(Q.back(), j + radius);
                    if (tmp.at<uchar>(i, j + radius) > tail){
                        Q.pop_back();
                    }else{
                        break;
                    }
                }

                Q.emplace_back(i);
                if (i - Q.front() == size){
                    Q.pop_front();
                }
            }

            dst.at<uchar>(h - 1, j) = tmp.at<uchar>(Q.front(), j);
        }
    }else{

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
    qint32 size = 2 * radius + 1;
    std::list<qint32> Q;
    cv::Mat dst(w, h, CV_8UC(c), cv::Scalar::all(255));
    if (c == 1){
        cv::Mat tmp;
        cv::copyMakeBorder(src, tmp, radius, radius, radius, radius, cv::BORDER_REPLICATE);
        for(qint32 i = 0; i < h; i++){
            Q.clear();
            for(qint32 j = 0; j < w + 2 * radius; j++){
                if (j >= size){
                    dst.at<uchar>(i, j - size) = tmp.at<uchar>(i + radius, Q.front());
                }

                while (!Q.empty()) {
                    const auto tail = tmp.at<uchar>(i + radius, Q.back());
                    if (tmp.at<uchar>(i + radius, j) < tail){
                        Q.pop_back();
                    }else{
                        break;
                    }
                }

                Q.emplace_back(j);
                if (j - Q.front() == size){
                    Q.pop_front();
                }
            }

            dst.at<uchar>(i, w - 1) = tmp.at<uchar>(i + radius, Q.front());
        }

        cv::copyMakeBorder(dst, tmp, radius, radius, radius, radius, cv::BORDER_REPLICATE);
        for(qint32 j = 0; j < w; j++){
            Q.clear();
            for(qint32 i = 0; i < h + 2 * radius; i++){
                if (i >= size){
                    dst.at<uchar>(i - size, j) = tmp.at<uchar>(Q.front(), j + radius);
                }

                while (!Q.empty()) {
                    const auto tail = tmp.at<uchar>(Q.back(), j + radius);
                    if (tmp.at<uchar>(i, j + radius) < tail){
                        Q.pop_back();
                    }else{
                        break;
                    }
                }

                Q.emplace_back(i);
                if (i - Q.front() == size){
                    Q.pop_front();
                }
            }

            dst.at<uchar>(h - 1, j) = tmp.at<uchar>(Q.front(), j);
        }
    }else{

    }

    qDebug("MINIMUM FILTER END");
    qDebug("--------------------------");
    return dst;
}
