
/* 
 * File:   AppWindow.h
 * Author: viniciusas
 *
 * Created on 2 de Dezembro de 2016, 14:35
 */

#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>

#include <sigc++/functors/ptr_fun.h>

#include <gdkmm/event.h>

#include <opencv2/core.hpp>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

#include "matframearea.h"
#include "facerecognitionqueue.h"
#include "recognizedfaceslist.h"

class AppWindow : public Gtk::Window {
public:
    AppWindow();
    
    void setFrame(const cv::Mat &image);
    
    void finish();
private:
    Gtk::Box container;
    MatFrameArea videoArea;
    RecognizedFacesList recognizedFaces;

    FaceRecognitionQueue recognitionQueue;
    
    cv::Mat currentFrame;
    
    bool keepRunning = true;
    std::condition_variable cond;
    std::thread detectionThread;
    std::queue<cv::Mat> frames;
    void detectFacesThread();
};

#endif /* APPWINDOW_H */

