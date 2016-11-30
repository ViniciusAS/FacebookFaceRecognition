/* 
 * File:   FaceRecognition.cpp
 * Author: viniciusas
 * 
 * Created on 27 de Novembro de 2016, 21:15
 */

#include "FaceRecognitionQueue.h"

#include "recognition_task.h"
#include "tasksMutex.h"

FaceRecognitionQueue::FaceRecognitionQueue() {
    threads = NULL;
    nThreads = 0;
    faceRecognizer = new FaceRecognizer();
}
FaceRecognitionQueue::~FaceRecognitionQueue() {
    delete faceRecognizer;
}


bool FaceRecognitionQueue::start(){
    return this->start( std::thread::hardware_concurrency()-1 );
}

bool FaceRecognitionQueue::start(const int &nThreads){
    this->nThreads = nThreads;
    threads = new thread[nThreads];
    if ( threads == NULL | nThreads == 0 ){
        return false;
    }
    for (int i = 0; i < nThreads; i++) {
        thread &t = threads[i];
        t = thread( RecognitionTask( *this ) );
    }
    return true;
}

void FaceRecognitionQueue::finish() {
    running = false;
    for (int i = 0; i < nThreads; i++) {
        TasksMutex::condition.notify_one();
    }
    for (int i = 0; i < nThreads; i++) {
        thread &t = threads[i];
        t.join();
    }
}

bool FaceRecognitionQueue::keepRunning(){
    return ( facesQueue.size() > 0 );
}
Mat FaceRecognitionQueue::pop(){
    Mat face = facesQueue.front();
    facesQueue.pop();
    return face;
}

void FaceRecognitionQueue::addToQueue(const vector<Mat> &faces){
    for (const Mat &face : faces){
        queueMTX.lock();
        facesQueue.push(face);
        queueMTX.unlock();
        TasksMutex::condition.notify_one();
    }
}


FaceRecognizer FaceRecognitionQueue::getRecognizer() {
    return *faceRecognizer;
}


unsigned FaceRecognitionQueue::getNThreads(){
    return nThreads;
}
bool FaceRecognitionQueue::isRunning(){
    return running;
}

void FaceRecognitionQueue::lockQueue(){
    queueMTX.lock();
}
void FaceRecognitionQueue::unlockQueue(){
    queueMTX.unlock();
}