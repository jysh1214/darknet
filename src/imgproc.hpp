#ifndef IMGPROC_H
#define IMGPROC_H

#include "../include/image.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void rgb2bgr(Image& img)
{
    for(int i = 0; i < img.w*img.h; ++i){
        float swap = img.data[i];
        img.data[i] = img.data[i + img.w*img.h*2];
        img.data[i + img.w*img.h*2] = swap;
    }
}

Image cvMat2Image(Mat& src)
{
    int h = src.rows;
    int w = src.cols;
    int c = src.channels();
    Image image(h, w, c);

    uchar* data = (uchar*)src.data;
    int step = src.step;
    int i, j, k;
    for (i = 0; i < h; ++i) {
        for (k = 0; k < c; ++k) {
            for (j = 0; j < w; ++j)
                image.data[k*w*h + i*w + j] = data[i*step + j*c + k]/255.;
        }
    }
    if (image.c == 3) rgb2bgr(image);

    return image;
}

static Image readImage(string filename)
{
    Mat input = imread(filename.c_str());
    if (!input.data) {
        throw string("Cannot load image: " + filename);
    }
    Image img = cvMat2Image(input);

    return img;
}

#endif
