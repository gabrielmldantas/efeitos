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
