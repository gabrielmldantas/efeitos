#include <opencv2/highgui/highgui.hpp>
#include "effects.h"
#include <vector>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture v("a.mp4");
    Size size(v.get(CV_CAP_PROP_FRAME_WIDTH), v.get(CV_CAP_PROP_FRAME_HEIGHT));
    double fps = v.get(CV_CAP_PROP_FPS);
    VideoWriter w("n.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size);

    vector<Effect*> effects;
    effects.push_back(new Grayscale);
    effects.push_back(new Sepia);

    Mat image;
    while (v.read(image)) {
        for_each(effects.begin(), effects.end(), [&image](Effect* effect) { effect->apply(image); });
        w << image;
    }

    for_each(effects.begin(), effects.end(), [](Effect* e) { delete e; });
    return 0;
}
