#ifndef RECOGNIZEDFACEROW_H
#define RECOGNIZEDFACEROW_H

#include <gtkmm/widget.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/box.h>

#include <glibmm/ustring.h>

class RecognizedFaceRow : public Gtk::Box
{
public:
    RecognizedFaceRow(Glib::ustring lbl);
    RecognizedFaceRow(const RecognizedFaceRow &recognizedFaceRow);
private:
    Gtk::Label label;
    struct {
        const int x = 80;
        const int y = 2;
    } size_request;
};

#endif // RECOGNIZEDFACEROW_H
