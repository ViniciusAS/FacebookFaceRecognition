/* 
 * File:   FaceRecognition.cpp
 * Author: viniciusas
 * 
 * Created on 27 de Novembro de 2016, 21:15
 */

#include "facerecognitionqueue.h"

#include "recognition_task_consumer.h"
#include "tasksmutex.h"

FaceRecognitionQueue::FaceRecognitionQueue() {
    threads = NULL;
    nThreads = 0;
}

bool FaceRecognitionQueue::init(FaceRecognizer::InitType initType){
    return faceRecognizer.init(initType);
}

bool FaceRecognitionQueue::start(){
    return this->start( std::thread::hardware_concurrency()-1 );
}

bool FaceRecognitionQueue::start(const unsigned &nThreads){
    this->nThreads = nThreads;
    threads = new thread[nThreads];
    if ( threads == NULL || nThreads == 0 ){
        return false;
    }
    for (unsigned i = 0; i < nThreads; i++) {
        thread &t = threads[i];
        t = thread( RecognitionTaskConsumer( *this ) );
    }
    return true;
}

void FaceRecognitionQueue::finish() {
    running = false;
    for (size_t i = 0; i < nThreads; i++) {
        TasksMutex::condition.notify_one();
    }
    for (size_t i = 0; i < nThreads; i++) {
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
    return faceRecognizer;
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
