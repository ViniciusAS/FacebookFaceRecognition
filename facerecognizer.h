
/* 
 * File:   FaceRecognizer.h
 * Author: viniciusas
 *
 * Created on 30 de Novembro de 2016, 13:28
 */

#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <vector>
#include <map>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
using namespace cv;

class FaceRecognizer {
public:
    enum InitType { LOAD, TRAIN };
    
    FaceRecognizer();
    bool init(FaceRecognizer::InitType initType);
    void recognize(Mat &face);
    
private:
    const int num_components = 80;
    const double threshold = DBL_MAX;
    Ptr<face::FaceRecognizer> recognizer;
    
    int im_width = 0;
    int im_height = 0;
    const std::string imagesize_train_file = "./train/imagesize-train.yml";
    const std::string train_file = "./train/train.yml";
    const std::string labels_file = "./labels.csv";
    const std::string faces_file = "./faces.csv";
    void loadNamesFile();
    void loadFacesDatabaseFile();
    void normalizeImages();
    bool cropFace(Mat &image);
    
    vector<Mat> images;
    vector<int> labels;
    map<int,std::string> names;
    
};

#endif /* FACERECOGNIZER_H */

