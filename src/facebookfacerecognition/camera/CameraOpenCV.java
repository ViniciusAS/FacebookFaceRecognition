package facebookfacerecognition.camera;

import facerecognition.opencv.FaceRecognition;
import static facerecognition.opencv.FaceRecognition.mat2Image;
import javafx.animation.AnimationTimer;
import javafx.scene.image.Image;
import org.opencv.core.Mat;
import org.opencv.videoio.VideoCapture;

/**
 *
 * @author Vinicius Santos
 */
public class CameraOpenCV extends ObservableCamera implements Runnable {

    private Thread thread;
    
    private final AnimationTimer timer;
    
    private VideoCapture videoCapture;
    
    private Image image;
    private final Mat mat;
    
    public CameraOpenCV() {
        mat = new Mat();
        timer = new AnimationTimer() {
            @Override public void handle(long l)
            {
                captureImage();
            }
        };
    }
    
    private void captureImage()
    {
        videoCapture.read(mat);   
        image = mat2Image(mat);
        this.setChanged();
        this.notifyObservers();
    }
    
    
    @Override
    public void start(){
        thread = new Thread(this);
        thread.start();
    }
    
    @Override
    public void run(){
        videoCapture = FaceRecognition.newVideoCapture();
        timer.start();
    }
    
    @Override
    public void stop(){
        timer.stop();
        videoCapture.release();
    }
    
    @Override
    public Image getImage(){
        return this.image;
    }
    
    public Mat getMat(){
        return this.mat;
    }
    
}
