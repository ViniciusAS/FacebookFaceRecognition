
/* 
 * File:   FaceRecognizer.h
 * Author: viniciusas
 *
 * Created on 30 de Novembro de 2016, 13:28
 */

#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <vector>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
using namespace cv;

class FaceRecognizer {
public:
    FaceRecognizer();
    void init();
    void recognize(Mat &face);
private:
    const int num_components = 80;
    const double threshold = DBL_MAX;
    Ptr<face::FaceRecognizer> recognizer;
    
    int im_width = 0;
    int im_height = 0;
    const std::string faces_file = "./faces.csv";
    void loadFacesDatabaseFile();
    void normalizeImages();
    bool cropFace(Mat &image);
    
    vector<Mat> images;
    vector<int> labels;
    
};

#endif /* FACERECOGNIZER_H */

