
/* 
 * File:   FaceRecognizer.h
 * Author: viniciusas
 *
 * Created on 30 de Novembro de 2016, 13:28
 */

#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
using namespace cv;

class FaceRecognizer {
public:
    FaceRecognizer();
    void recognize(Mat &face);
private:
    const int num_components = 80;
    const double threshold = DBL_MAX;
    Ptr<face::FaceRecognizer> recognizer;
};

#endif /* FACERECOGNIZER_H */

