#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "effects.h"
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture v("bsg.avi");
    Size size(v.get(CV_CAP_PROP_FRAME_WIDTH), v.get(CV_CAP_PROP_FRAME_HEIGHT));
    double fps = v.get(CV_CAP_PROP_FPS);
    VideoWriter w("bsg_proc.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size);

    Mat image;
    int frame = 0;
    Negative *negative = new Negative;
    Bright *bright = new Bright(3);
    Mat blurred;
    while (v.read(image)) {
        frame++;
        bright->apply(image);
        GaussianBlur(image, blurred, Size(5, 5), 0);
        addWeighted(image, 1.5, blurred, -0.5, 0, image);
        if (frame > (10 * fps) && frame < (25 * fps)) {
            negative->apply(image);
        }
        w << image;
    }
    delete negative;
    delete bright;
    return 0;
}
