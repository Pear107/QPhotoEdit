#include "equalize_histogram.h"

cv::Mat utils::equlizeHistogram(cv::Mat& src){
    qint32 h = src.rows, w = src.cols, c = src.channels();
    double size = static_cast<double>(h * w);
    cv::Mat dst(h, w, CV_8UC(c), cv::Scalar::all(0));
    if(c == 1){
        QVector<double> v(256, 0);
        for(qint32 i = 0; i < h; i++){
            uchar* ptr = src.ptr<uchar>(i);
            for(qint32 j = 0; j < w; j++){
                v[ptr[j]]++;
            }
        }

        printf("%s", "u");
        QVector<double> u(256, 0);
        for(qint32 i = 0; i < 256; i++){
            u[i] = (v[i] / size);
        }

        printf("%s", "x");
        QVector<double> x(256, 0);
        x[0] = u[0];
        for(qint32 i = 1; i < 256; i++){
            x[i] = x[i - 1] + u[i];
        }

        QVector<uchar> y(256, 0);
        for(qint32 i = 0; i < 256; i++){
            y[i] = std::round(255.0 * x[i]);
        }

        for(qint32 i = 0; i < h; i++){
            for(qint32 j = 0; j < w; j++){
                dst.at<uchar>(i,j) = y[src.at<uchar>(i, j)];
            }
        }
    }else if(c == 3){
        QVector<QVector<double>> v(3, QVector<double>(256, 0));
        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                v[0][ptr[j][0]]++;
                v[1][ptr[j][1]]++;
                v[2][ptr[j][2]]++;
            }
        }

        QVector<QVector<double>> u(3, QVector<double>(256, 0));
        for(qint32 i = 0; i < 256; i++){
            u[0][i] = v[0][i] / size;
            u[1][i] = v[1][i] / size;
            u[2][i] = v[2][i] / size;
        }

        QVector<QVector<double>> x(3, QVector<double>(256, 0));
        x[0][0] = u[0][0];
        x[1][0] = u[1][0];
        x[2][0] = u[2][0];
        for(qint32 i = 1; i < 256; i++){
            x[0][i] = x[0][i - 1] + u[0][i];
            x[1][i] = x[1][i - 1] + u[1][i];
            x[2][i] = x[2][i - 1] + u[2][i];
        }

        QVector<QVector<uchar>> y(3, QVector<uchar>(256, 0));
        for(qint32 i = 1; i < 256; i++){
            y[0][i] = std::round(255.0 * x[0][i]);
            y[1][i] = std::round(255.0 * x[1][i]);
            y[2][i] = std::round(255.0 * x[2][i]);
        }

        for(qint32 i = 0; i < h; i++){
            cv::Vec3b* ptr = src.ptr<cv::Vec3b>(i);
            cv::Vec3b* qtr = dst.ptr<cv::Vec3b>(i);
            for(qint32 j = 0; j < w; j++){
                qtr[j][0] = y[0][ptr[j][0]];
                qtr[j][1] = y[1][ptr[j][1]];
                qtr[j][2] = y[2][ptr[j][2]];
            }
        }
    }else if(c == 4){
        QVector<QVector<double>> v(4, QVector<double>(256, 0));
        for(qint32 i = 0; i < h; i++){
            for(qint32 j = 0; j < w; j++){
                v[0][src.at<cv::Vec4b>(i, j)[0]]++;
                v[1][src.at<cv::Vec4b>(i, j)[1]]++;
                v[2][src.at<cv::Vec4b>(i, j)[2]]++;
                v[3][src.at<cv::Vec4b>(i, j)[3]]++;
            }
        }

        QVector<QVector<double>> u(4, QVector<double>(256, 0));
        for(qint32 i = 0; i < 256; i++){
            u[0][i] = v[0][i] / size;
            u[1][i] = v[1][i] / size;
            u[2][i] = v[2][i] / size;
            u[3][i] = v[3][i] / size;
        }

        QVector<QVector<double>> x(3, QVector<double>(256, 0));
        x[0][0] = u[0][0];
        x[1][0] = u[1][0];
        x[2][0] = u[2][0];
        x[2][0] = u[3][0];
        for(qint32 i = 1; i < 256; i++){
            x[0][i] = x[0][i - 1] + u[0][i];
            x[1][i] = x[1][i - 1] + u[1][i];
            x[2][i] = x[2][i - 1] + u[2][i];
            x[3][i] = x[3][i - 1] + u[3][i];
        }

        QVector<QVector<uchar>> y(3, QVector<uchar>(256, 0));
        for(qint32 i = 1; i < 256; i++){
            y[0][i] = std::round(255.0 * x[0][i]);
            y[1][i] = std::round(255.0 * x[1][i]);
            y[2][i] = std::round(255.0 * x[2][i]);
            y[3][i] = std::round(255.0 * x[3][i]);
        }

        for(qint32 i = 0; i < h; i++){
            for(qint32 j = 0; j < w; j++){
                dst.at<cv::Vec3b>(i, j)[0] = y[0][src.at<cv::Vec3b>(i, j)[0]];
                dst.at<cv::Vec3b>(i, j)[1] = y[1][src.at<cv::Vec3b>(i, j)[1]];
                dst.at<cv::Vec3b>(i, j)[2] = y[2][src.at<cv::Vec3b>(i, j)[2]];
                dst.at<cv::Vec3b>(i, j)[3] = y[3][src.at<cv::Vec3b>(i, j)[3]];
            }
        }
    }

    return dst;
}

//cv::Mat yuv;
//cv::cvtColor(src, yuv, cv::COLOR_RGB2YUV);
//std::vector<int> v(256, 0);
//for(int i = 0; i < h; i++){
//    for(int j = 0; j < w; j++){
//        v[yuv.at<cv::Vec3b>(i, j)[0]]++;
//    }
//}
//std::vector<double> u(256, 0);
//for(int i = 0; i < 256; i++){
//    u[i] = (v[i] / sum);
//}
//std::vector<double> x(256, 0);
//x[0] = u[0];
//for(int i = 1; i < 256; i++){
//    x[i] = x[i - 1] + u[i];
//}
//std::vector<uchar> y(256, 0);
//for(int i = 1; i < 256; i++){
//    y[i] = (uchar) round((255 * x[i]));
//}
//for(int i = 0; i < h; i++){
//    for(int j = 0; j < w; j++){
//        yuv.at<cv::Vec3b>(i, j)[0] = y[yuv.at<cv::Vec3b>(i, j)[0]];
//    }
//}
//cv::cvtColor(yuv, dst, cv::COLOR_YUV2RGB);
