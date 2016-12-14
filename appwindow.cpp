
/* 
 * File:   AppWindow.cpp
 * Author: viniciusas
 * 
 * Created on 2 de Dezembro de 2016, 14:35
 */
#include "objectdetector.h"
#include "appwindow.h"

AppWindow::AppWindow()
    :
    detectionThread(
        [&](AppWindow *appWindow){
            appWindow->detectFacesThread();
        },
        this
    ),
    container( Gtk::ORIENTATION_HORIZONTAL, 0 )
{

    set_title("Face Recognition App");
    set_default_size(800,600);

    container.pack_start(videoArea,Gtk::PACK_EXPAND_WIDGET,0);
    container.pack_end(recognizedFaces,Gtk::PACK_SHRINK,0);

    add(container);

    recognizedFaces.addFace("teste 0");
    show_all_children(true);

    recognizedFaces.addFace("teste 1");
    recognizedFaces.addFace("teste 2");

    signal_key_release_event().connect( [&](GdkEventKey *e) -> bool{
        if (e->keyval == GDK_KEY_E || e->keyval == GDK_KEY_e){
            videoArea.toggleShowEigenFaceImage();
        }
        return true;
    });
    add_events(Gdk::KEY_RELEASE_MASK);
}

void AppWindow::detectFacesThread(){
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    printf("Initializing face recognition\n");
    if ( !recognitionQueue.init(FaceRecognizer::InitType::LOAD) ){
        printf("Failed to initialize face recognition\n");
        exit(EXIT_FAILURE);
    }
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
