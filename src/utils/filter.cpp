#include "filter.h"

cv::Mat utils::invertFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qtr[j] = 255 - ptr[j];
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qtr[j][0] = 255 - ptr[j][0];
                qtr[j][1] = 255 - ptr[j][1];
                qtr[j][2] = 255 - ptr[j][2];
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qtr[j][0] = 255 - ptr[j][0];
                qtr[j][1] = 255 - ptr[j][1];
                qtr[j][2] = 255 - ptr[j][2];
            }
        }
    }

    return dst;
}

cv::Mat utils::decolorFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 avg = (std::min(red, std::min(green, blue)) + std::max(red, std::max(green, blue))) / 2;
                qtr[j][0] = red;
                qtr[j][1] = green;
                qtr[j][2] = avg;
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 avg = (std::min(red, std::min(green, blue)) + std::max(red, std::max(green, blue))) / 2;
                qtr[j][0] = red;
                qtr[j][1] = green;
                qtr[j][2] = avg;
            }
        }
    }

    return dst;
}

cv::Mat utils::nostalgiaFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                double red = static_cast<double>(ptr[j][0]);
                double green = static_cast<double>(ptr[j][1]);
                double blue = static_cast<double>(ptr[j][2]);
                qint32 newRed = static_cast<qint32>(0.393 *  red + 0.769 * green + 0.189 * blue);
                qint32 newGreen = static_cast<qint32>(0.349 * red + 0.686 * green + 0.168 * blue);
                qint32 newBlue = static_cast<qint32>(0.272 * red + 0.534 * green + 0.131 * blue);
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                double red = static_cast<double>(ptr[j][0]);
                double green = static_cast<double>(ptr[j][1]);
                double blue = static_cast<double>(ptr[j][2]);
                qint32 newRed = static_cast<qint32>(0.393 *  red + 0.769 * green + 0.189 * blue);
                qint32 newGreen = static_cast<qint32>(0.349 * red + 0.686 * green + 0.168 * blue);
                qint32 newBlue = static_cast<qint32>(0.272 * red + 0.534 * green + 0.131 * blue);
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newBlue));
                qtr[j][2] = std::max(0, std::min(255, newGreen));
            }
        }
    }

    return dst;
}

cv::Mat utils::castFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = red * 128 / (blue + green + 1);
                qint32 newGreen = green * 128 / (red + blue + 1);
                qint32 newBlue = blue * 128 / (red + green + 1);
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = red * 128 / (blue + green + 1);
                qint32 newGreen = green * 128 / (red + blue + 1);
                qint32 newBlue = blue * 128 / (red + green + 1);
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }

    return dst;
}

cv::Mat utils::freezeFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = (red - blue - green) * 3 / 2;
                qint32 newGreen = (green - red - blue) * 3 / 2;
                qint32 newBlue = (blue - red - green) * 3 / 2;
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = (red - blue - green) * 3 / 2;
                qint32 newGreen = (green - red - blue) * 3 / 2;
                qint32 newBlue = (blue - red - green) * 3 / 2;
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }

    return dst;
}

cv::Mat utils::comicStripFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = std::abs(green - blue + green + red) * red / 256;
                qint32 newGreen = std::abs(blue - green + blue + red) * red / 256;
                qint32 newBlue =  std::abs(blue - green + blue + red) * green / 256;
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = ptr[j][0];
                qint32 green = ptr[j][1];
                qint32 blue = ptr[j][2];
                qint32 newRed = std::abs(green - blue + green + red) * red / 256;
                qint32 newGreen = std::abs(blue - green + blue + red) * red / 256;
                qint32 newBlue =  std::abs(blue - green + blue + red) * green / 256;
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }

    return dst;
}

cv::Mat utils::exposureFilter(cv::Mat& src){
    qint32 w = src.cols, h = src.rows;
    qint32 c = src.channels();
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = src.ptr<uchar>(i);
            uchar* qtr = dst.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 gray = static_cast<double>(ptr[j]);
                qint32 newGray = static_cast<qint32>(gray + gray * 1.2);
                qtr[j] = std::max(0, std::min(255, newGray));
            }
        }
    }else if(c == 3){
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = static_cast<double>(ptr[j][0]);
                qint32 green = static_cast<double>(ptr[j][1]);
                qint32 blue = static_cast<double>(ptr[j][2]);
                qint32 newRed = static_cast<qint32>(red + red * 1.2);
                qint32 newGreen = static_cast<qint32>(green + green * 1.2);
                qint32 newBlue = static_cast<qint32>(blue + blue * 1.2);
                qtr[j][0] = std::max(0, std::min(255, newRed));
                qtr[j][1] = std::max(0, std::min(255, newGreen));
                qtr[j][2] = std::max(0, std::min(255, newBlue));
            }
        }
    }else if(c == 4){
        for(qint32 i = 0; i < h; i++){
            cv::Vec4b* ptr = src.ptr<cv::Vec4b>(i);
            cv::Vec4b* qtr = dst.ptr<cv::Vec4b>(i);
            for(qint32 j = 0; j < w; j++){
                qint32 red = static_cast<double>(ptr[j][0]);
                qint32 green = static_cast<double>(ptr[j][1]);
                qint32 blue = static_cast<double>(ptr[j][2]);
                qint32 newRed = static_cast<qint32>(red + red * 1.2);
                qint32 newGreen = static_cast<qint32>(green + green * 1.2);
                qint32 newBlue = static_cast<qint32>(blue + blue * 1.2);
                qtr[j][0] = std::min(255, newRed);
                qtr[j][1] = std::min(255, newGreen);
                qtr[j][2] = std::min(255, newBlue);
            }
        }
    }

    return dst;
}
