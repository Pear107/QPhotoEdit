#ifndef FILTER_H
#define FILTER_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define INVERT_FILTER 0
#define DECOLORI_FILTER 1
#define NOSTALGIZ_FILTER 2
#define CAST_FILTER 3
#define FREEZE_FILTER 4
#define COMIC_STRIP_FILTER 5
#define EXPOSURE_FILTER 6

namespace utils{
cv::Mat invertFilter(cv::Mat&);
cv::Mat decolorFilter(cv::Mat&);
cv::Mat nostalgiaFilter(cv::Mat&);
cv::Mat castFilter(cv::Mat&);
cv::Mat freezeFilter(cv::Mat&);
cv::Mat comicStripFilter(cv::Mat&);
cv::Mat exposureFilter(cv::Mat&);
}

#endif // FILTER_H
