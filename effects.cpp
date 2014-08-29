#include "effects.h"
#include <cstdlib>
using namespace cv;
using namespace std;

void Effect::traverse(cv::Mat& image, function<void(Mat&, int, int)> transformation)
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

void Sepia::apply(Mat& image)
{
    auto f = [](Mat& image, int i, int j) {
        Vec3b &pixel = image.at<Vec3b>(i, j);
        int red = pixel.val[2] * 0.393 + pixel.val[1] * 0.769 + pixel.val[0] * 0.189;
        int green = pixel.val[2] * 0.349 + pixel.val[1] * 0.686 + pixel.val[0] * 0.168;
        int blue = pixel.val[2] * 0.272 + pixel.val[1] * 0.534 + pixel.val[0] * 0.131;
        if (red > 255) red = 255;
        if (green > 255) green = 255;
        if (blue > 255) blue = 255;
        pixel.val[0] = blue;
        pixel.val[1] = green;
        pixel.val[2] = red;
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
