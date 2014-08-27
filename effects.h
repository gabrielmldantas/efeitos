#ifndef __EFFECTS_H__
#define __EFFECTS_H__ 1

#include <opencv2/core/core.hpp>

class Effect
{
public:
    virtual void apply(cv::Mat& image) = 0;
};

class Grayscale : public Effect
{
public:
    void apply(cv::Mat& image);
};

class Sepia : public Effect
{
    void apply(cv::Mat& image);
};
#endif
