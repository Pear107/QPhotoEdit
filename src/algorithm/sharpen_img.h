#ifndef SHARPEN_IMG_H
#define SHARPEN_IMG_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define GRADS_OPERATOR 0
#define LAPLACE_OPERATOR 1
#define ROBERTS_OPERATOR 2
#define SOBEL_OPERATOR 3

namespace algorithm{
cv::Mat gradsOperator(cv::Mat&);
cv::Mat laplaceOperator(cv::Mat&);
cv::Mat robertsOperator(cv::Mat&);
cv::Mat sobelOperator(cv::Mat&);
}

#endif // SHARPEN_IMG_H
