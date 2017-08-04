#include "recognizedfaceslist.h"

RecognizedFacesList::RecognizedFacesList()
{
    add(box);
    set_policy(Gtk::POLICY_NEVER,Gtk::POLICY_AUTOMATIC);

    box.set_spacing(4);
    box.property_margin() = 4;
    box.set_size_request( RecognizedFaceRow::width );

    Glib::signal_timeout().connect( sigc::mem_fun(*this, &RecognizedFacesList::updateRecognized), 120 );
}

RecognizedFacesList::~RecognizedFacesList()
{
    for (RecognizedFaceRow *&row : rowsAdded) {
        delete row;
    }
    for (RecognizedFaceRow *&row : rows) {
        delete row;
    }
}

bool RecognizedFacesList::updateRecognized(){
    for (RecognizedFaceRow *&row : rowsAdded) {
        box.remove(*row);
        delete row;
    }
    rowsAdded.clear();
    vecLock.lock();
    for (RecognizedFaceRow *&row : rows) {
        box.pack_start( *row, Gtk::PACK_SHRINK, 0 );
        rowsAdded.push_back( row );
        row->show_all();
    }
    rows.clear();
    vecLock.unlock();
    return true;
}

void RecognizedFacesList::addFace(cv::Mat &image, Glib::ustring label){
    vecLock.lock();
    rows.push_back( new RecognizedFaceRow(image,label) );
    vecLock.unlock();
}

