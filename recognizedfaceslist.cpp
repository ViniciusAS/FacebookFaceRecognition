#include "recognizedfaceslist.h"

RecognizedFacesList::RecognizedFacesList()
{
    add(box);
    set_policy(Gtk::POLICY_NEVER,Gtk::POLICY_AUTOMATIC);

    box.set_spacing(4);
    box.property_margin() = 4;
    box.set_size_request( RecognizedFaceRow::width );

    Glib::signal_timeout().connect( sigc::mem_fun(*this, &RecognizedFacesList::updateRecognized), 90 );
}

RecognizedFacesList::~RecognizedFacesList()
{
    for (RecognizedFaceRow *&row : rows){
        delete row;
    }
}

bool RecognizedFacesList::updateRecognized(){
    for (auto *row : rowsAdded){
        delete row;
    }
    rowsAdded.clear();
    vecLock.lock();
    for (auto *row : rows) {
        box.pack_start( *row, Gtk::PACK_SHRINK, 0 );
        rowsAdded.push_back(row);
    }
    rows.clear();
    vecLock.unlock();
    return true;
}

void RecognizedFacesList::addFace(cv::Mat &image, Glib::ustring label){
    RecognizedFaceRow *row = new RecognizedFaceRow(image,label);
    row->show_all();
    vecLock.lock();
    rows.push_back(row);
    vecLock.unlock();
}

