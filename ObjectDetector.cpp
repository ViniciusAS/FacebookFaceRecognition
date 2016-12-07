#include "ObjectDetector.h"

namespace ObjectDetector {
    
    CascadeClassifier face_cascade(Constants::defaultFaceDetection);
    
    void to_gray(const Mat &src, Mat &dst){
        // bgr to gray
        switch(src.channels()) {
        case 3:
            cv::cvtColor(src, dst, CV_BGR2GRAY);
            break;
        case 4:
            cv::cvtColor(src, dst, CV_BGRA2GRAY);
            break;
        default:
            src.copyTo(dst);
            break;
        }
    }

    vector<Rect> detectFaces(const Mat &frame, Mat &frame_gray, bool deep){

        vector<Rect> faces;
        
        to_gray(frame,frame_gray);
        
        // Equalizes the histogram of a grayscale image.
        cv::equalizeHist( frame_gray, frame_gray );

        double scaleFactor = ( deep ? Constants::deepScaleFactor : Constants::scaleFactor  );
        
        int flag = ( deep ? CASCADE_SCALE_IMAGE : CV_HAAR_DO_CANNY_PRUNING );
        // detect faces
        face_cascade.detectMultiScale(frame_gray, faces, scaleFactor, 2, flag ); // 0|CASCADE_SCALE_IMAGE , Size(30,30)

        return faces;
    }
    
    void detectFaces(const Mat &frame, vector<Rect> &faces, vector<Mat> &matFaces){
        
        Mat frame_gray;
        
        faces = detectFaces(frame,frame_gray,false);
        
        // crop images from original and insert into the vector
        for (const Rect &face : faces){
            matFaces.push_back( frame_gray( face ) );
        }
    }
    
    vector<Rect> detectFaces(const Mat &frame){
        Mat frame_gray;
        return detectFaces( frame, frame_gray, false );
    }
    
    vector<Rect> deepDetectFaces(const Mat &frame){
        Mat frame_gray;
        return detectFaces( frame, frame_gray, true );
    }
    
}

