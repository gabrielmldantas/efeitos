#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture v("a.mp4");
    Size size(v.get(CV_CAP_PROP_FRAME_WIDTH), v.get(CV_CAP_PROP_FRAME_HEIGHT));
    double fps = v.get(CV_CAP_PROP_FPS);
    VideoWriter w("n.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, size);
    Mat image;
    while (v.read(image)) {
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                Vec3b &pixel = image.at<Vec3b>(i, j);
                int c = (pixel.val[0] + pixel.val[1] + pixel.val[2]) / 3;
                pixel.val[0] = c;
                pixel.val[1] = c;
                pixel.val[2] = c;
            }
        }
        w << image;
    }
    return 0;
}
