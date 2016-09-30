package facebookfacerecognition;

import java.io.ByteArrayInputStream;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.List;
import javafx.animation.AnimationTimer;
import javafx.geometry.Rectangle2D;
import javafx.scene.image.Image;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfByte;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.objdetect.CascadeClassifier;
import org.opencv.videoio.VideoCapture;

/**
 *
 * @author Vinicius Santos
 */
public class FaceRecognition {

    private AnimationTimer timer;

    
    public static CascadeClassifier newCascadeClassifier(String filename){
        initOpenCV();
        CascadeClassifier cascadeClassifier = new CascadeClassifier();
        cascadeClassifier.load(filename);
        return cascadeClassifier;
    }
    
    public static List<Rectangle2D> detectFaces(CascadeClassifier cascadeClassifier, Mat mat) {

        MatOfRect faceDetections = new MatOfRect();
        cascadeClassifier.detectMultiScale( mat, faceDetections);

        System.out.println(String.format("Detected %s faces", faceDetections.toArray().length));

        List<Rectangle2D> rectList = new ArrayList<>();
        for (Rect rect : faceDetections.toArray()) {

            int x = rect.x;
            int y = rect.y;
            int w = rect.width;
            int h = rect.height;

            rectList.add(new Rectangle2D(x, y, w, h));
        }

        return rectList;
    }

    public static VideoCapture newVideoCapture() {
            
        setLibraryPath();

        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        VideoCapture videoCapture = new VideoCapture();
        videoCapture.open(0);

        return videoCapture;

    }
    
    public void startDetect(){
        new Thread(() -> {
            
            timer = new AnimationTimer() {

                Mat mat = new Mat();

                @Override
                public void handle(long now) {


                }
            };
            timer.start();
            
        }).start();
    }

    public static Image mat2Image(Mat mat) {
        MatOfByte buffer = new MatOfByte();
        Imgcodecs.imencode(".png", mat, buffer);
        return new Image(new ByteArrayInputStream(buffer.toArray()));
    }

    private static void initOpenCV(){
        setLibraryPath();
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }
    
    private static void setLibraryPath() {

        try {

            System.setProperty("java.library.path", "lib");

            Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
            fieldSysPath.setAccessible(true);
            fieldSysPath.set(null, null);

        } catch (Exception ex) {
            ex.printStackTrace();
            throw new RuntimeException(ex);
        }

    }
//
//    public static String getOpenCvResource(Class<?> clas, String path) {
//        try {
//            return Paths.get( clas.getResource(path).toURI()).toString();
//        } catch (URISyntaxException e) {
//            throw new RuntimeException(e);
//        }
//    }

    
}
