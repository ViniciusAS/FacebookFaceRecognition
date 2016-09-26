package facebookfacerecognition;

import java.io.ByteArrayInputStream;
import java.lang.reflect.Field;
import java.net.URISyntaxException;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import javafx.animation.AnimationTimer;
import javafx.geometry.Rectangle2D;
import javafx.scene.Group;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.Reflection;
import javafx.scene.image.Image;
import javafx.scene.paint.Color;
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
    
    private static FaceRecognition instance;
    public static FaceRecognition getInstance(){
        if (instance == null) {
            instance = new FaceRecognition( 500, 300 );
        }
        return instance;
    }
    
    private CascadeClassifier faceDetector;
    private VideoCapture videoCapture;

    private final Canvas canvas;
    private final GraphicsContext g2d;
    private AnimationTimer timer;

    private final Group group;
    
    public FaceRecognition(double width, double height) {

        initOpenCv();
        
        canvas = new Canvas( width, height );
        g2d = canvas.getGraphicsContext2D();
        g2d.setStroke(Color.GREEN);        
        
        group = new Group(canvas);
        
        startDetect();

    }

    public Group getNode(){
        return group;
    }
    
    public List<Rectangle2D> detectFaces(Mat mat) {

        MatOfRect faceDetections = new MatOfRect();
        faceDetector.detectMultiScale( mat, faceDetections);

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

    private void initOpenCv() {
            
        setLibraryPath();

        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);

        videoCapture = new VideoCapture();
        videoCapture.open(0);

        System.out.println("Camera open: " + videoCapture.isOpened());


//        faceDetector = new CascadeClassifier(getOpenCvResource(getClass(), "/opencv/data/lbpcascades/lbpcascade_frontalface.xml"));
        faceDetector = new CascadeClassifier();
        faceDetector.load( "./haarcascades/haarcascade_profileface.xml" );

    }
    
    public void startDetect(){
        new Thread(() -> {
            
            timer = new AnimationTimer() {

                Mat mat = new Mat();

                @Override
                public void handle(long now) {

                    final double w = 400;
                    final double h = 300;
                    
                    videoCapture.read(mat);
                    Image image = mat2Image(mat);
                    g2d.drawImage(image, 0, 0, w, h);
                    
                    long t = System.currentTimeMillis();
                    List<Rectangle2D> rectList = detectFaces(mat);

                    for (Rectangle2D rect : rectList) {
                        g2d.setFill(Color.GREEN);
                        g2d.strokeRect(
                            (w/image.getWidth()) * rect.getMinX(),
                            (h/image.getHeight()) * rect.getMinY(),
                            (w/image.getWidth()) * rect.getWidth(),
                            (h/image.getHeight()) * rect.getHeight()
                        );
                    }
                    t = System.currentTimeMillis()-t;
                    System.out.println("detection time: "+ t );

                }
            };
            timer.start();
            
        }).start();
    }
    
    public void stop(){
        timer.stop();
        videoCapture.release();
    }

    public static Image mat2Image(Mat mat) {
        MatOfByte buffer = new MatOfByte();
        Imgcodecs.imencode(".png", mat, buffer);
        return new Image(new ByteArrayInputStream(buffer.toArray()));
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

    public static String getOpenCvResource(Class<?> clas, String path) {
        try {
            return Paths.get( clas.getResource(path).toURI()).toString();
        } catch (URISyntaxException e) {
            throw new RuntimeException(e);
        }
    }

    
}
