#ifndef RECOGNIZEDFACESLISTBOX_H
#define RECOGNIZEDFACESLISTBOX_H

#include <gtkmm/box.h>
#include <gtkmm/widget.h>

#include <vector>

#include "recognizedfacerow.h"

class RecognizedFacesList : public Gtk::Box
{
public:
    RecognizedFacesList();
    void addFace(Glib::ustring label);
private:
    std::vector<RecognizedFaceRow> rows;
};

#endif // RECOGNIZEDFACESLISTBOX_H
