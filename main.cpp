/* 
 * File:   main.cpp
 * Author: viniciusas
 *
 * Created on 25/11/2016, 16:11
 */
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
using namespace cv;

#include "Constants.h"
#include "FaceRecognitionQueue.h"


FaceRecognitionQueue recognition;
VideoCapture capture;
CascadeClassifier face_cascade;


bool init(){
    
    if (!recognition.start()){
        printf("Failed to start face recognition threads\n");
        return false;
    }
    
    if (!face_cascade.load(Constants::faceCascadeFile)){
        printf("Failed to load face cascade classifier\n");
        return false;
    }
    
    capture.open( 0 );
    if (!capture.isOpened()){
        printf("Error opening video capture\n");
        return false;
    }
    
    return true;
}

std::vector<cv::Mat> detectAndDisplay(const Mat &frame);

int main(int argc, char** argv) {
    
    if ( !init() ){
        return -1;
    }
    
    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty()){
            printf("No captured frame");
            break;
        }

        const std::vector<Mat> faces = detectAndDisplay(frame);
        recognition.addToQueue(faces);
        
        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    capture.release();
    recognition.finish();
    
    return 0;
}

std::vector<cv::Mat> detectAndDisplay(const cv::Mat &frame){
    
    vector<Rect> faces;
    vector<Mat> matFaces;
    Mat frame_gray;
    
    cv::cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    
    cv::equalizeHist( frame_gray, frame_gray );
    
    face_cascade.detectMultiScale(frame_gray, faces, Constants::scaleFactor, 2, 0|CASCADE_SCALE_IMAGE, Size(30,30));
    
    for (const Rect &face : faces){
        cv::Point center( face.x+face.width/2, face.y+face.height/2 );
        cv::Size axes( face.width/2, face.height/2 );
        cv::ellipse( frame, center, axes, 0,0, 360, Scalar(0,0,0), 4, LINE_8, 0 );
        
        // the detected face
        matFaces.push_back( frame_gray( face ) );
    }
    cv::flip(frame,frame,1);
    cv::imshow("Capture - Face Detection",frame);
    
    return matFaces;
}