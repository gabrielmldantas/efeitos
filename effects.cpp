#include "effects.h"
#include <cstdlib>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

void Effect::traverse(Mat& image, std::function<void(Mat&, int, int)> transformation)
{
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            transformation(image, i, j);
        }
    }
}

void Grayscale::apply(Mat& image)
{
    auto f = [](Mat& image, int i, int j) {
        Vec3b &pixel = image.at<Vec3b>(i, j);
        int c = (pixel.val[0] + pixel.val[1] + pixel.val[2]) / 3;
        pixel.val[0] = c;
        pixel.val[1] = c;
        pixel.val[2] = c;
    };
    traverse(image, f);
}

void Negative::apply(Mat& image)
{
    auto f = [](Mat& image, int i, int j) {
        Vec3b& pixel = image.at<Vec3b>(i, j);
        pixel.val[0] = abs(pixel.val[0] - 255);
        pixel.val[1] = abs(pixel.val[1] - 255);
        pixel.val[2] = abs(pixel.val[2] - 255);
    };
    traverse(image, f);
}

Threshold::Threshold(int threshold)
    : _threshold(threshold)
{}

void Threshold::apply(Mat& image)
{
    auto f = [this](Mat& image, int i, int j) {
        Vec3b& pixel = image.at<Vec3b>(i, j);
        if (pixel.val[0] < _threshold) pixel.val[0] = 0;
        else pixel.val[0] = 255;
        if (pixel.val[1] < _threshold) pixel.val[1] = 0;
        else pixel.val[1] = 255;
        if (pixel.val[2] < _threshold) pixel.val[2] = 0;
        else pixel.val[2] = 255;
    };
    traverse(image, f);
}

FiltroMedia::FiltroMedia(int maskSize)
    : _maskSize(maskSize), _center(floor(maskSize / 2)), _multiplier(1 / (maskSize * maskSize))
{
}

void FiltroMedia::apply(Mat& image)
{
    auto f = [this](Mat& image, int i, int j) {
        Vec3b &pixel = image.at<Vec3b>(i, j);
        Size imageSize = image.size();
        Vec3f resultado(0, 0, 0);
        for (int k = i - _center; k <= i + _center; k++) {
            if (k < 0 || k >= imageSize.height) continue;
            for (int w = j - _center; w <= j + _center; w++) {
                if (w < 0 || w >= imageSize.width) continue;
                Vec3b& vizinho = image.at<Vec3b>(k, w);
                resultado.val[0] += vizinho.val[0];
                resultado.val[1] += vizinho.val[1];
                resultado.val[2] += vizinho.val[2]; 
            }
        }
        pixel.val[0] = saturate_cast<uchar>(resultado.val[0] * _multiplier);
        pixel.val[1] = saturate_cast<uchar>(resultado.val[1] * _multiplier);
        pixel.val[2] = saturate_cast<uchar>(resultado.val[2] * _multiplier);
    };
    traverse(image, f);
}

Bright::Bright(float factor)
    : _factor(factor)
{}

void Bright::apply(Mat& image)
{
    auto f = [this](Mat& image, int i, int j) {
        Vec3b &pixel = image.at<Vec3b>(i, j);
        pixel.val[0] = saturate_cast<uchar>(pixel.val[0] * _factor);
        pixel.val[1] = saturate_cast<uchar>(pixel.val[1] * _factor);
        pixel.val[2] = saturate_cast<uchar>(pixel.val[2] * _factor);
    };
    traverse(image, f);
}