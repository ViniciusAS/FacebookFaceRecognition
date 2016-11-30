
/* 
 * File:   FaceRecognizer.cpp
 * Author: viniciusas
 * 
 * Created on 30 de Novembro de 2016, 13:28
 */

#include "FaceRecognizer.h"


FaceRecognizer::FaceRecognizer() {
    recognizer = face::createEigenFaceRecognizer( num_components, threshold );
}

int i = 0;
void FaceRecognizer::recognize(Mat &face) {
    printf("Recognizing a face: %d\n", ++i);
    
}

