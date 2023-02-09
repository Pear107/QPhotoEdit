#ifndef TRANSFER_GRAYSCALE_H
#define TRANSFER_GRAYSCALE_H

#include <QDebug>
#include <opencv2/opencv.hpp>

namespace utils{
cv::Mat linearGrayTransfer(cv::Mat&, double, qint32);
}

#endif // TRANSFER_GRAYSCALE_H
