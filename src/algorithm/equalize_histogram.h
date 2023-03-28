#ifndef EQUALIZE_HISTOGRAM_H
#define EQUALIZE_HISTOGRAM_H

#include <QDebug>
#include <opencv2/opencv.hpp>

namespace algorithm{
    cv::Mat equlizeHistogram(cv::Mat&);
}

#endif // EQUALIZE_HISTOGRAM_H
