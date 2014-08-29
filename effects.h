#ifndef __EFFECTS_H__
#define __EFFECTS_H__ 1

#include <opencv2/core/core.hpp>
#include <functional>

class Effect
{
public:
    virtual void apply(cv::Mat& image) = 0;
protected:
    void traverse(cv::Mat& image, std::function<void(cv::Mat&, int, int)> transformation);
};

class Grayscale : public Effect
{
public:
    void apply(cv::Mat& image);
};

class Sepia : public Effect
{
public:
    void apply(cv::Mat& image);
};

class Negative : public Effect
{
public:
    void apply(cv::Mat& image);
};

class Threshold : public Effect
{
public:
    Threshold(int threshold);
    void apply(cv::Mat& image);
private:
    int _threshold;
};
#endif
