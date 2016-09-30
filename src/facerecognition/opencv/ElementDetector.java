package facerecognition.opencv;

import facebookfacerecognition.FaceRecognition;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import javafx.geometry.Rectangle2D;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.objdetect.CascadeClassifier;

/**
 *
 * @author Vinicius Santos
 */
public class ElementDetector implements Runnable{

    private final CascadeClassifier cascadeClassifier;
    private Thread thread;
    private DetectionFinishedListener dfl;
    private Mat mat;
    
    public static enum Element {

        EYE, EYE_TREE_EYEGLASSES,
        EYELEFT_2SPLITS, EYERIGHT_2SPLITS, 
        
        FRONTAL_CAT_FACE, FRONTAL_CAT_FACE_EXTENDED,
        FRONTAL_FACE_DEFAULT, FRONTAL_FACE_ALT, FRONTAL_FACE_ALT2, FRONTAL_FACE_ALT_TREE,
        
        LICENCE_PLATE_RUS_16STAGES,
        RUSSIAN_PLATE_NUMBER,
        
        BODY_FULL, BODY_LOWER, BODY_UPPER,
        PROFILE_FACE, SMILE
    }
    
    public ElementDetector(Element element) {
        String el = null;
        switch (element) {
            case EYE:                        el = "./haarcascades/haarcascade_eye.xml"; break;
            case EYE_TREE_EYEGLASSES:        el = "./haarcascades/haarcascade_eye_tree_eyeglasses.xml"; break;
            case EYELEFT_2SPLITS:            el = "./haarcascades/haarcascade_lefteye_2splits.xml"; break;
            case EYERIGHT_2SPLITS:           el = "./haarcascades/haarcascade_righteye_2splits.xml"; break;
            case FRONTAL_CAT_FACE:           el = "./haarcascades/haarcascade_frontalcatface.xml"; break;
            case FRONTAL_CAT_FACE_EXTENDED:  el = "./haarcascades/haarcascade_frontalcatface_extended.xml"; break;
            case FRONTAL_FACE_DEFAULT:       el = "./haarcascades/haarcascade_frontalface_default.xml"; break;
            case FRONTAL_FACE_ALT:           el = "./haarcascades/haarcascade_frontalface_alt.xml"; break;
            case FRONTAL_FACE_ALT2:          el = "./haarcascades/haarcascade_frontalface_alt2.xml"; break;
            case FRONTAL_FACE_ALT_TREE:      el = "./haarcascades/haarcascade_frontalface_alt2.xml"; break;
            case LICENCE_PLATE_RUS_16STAGES: el = "./haarcascades/haarcascade_licence_plate_rus_16stages.xml"; break;
            case RUSSIAN_PLATE_NUMBER:       el = "./haarcascades/haarcascade_russian_plate_number.xml"; break;
            case BODY_FULL:                  el = "./haarcascades/haarcascade_fullbody.xml"; break;
            case BODY_LOWER:                 el = "./haarcascades/haarcascade_lowerbody.xml"; break;
            case BODY_UPPER:                 el = "./haarcascades/haarcascade_upperbody.xml"; break;
            case PROFILE_FACE:               el = "./haarcascades/haarcascade_profileface.xml"; break;
            case SMILE:                      el = "./haarcascades/haarcascade_smile.xml"; break;
            default: throw new IllegalArgumentException("Element not found");
        }
        cascadeClassifier = FaceRecognition.newCascadeClassifier(el);
    }
    
    public void detectPositions( Mat mat, DetectionFinishedListener dfl ) {
        if ( thread != null && thread.isAlive() )
        {
            return;
        }
        thread = new Thread(this);
        this.mat = mat;
        this.dfl = dfl;
        thread.start();
    }
    

    @Override
    public void run() {
        MatOfRect detections = new MatOfRect();
        cascadeClassifier.detectMultiScale( mat, detections);

        dfl.detectionFinished(
            Arrays.asList(detections.toArray())
        );
    }
    
    public interface DetectionFinishedListener {
        public void detectionFinished(List<Rect> rectList);
    }
    
}
