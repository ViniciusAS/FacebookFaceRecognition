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
#include <functional>
#include <exception>
#include <vector>
using namespace std;
#include "constants.h"
#include "objectdetector.h"
#include "csv_handler.h"
#include "facerecognizer.h"


FaceRecognizer::FaceRecognizer(){
}

FaceRecognizer::FaceRecognizer(RecognizedFacesList *recognizedList)
    : recognizedList(recognizedList)
{
}

bool FaceRecognizer::init(FaceRecognizer::InitType initType){
    recognizer = face::createEigenFaceRecognizer( num_components, threshold );
//    recognizer = face::createFisherFaceRecognizer( num_components, threshold );

    loadNamesFile();
    switch (initType){

        case InitType::LOAD:{
            printf("Loading train\n");
            ifstream f(train_file);
            if (f.good()) {
                try {
                    // get train image size
                    if (!CsvHandler::readCsvFile(imagesize_train_file,';',2,[this](string *values){
                        im_width = stoi(values[0]);
                        im_height = stoi(values[1]);
                    }))
                    { throw exception(); }
                    // load train
                    recognizer->load(train_file);
                    break;
                } catch (exception &e){
                    printf("Error %s on attempt to load training\n", e.what());
                }
            } else {
                printf("Warning: File not found\n");
            }
        }
        case InitType::TRAIN:
            printf("Loading data\n");
            loadFacesDatabaseFile();
            if (images.size() == 0){
                printf("Error: No valid image found in file\n");
                return false;
            }
            normalizeImages();
            if (images.size() == 0){
                printf("Error: Normalized images error, no face recognized\n");
                return false;
            }
            printf("Traning\n");
            recognizer->train(images,labels);
            printf("Saving train to file\n");
            system("mkdir -p ./train/");
            recognizer->save(train_file);
            // save train image size
            vector<string*> values(1);
            values[0] = new string[2]{
                to_string(im_width),
                to_string(im_height)
            };
            CsvHandler::writeCsvFile(imagesize_train_file,';',2,values);
            break;
    }
    return true;
}

void FaceRecognizer::loadNamesFile(){
    printf("Loading names\n");
    if (!CsvHandler::readCsvFile(labels_file, ';', 2, [this](string *values)
    {
        names[stoi(values[0])] = values[1];
    })){
        printf("FATAL ERROR: CSV file %s not found\n", labels_file.c_str());
        exit(EXIT_FAILURE);
    }
}

void FaceRecognizer::loadFacesDatabaseFile(){
    printf("Loading faces\n");
    if (!CsvHandler::readCsvFile(faces_file, ';', 2, std::function<void(string*)>([this](string *values)
    {
        string &classlabel = values[0];
        string &path = values[1];
        if ( !path.empty() && !classlabel.empty() ) {
            images.push_back(imread(path,0));
            labels.push_back(stoi(classlabel.c_str()));
        }
    }))){
        printf("FATAL ERROR: CSV file %s not found\n", faces_file.c_str());
        exit(EXIT_FAILURE);
    }
}

std::vector<Rect> faces;
bool FaceRecognizer::cropFace(Mat &image){
    if (image.rows == 0 || image.cols == 0 || image.empty()){
        return false;
    }
    faces = ObjectDetector::detectFaces(image);
    if ( faces.size() == 0 ){
        std::printf("Warning: simple detect face did'nt work, using deep face detection\n");
        faces = ObjectDetector::deepDetectFaces(image);
    }
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

void FaceRecognizer::normalizeImages(){
    unsigned normalizeWarningCount = 0;
    for (long unsigned int i = 0; i < images.size(); i++){
        Mat &image = images[i];
        if ( !cropFace(image) ){
            std::printf(
                "Normalize warning #%d: Training image from label %d was invalid, removing from list\n",
                ++normalizeWarningCount, labels[i]
            );
            images.erase( images.begin()+i );
            labels.erase( labels.begin()+i );
            i--;
            continue;
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
        std::printf("Normalizing images %lu/%lu\n", i+1, images.size());
    }
}

void FaceRecognizer::recognize(QueueFace &face){
    if ( face.processed.rows == 0 || face.processed.cols == 0 || face.processed.empty() ){
        std::printf("FATAL ERROR: empty face mat\n");
        return;
    }
    cv::resize(
        face.processed, face.processed,
        cv::Size(im_width,im_height),
        1.0, 1.0,
        INTER_CUBIC
    );
    int prediction;
    double confidence;
    recognizer->predict(face.processed,prediction,confidence);
//    std::printf( "Predicted face: %d, confidence: %f, name: %s\n", prediction, confidence, names[prediction].c_str() );
    recognizedList->addFace(face.original,names[prediction].c_str());
}

