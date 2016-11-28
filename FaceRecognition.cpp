/* 
 * File:   FaceRecognition.cpp
 * Author: viniciusas
 * 
 * Created on 27 de Novembro de 2016, 21:15
 */

#include "FaceRecognition.h"

#include "recognition_task.h"
#include "tasksMutex.h"

FaceRecognition::FaceRecognition() {
    threads = NULL;
    nThreads = 0;
}


bool FaceRecognition::start(){
    nThreads = std::thread::hardware_concurrency()-1;
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

void FaceRecognition::finish() {
    running = false;
    for (int i = 0; i < nThreads; i++) {
        TasksMutex::condition.notify_one();
    }
    for (int i = 0; i < nThreads; i++) {
        thread &t = threads[i];
        t.join();
    }
}

bool FaceRecognition::keepRunning(){
    return ( facesQueue.size() > 0 );
}
Mat FaceRecognition::pop(){
    Mat face = facesQueue.front();
    facesQueue.pop();
    return face;
}

void FaceRecognition::recognize(const vector<Mat> &faces){
    for (const Mat &face : faces){
        queueMTX.lock();
        facesQueue.push(face);
        queueMTX.unlock();
        TasksMutex::condition.notify_one();
    }
}

int i = 0;
void FaceRecognition::recognize(Mat &face){
    printf("Recognizing a face: %d; size: %lu\n", i++, facesQueue.size());
}


unsigned FaceRecognition::getNThreads(){
    return nThreads;
}
bool FaceRecognition::isRunning(){
    return running;
}

void FaceRecognition::lockQueue(){
    queueMTX.lock();
}
void FaceRecognition::unlockQueue(){
    queueMTX.unlock();
}