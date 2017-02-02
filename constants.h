
/* 
 * File:   Constant.h
 * Author: viniciusas
 *
 * Created on 1 de Dezembro de 2016, 15:38
 */

#ifndef CONSTANT_H
#define CONSTANT_H

#include <string>

namespace Constants {
    
    using namespace std;
    
    const string OpenCV_dir  = "/usr/local/share/OpenCV";

//    const string eye                 = OpenCV_dir+"/haarcascades/haarcascade_eye.xml";
//    const string eye_tree_eyeglasses = OpenCV_dir+"/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
//    const string lefteye_2splits     = OpenCV_dir+"/haarcascades/haarcascade_lefteye_2splits.xml";
//    const string righteye_2splits    = OpenCV_dir+"/haarcascades/haarcascade_righteye_2splits.xml";
    
    const string frontalface_default     = OpenCV_dir+"/haarcascades/haarcascade_frontalface_default.xml";
    const string frontalcatface          = OpenCV_dir+"/haarcascades/haarcascade_frontalcatface.xml";
    const string frontalcatface_extended = OpenCV_dir+"/haarcascades/haarcascade_frontalcatface_extended.xml";
    const string frontalface_alt         = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt.xml";
    const string frontalface_alt2        = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt2.xml";
    const string frontalface_alt_tree    = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt_tree.xml";
    
    const string profileface = OpenCV_dir+"/haarcascades/haarcascade_profileface.xml";
    const string smile       = OpenCV_dir+"/haarcascades/haarcascade_smile.xml";
    
//    const string fullbody  = OpenCV_dir+"/haarcascades/haarcascade_fullbody.xml";
//    const string lowerbody = OpenCV_dir+"/haarcascades/haarcascade_lowerbody.xml";
//    const string upperbody = OpenCV_dir+"/haarcascades/haarcascade_upperbody.xml";

    const string defaultFaceDetection = frontalface_alt2;
    
    const double scaleFactor = 1.9;
    const double deepScaleFactor = 1.1;

}


#endif /* CONSTANT_H */

