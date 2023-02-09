#ifndef BINARIZE_H
#define BINARIZE_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define FIXED_THRESH 0
#define OSTU_THRESH 1
#define ADAPTIVE_THRESH 2

namespace utils{
cv::Mat fixedThresh(cv::Mat&, qint32);
cv::Mat ostuThresh(cv::Mat&);
cv::Mat adaptiveThresh(cv::Mat&, qint32, qint32);
}

#endif // BINARIZE_H
