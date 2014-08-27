#include "effects.h"
using namespace cv;

void Grayscale::apply(Mat& image)
{
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            Vec3b &pixel = image.at<Vec3b>(i, j);
            int c = (pixel.val[0] + pixel.val[1] + pixel.val[2]) / 3;
            pixel.val[0] = c;
            pixel.val[1] = c;
            pixel.val[2] = c;
        }
    }
}

void Sepia::apply(Mat& image)
{
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
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
        }
    }
}
