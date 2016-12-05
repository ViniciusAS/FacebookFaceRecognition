
/* 
 * File:   FaceRecognizer.cpp
 * Author: viniciusas
 * 
 * Created on 30 de Novembro de 2016, 13:28
 */

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Constants.h"
#include "ObjectDetector.h"
#include "FaceRecognizer.h"


FaceRecognizer::FaceRecognizer() {
    recognizer = face::createEigenFaceRecognizer( num_components, threshold );
}

void FaceRecognizer::init(){
    loadFacesDatabaseFile();
    if (images.size() == 0){
        printf("Error: No valid image found in file\n");
        exit(EXIT_FAILURE);
    }
    normalizeImages();
    if (images.size() == 0){
        printf("Error: Normalized images error, no face recognized\n");
        exit(EXIT_FAILURE);
    }
    recognizer->train(images,labels);    
}

void FaceRecognizer::loadFacesDatabaseFile(){
    ifstream file( faces_file, ifstream::in );
    if (!file){
        printf("CSV file of faces not found\n");
        exit(EXIT_FAILURE);
    }
    string line, path, classlabel;
    while ( std::getline(file,line) ){
        
        if ( line.empty() ) continue;
        if ( line.at(0) == '#' ) continue;
        
        std::stringstream sline(line);
        std::getline(sline, classlabel, ';');
        std::getline(sline, path);
        if ( !path.empty() && !classlabel.empty() ) {
            images.push_back(imread(path,0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

std::vector<Rect> faces;
bool FaceRecognizer::cropFace(Mat &image){
    if (image.rows == 0 | image.cols == 0 | image.empty()){
        return false;
    }
    faces = ObjectDetector::roughDetectFaces(image);
    if ( faces.size() == 0 ){
//        std::printf("Warning: no face found at image, using it anyway\n");
//        return true;
        return false;
    }
    unsigned bigger = 0;
    if ( faces.size() > 1 ){
        std::printf("Warning: %lu faces found in one image, using the bigger one\n",faces.size());
        unsigned area = 0;
        for (unsigned i = 0; i < faces.size(); i++){
            unsigned a = faces[0].width * faces[0].height;
            if ( a > area ) {
                area = a;
                bigger = i;
            }
        }
    }
    image = image(faces[bigger]);
    return true;
}

int normalizeWarningCount = 0;
void FaceRecognizer::normalizeImages(){
    for (long unsigned int i = 0; i < images.size(); i++){
        Mat &image = images[i];
        if ( !cropFace(image) ){
            std::printf(
                "Normalize warning #%d: Training image label %d was invalid, removing from list\n",
                ++normalizeWarningCount, labels[i]
            );
            images.erase( images.begin()+i );
            labels.erase( labels.begin()+i );
            normalizeImages();
            break;
        }
        ObjectDetector::to_gray(image,image);
        cv::equalizeHist(image,image);
        if ( im_width == 0 || im_height == 0 ){
            im_width  = image.cols;
            im_height = image.rows;
        } else {
            cv::resize(
                image, image,
                cv::Size(im_width,im_height),
                1.0, 1.0,
                INTER_CUBIC
            );
        }
    }
}

void FaceRecognizer::recognize(Mat &face){
    if ( face.rows == 0 | face.cols == 0 | face.empty() ){
        std::printf("FATAL ERROR: empty face mat\n");
        return;
    }
    cv::resize(
        face, face,
        cv::Size(im_width,im_height),
        1.0, 1.0,
        INTER_CUBIC
    );
    int prediction;
    double confidence;
    recognizer->predict(face,prediction,confidence);
    std::printf( "Predicted face: %d, confidence: %f\n", prediction, confidence );
}

