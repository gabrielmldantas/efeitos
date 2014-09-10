#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "effects.h"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture v("a.avi");
    Size size(v.get(CV_CAP_PROP_FRAME_WIDTH), v.get(CV_CAP_PROP_FRAME_HEIGHT));
    double fps = v.get(CV_CAP_PROP_FPS);
    VideoWriter w("a_proc.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size);

    Mat image;
    int frame = 0;
    Grayscale *grayScale = new Grayscale;
    FiltroMedia *media = new FiltroMedia(9);
    Threshold *threshold = new Threshold(80);
    Mat last;
    Mat laplace;
    while (v.read(image)) {
        frame++;
        if (frame < (17 * fps + 18)) {
            grayScale->apply(image);
        } else if (frame > (17 * fps + 18) && frame < (24 * fps)) {
            addWeighted(image, 1.5, last, 0.5, 0, image);
        } else if (frame > (32 * fps) && frame < (39 * fps)) {
            media->apply(image);
        } else if (frame > (41 * fps)) {
            threshold->apply(image);
        } else if (frame > (25 * fps) && frame < (31 * fps)) {
            Laplacian(image, laplace, CV_8U, 5);
            addWeighted(image, 1.0, laplace, -2.0, 0, image);
        }
        last = image.clone();
        w << image;
    }
    delete grayScale;
    delete media;
    delete threshold;
    return 0;
}
