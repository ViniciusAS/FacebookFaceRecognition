
/* 
 * File:   AppWindow.cpp
 * Author: viniciusas
 * 
 * Created on 2 de Dezembro de 2016, 14:35
 */
#include "ObjectDetector.h"
#include "AppWindow.h"

AppWindow::AppWindow()
    :
    detectionThread(
        [&](AppWindow *appWindow){
            appWindow->detectFacesThread();
        },
        this
    )
{
    set_title("Face Recognition App");
    set_default_size(800,600);
    
    add(videoArea);
    videoArea.show();
}

void AppWindow::detectFacesThread(){
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    printf("Initializing face recognition\n");
    recognitionQueue.init(FaceRecognizer::InitType::LOAD);
    if ( !recognitionQueue.start() ){
        printf("Failed to start face recognition consumer threads\n");
        exit(EXIT_FAILURE);
    }
    printf("Faces detection from camera started\n");
    while ( keepRunning ){
        // wait when there is nothing to pop
        if ( frames.size() == 0 ) {
            cond.wait( lock );
            continue;
        }
        // pop from queue
        cv::Mat image = frames.front();
        frames.pop();
        // detect image faces
        std::vector<cv::Rect> faces;
        std::vector<cv::Mat> matFaces;
        ObjectDetector::detectFaces(image, faces, matFaces);
        // send to gui
        videoArea.setFaces( faces );
        // queue to recognition
        recognitionQueue.addToQueue(matFaces);
    }
}

void AppWindow::finish(){
    keepRunning = false;
    cond.notify_one();
    detectionThread.join();
    recognitionQueue.finish();
}
void AppWindow::setFrame(const cv::Mat &image){
    frames.push(image);
    cond.notify_one();
    videoArea.setFrame(image.clone());
}