
/* 
 * File:   FaceRecognizer.cpp
 * Author: viniciusas
 * 
 * Created on 30 de Novembro de 2016, 13:28
 */

#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <stdlib.h>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <opencv2/objdetect.hpp>

#include "Constants.h"
#include "FaceRecognizer.h"


FaceRecognizer::FaceRecognizer() {
//    if (!face_cascade.load(Constants::faceCascadeFile)){
//        printf("Failed to load Cascade Classifier\n");
//        exit(EXIT_FAILURE);
//    }
    recognizer = face::createEigenFaceRecognizer( num_components, threshold );
    loadFacesDatabaseFile();
    if (images.size() == 0){
        printf("No image found in file\n");
        exit(EXIT_FAILURE);
    }
    normalizeImages();
    recognizer->train(images,labels);
}

std::vector<Rect> faces;
bool FaceRecognizer::cropFace(Mat &image){
//    faces.clear();
//    face_cascade.detectMultiScale(image, faces, Constants::scaleFactor, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
//    if ( faces.size() == 0 ){
//        return false;
//    }
//    if ( faces.size() > 1 ){
//        printf("Warning: 2 faces in one, using the first one\n");
//    }
//    image = image(faces[0]);
    return true;
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

void FaceRecognizer::normalizeImages(){
    for (Mat &image:  images){
        if (!cropFace(image)){
            return;
        }
        equalizeHist(image,image);
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

int i = 0;
void FaceRecognizer::recognize(Mat &face) {
    //printf("Recognizing a face: %d\n", ++i);
    if (!cropFace(face)){
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
    if ( confidence < 26'000 )
        printf( "Predicted face: %d, confidence: %f\n", prediction, confidence );
}

