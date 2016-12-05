
/* 
 * File:   AppWindow.h
 * Author: viniciusas
 *
 * Created on 2 de Dezembro de 2016, 14:35
 */

#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/image.h>
#include <opencv2/core.hpp>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

#include "VideoArea.h"
#include "FaceRecognitionQueue.h"

class AppWindow : public Gtk::Window {
public:
    AppWindow();
    
    void setFrame(const cv::Mat &image);
    
    void finish();
private:
    VideoArea videoArea;
    FaceRecognitionQueue recognitionQueue;
    
    cv::Mat currentFrame;
    
    bool keepRunning = true;
    std::condition_variable cond;
    std::thread detectionThread;
    std::queue<cv::Mat> frames;
    void detectFacesThread();
};

#endif /* APPWINDOW_H */

