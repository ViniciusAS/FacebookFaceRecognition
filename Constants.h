
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

    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_eye.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_lefteye_2splits.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_righteye_2splits.xml";
    //
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalface_default.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalcatface.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalcatface_extended.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt.xml";
    const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt2.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_frontalface_alt_tree.xml";
    //
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_profileface.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_smile.xml";
    //
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_fullbody.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_lowerbody.xml";
    //const string faceCascadeFile = OpenCV_dir+"/haarcascades/haarcascade_upperbody.xml";

    const double scaleFactor = 1.8;

}


#endif /* CONSTANT_H */

