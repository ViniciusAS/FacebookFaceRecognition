#ifndef OBJECT_DETECTOR_H
#define OBJECT_DETECTOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
using namespace cv;
#include <vector>
using namespace std;
#include "Constants.h"

namespace ObjectDetector {
    
    void to_gray(const Mat &src, Mat &dst);
    
    void detectFaces(const Mat &frame, vector<Rect> &faces, vector<Mat> &matFaces);
    
    vector<Rect> detectFaces(const Mat &frame);
    
    vector<Rect> roughDetectFaces(const Mat &frame);
    
}

#endif /* OBJECT_DETECTOR_H */