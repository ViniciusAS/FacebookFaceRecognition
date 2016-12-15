
/* 
 * File:   VideoArea.h
 * Author: viniciusas
 *
 * Created on 2 de Dezembro de 2016, 18:15
 */

#ifndef VIDEOAREA_H
#define VIDEOAREA_H

#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <gtkmm-3.0/gtkmm/drawingarea.h>

#include <gdkmm-3.0/gdkmm/general.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>

#include <glibmm-2.4/glibmm/refptr.h>
#include <glibmm-2.4/glibmm/main.h>

#include <cairomm-1.0/cairomm/surface.h>

class MatFrameArea : public Gtk::DrawingArea {
public:
    MatFrameArea();
    void setFrame(const cv::Mat &img);
    cv::Mat getFrame();
    void setFaces(const std::vector<cv::Rect> &faces);

    void setShowEigenFaceImage(bool t);
    bool getShowEigenFaceImage();
    void toggleShowEigenFaceImage();
    bool repaint();

protected:
    virtual bool on_draw (const Cairo::RefPtr<Cairo::Context> &cr);
private:
    bool showEigenFaceImage = false;

    struct Rectangle {
        double x, y;
        double widht, height;
    };
    
    cv::Mat frame;
    std::vector<Rectangle> facesRects;
    
    double mHorizontal = 0, mVertical = 0;
    
};

#endif /* VIDEOAREA_H */

