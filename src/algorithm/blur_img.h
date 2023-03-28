#ifndef BLUR_IMG_H
#define BLUR_IMG_H

#include <QDebug>
#include <opencv2/opencv.hpp>
#include <algorithm>

#define GAUSSIN_FILTER 0
#define LINEAR_MEAN_FILTER 1
#define MAXIUM_FILTER 2
#define MEDIAN_FILTER 3
#define MINIMUM_FILTER 4

namespace algorithm{
cv::Mat gaussianFilter(cv::Mat&, qint32, double);
cv::Mat linearMeanFilter(cv::Mat&, qint32);
cv::Mat maximumFilter(cv::Mat&, qint32);
cv::Mat medianFilter(cv::Mat&, qint32);
cv::Mat minimumFilter(cv::Mat&, qint32);
}

#endif // BLUR)IMG_H
