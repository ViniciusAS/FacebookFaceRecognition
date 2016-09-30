package facerecognition.opencv;

import facebookfacerecognition.FaceRecognition;
import static facebookfacerecognition.FaceRecognition.mat2Image;
import java.util.Observable;
import javafx.animation.AnimationTimer;
import javafx.scene.image.Image;
import org.opencv.core.Mat;
import org.opencv.videoio.VideoCapture;

/**
 *
 * @author Vinicius Santos
 */
public class CameraSubject extends Observable implements Runnable {

    private Thread thread;
    
    private final AnimationTimer timer;
    
    private VideoCapture videoCapture;
    
    private Image image;
    private final Mat mat;
    
    public CameraSubject() {
        mat = new Mat();
        timer = new AnimationTimer() {
            @Override public void handle(long l)
            {
                captureImage();
            }
        };
    }
    
    protected void captureImage()
    {
        videoCapture.read(mat);   
        image = mat2Image(mat);
        this.setChanged();
        this.notifyObservers();
    }
    
    
    public void start(){
        thread = new Thread(this);
        thread.start();
    }
    
    @Override
    public void run(){
        videoCapture = FaceRecognition.newVideoCapture();
        timer.start();
    }
    
    public void stop(){
        timer.stop();
        videoCapture.release();
    }

    @Override
    public void notifyObservers() {
        super.notifyObservers();
    }
    
    public Image getImage(){
        return this.image;
    }
    
    public Mat getMat(){
        return this.mat;
    }
    
}
