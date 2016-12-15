#ifndef RECOGNIZEDFACESLISTBOX_H
#define RECOGNIZEDFACESLISTBOX_H

#include <opencv2/core.hpp>

#include <gtkmm/box.h>
#include <gtkmm/widget.h>
#include <gtkmm/scrolledwindow.h>

#include <glibmm/main.h>
#include <sigc++/functors/mem_fun.h>

#include <vector>
#include <mutex>
#include <thread>
#include "recognizedfacerow.h"

class RecognizedFacesList : public Gtk::ScrolledWindow
{
public:
    RecognizedFacesList();
    ~RecognizedFacesList();
    void addFace(cv::Mat &mat, Glib::ustring label);
private:
    Gtk::VBox box;

    std::mutex vecLock;
    std::vector<RecognizedFaceRow*> rowsAdded, rows;
    bool updateRecognized();
};

#endif // RECOGNIZEDFACESLISTBOX_H
