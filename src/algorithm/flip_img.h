#ifndef FLIP_IMG_H
#define FLIP_IMG_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define HORIZONTALLY 0
#define VERTICALLY 1

namespace algorithm{
cv::Mat flipHorizontally(cv::Mat&);
cv::Mat flipVertically(cv::Mat&);
}

#endif // FLIP_IMG_H
