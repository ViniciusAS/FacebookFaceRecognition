#ifndef QUEUEFACE_H
#define QUEUEFACE_H

#include <opencv2/core.hpp>

struct QueueFace {
    cv::Mat original;
    cv::Mat processed;
};


#endif // QUEUEFACE_H
