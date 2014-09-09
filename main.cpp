#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "effects.h"
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture v("a.avi");
    Size size(v.get(CV_CAP_PROP_FRAME_WIDTH), v.get(CV_CAP_PROP_FRAME_HEIGHT));
    double fps = v.get(CV_CAP_PROP_FPS);
    VideoWriter w("n.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size);
    vector<Effect*> effects;
    effects.push_back(new Bright(3));

    Mat image;
    int frame = 0;
    Grayscale *g = new Grayscale;
    FiltroMedia *media = new FiltroMedia(3);
    while (v.read(image)) {
        frame++;
        //for_each(effects.begin(), effects.end(), [&image](Effect* effect) { effect->apply(image); });
        if (frame < (17 * fps + 18)) {
            g->apply(image);
        } else if (frame > (32 * fps) && frame < (39 * fps)) {
            media->apply(image);
        }
        w << image;
    }

    for_each(effects.begin(), effects.end(), [](Effect* e) { delete e; });
    delete g;
    delete media;
    return 0;
}
