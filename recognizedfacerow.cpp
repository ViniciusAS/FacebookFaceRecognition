#include "recognizedfacerow.h"

RecognizedFaceRow::RecognizedFaceRow(cv::Mat &image, Glib::ustring lbl)
    : label(lbl)
{
    this->image.setFrame(image);
    init();
}

void RecognizedFaceRow::init(){
    override_background_color(Gdk::RGBA("#EEEEEE"));
    set_size_request( width );
    set_spacing(0);
    label.override_font(Pango::FontDescription("arial,serif  18"));
    pack_start(image, Gtk::PACK_SHRINK, 0);
    pack_start(label, Gtk::PACK_EXPAND_PADDING, 0 );
}
