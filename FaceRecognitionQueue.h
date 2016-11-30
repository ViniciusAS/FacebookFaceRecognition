
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

#include "FaceRecognizer.h"

class FaceRecognitionQueue {
    
public:
    FaceRecognitionQueue();
    ~FaceRecognitionQueue();
    
    bool start();
    bool start(const int &nThreads);
    void finish();
    
    void addToQueue(const vector<Mat> &faces);
    
    unsigned getNThreads();
    
    bool isRunning();
    
    
    void lockQueue();
    void unlockQueue();
    bool keepRunning();
    Mat pop();
    
    FaceRecognizer getRecognizer();
    
    
private:

    FaceRecognizer *faceRecognizer;
    
    queue<Mat> facesQueue; 
    mutex queueMTX;
    
    thread *threads;
    unsigned nThreads;
    
    bool running = true;

};

#endif /* FACERECOGNITION_H */

