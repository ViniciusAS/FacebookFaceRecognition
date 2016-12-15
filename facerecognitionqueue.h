
/* 
 * File:   FaceRecognition.h
 * Author: viniciusas
 *
 * Created on 27 de Novembro de 2016, 21:15
 */

#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <cstdlib>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

#include <opencv2/core.hpp>
using namespace cv;

#include "facerecognizer.h"
#include "recognizedfaceslist.h"
#include "queueface.h"

class FaceRecognitionQueue {
    
public:

    FaceRecognitionQueue(RecognizedFacesList *recognizedList);
    bool init(FaceRecognizer::InitType initType);
    
    bool start();
    bool start(const unsigned &nThreads);
    void finish();
    
    void addToQueue( cv::Mat &original, std::vector<cv::Rect> facesRect, const vector<Mat> &faces );
    
    unsigned getNThreads();
    
    bool isRunning();
    
    
    void lockQueue();
    void unlockQueue();
    bool keepRunning();
    QueueFace pop();
    
    FaceRecognizer getRecognizer();

private:
    FaceRecognizer faceRecognizer;
    queue<QueueFace> facesQueue;
    mutex queueMTX;
    
    thread *threads;
    unsigned nThreads;
    
    bool running = true;

};

#endif /* FACERECOGNITION_H */

