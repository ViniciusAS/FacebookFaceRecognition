
/* 
 * File:   VideoArea.cpp
 * Author: viniciusas
 * 
 * Created on 2 de Dezembro de 2016, 18:15
 */

#include "videoarea.h"

VideoArea::VideoArea() {
    
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &VideoArea::repaint), 10);
    
    set_size_request(100,100);
}

bool VideoArea::repaint(){
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(
            0, 0,
            get_allocation().get_width(),
            get_allocation().get_height()
        );
        win->invalidate_rect(r, false);
    }
    return true;
}

void VideoArea::setFrame(const cv::Mat &img){
    cv::Mat mat = img.clone();
    mHorizontal = (double) get_width() / (double) mat.cols;
    mVertical   = (double) get_height() / (double) mat.rows;
    cv::resize(
        mat, mat,
        cv::Size(get_width(),get_height()),
        1.0, 1.0,
        cv::INTER_CUBIC
    );
    if ( showEigenFaceImage ){
        cv::cvtColor(mat, mat, CV_BGR2GRAY);
        cv::equalizeHist( mat, mat );
        cv::cvtColor(mat, mat, CV_GRAY2RGB);
    } else {
        cv::cvtColor(mat, mat, CV_BGR2RGB);
    }
    cv::flip(mat,mat,1);
    this->frame = mat;
}

void VideoArea::setFaces(const std::vector<cv::Rect>& faces){
    std::vector<Rectangle> rects(faces.size());
    Rectangle r;
    for (cv::Rect f : faces){
        // conversion to area size
        r.x = (double) f.x * mHorizontal;
        r.y = (double) f.y * mVertical;
        r.widht = (double) f.width * mHorizontal;
        r.height = (double) f.height * mVertical;
        // flip
        r.x = (double) get_width() - r.x - r.widht;
        // push
        rects.push_back(r);
    }
    facesRects = rects;
}


void VideoArea::setShowEigenFaceImage(bool t){
    showEigenFaceImage = t;
}
bool VideoArea::getShowEigenFaceImage(){
    return showEigenFaceImage;
}
void VideoArea::toggleShowEigenFaceImage(){
    showEigenFaceImage = !showEigenFaceImage;
}

bool VideoArea::on_draw (const Cairo::RefPtr<Cairo::Context> &cr)
{
    cv::Mat frame = this->frame;
    if ( frame.empty() ){
        return false;
    }
    // image
    Gdk::Cairo::set_source_pixbuf (cr, Gdk::Pixbuf::create_from_data(
        frame.data,
        Gdk::COLORSPACE_RGB,
        false, 8,
        frame.cols, frame.rows,
        frame.step
    ));
    cr->rectangle(0,0,get_width(),get_height());
    cr->fill();
    // faces
    std::vector<Rectangle> faces = this->facesRects;
    for (Rectangle face : faces){
        cr->set_source_rgb(0.0, 0.0, 0.0);
        // top left
        cr->move_to( face.x, face.y );
        // top right
        cr->line_to(
            face.x + face.widht,
            face.y
        );
        // bottom right
        cr->line_to(
            face.x + face.widht,
            face.y + face.height
        );
        // bottom left
        cr->line_to(
            face.x,
            face.y + face.height
        );
        // top left
        cr->line_to( face.x, face.y );
    }
    cr->stroke();
    return true;
}

