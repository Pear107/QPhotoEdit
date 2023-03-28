#ifndef ROTATE_IMG_H
#define ROTATE_IMG_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define LEFT 0
#define RIGHT 1

namespace algorithm{
cv::Mat rotateLeft(cv::Mat&);
cv::Mat rotateRight(cv::Mat&);
}

#endif // ROTATE_IMG_H
