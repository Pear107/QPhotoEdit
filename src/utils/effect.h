#ifndef EFFECT_H
#define EFFECT_H

#include <QDebug>
#include <opencv2/opencv.hpp>

#define FROSTED_GLASS_EFFECT 0
#define RELIEF_EFFECT 1
#define OIL_PAINTING_EFFECT 2
#define MOSAIC_EFFECT 3
#define SKETCH_EFFECT 4
#define FLEETING_TIME_EFFECT 5

namespace utils{
cv::Mat frostedGlassEffect(cv::Mat&);
cv::Mat reliefEffect(cv::Mat&);
cv::Mat oilPaintingEffect(cv::Mat&);
cv::Mat mosaicEffect(cv::Mat&);
cv::Mat sketchEffect(cv::Mat&);
cv::Mat fleetingTimeEffect(cv::Mat&);
}

#endif // EFFECT_H
