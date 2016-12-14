#include "recognizedfaceslist.h"

RecognizedFacesList::RecognizedFacesList()
{
    set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    set_spacing(3);
    property_margin() = 6;
}

void RecognizedFacesList::addFace(Glib::ustring label){
    rows.push_back(RecognizedFaceRow(label));
    this->pack_end( rows.back() );//, Gtk::PACK_EXPAND_PADDING, 3 );
    show_all_children();
}

