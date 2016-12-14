#include "recognizedfacerow.h"

RecognizedFaceRow::RecognizedFaceRow(Glib::ustring lbl)
    :
      label(lbl)
{
    set_size_request( size_request.x, size_request.y );
//    this->
    pack_start(label,Gtk::PACK_SHRINK,1);
}


RecognizedFaceRow::RecognizedFaceRow(const RecognizedFaceRow &recognizedFaceRow)
    : label(recognizedFaceRow.label.get_text())
{
    set_size_request( size_request.x, size_request.y );
    pack_start(label,Gtk::PACK_SHRINK,1);
}
