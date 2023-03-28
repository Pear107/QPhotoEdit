#ifndef CONVERT_COLOR_H
#define CONVERT_COLOR_H

#include <QDebug>
#include <opencv2/opencv.hpp>

namespace algorithm{
cv::Mat rgb2hsi(cv::Mat&);
cv::Mat rgb2cmyk(cv::Mat&);
cv::Mat rgb2gray(cv::Mat&);

cv::Mat hsi2rgb(cv::Mat&);
cv::Mat hsi2cmyk(cv::Mat&);
cv::Mat hsi2gray(cv::Mat&);

cv::Mat cmyk2Rgb(cv::Mat&);
cv::Mat cmyk2Hsi(cv::Mat&);
cv::Mat cmyk2Gray(cv::Mat&);

cv::Mat gray2rgb(cv::Mat&);
cv::Mat gray2hsi(cv::Mat&);
cv::Mat gray2cmyk(cv::Mat&);
}

#endif // CONVERT_COLOR_H
