#ifndef RECOGNIZEDFACEROW_H
#define RECOGNIZEDFACEROW_H

#include <opencv2/core.hpp>

#include <gtkmm/widget.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/box.h>

#include <glibmm/ustring.h>

#include <pangomm/fontdescription.h>

#include "matframearea.h"

class RecognizedFaceRow : public Gtk::HBox
{
public:
    static const int width = 300;
    RecognizedFaceRow(cv::Mat &image, Glib::ustring lbl);
private:
    void init();
    MatFrameArea image;
    Gtk::Label label;
};

#endif // RECOGNIZEDFACEROW_H
