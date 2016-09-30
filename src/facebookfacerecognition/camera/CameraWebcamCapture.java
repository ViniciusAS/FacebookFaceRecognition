package facebookfacerecognition.camera;

import com.github.sarxos.webcam.Webcam;
import java.awt.Dimension;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import javafx.animation.AnimationTimer;
import javafx.scene.image.Image;
import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import org.opencv.core.CvType;
import org.opencv.core.Mat;


/**
 *
 * @author Vinicius Santos
 */
public class CameraWebcamCapture extends ObservableCamera {

    private Image image;
    private Mat mat;
    
    private final Webcam webcam;
    private final AnimationTimer timer;
    
    public CameraWebcamCapture() {
        webcam = Webcam.getDefault();
        webcam.setViewSize(new Dimension( 640, 480 ));
        timer = new AnimationTimer() {
            @Override public void handle(long l)
            {
                captureImage();
            }
        };
    }
    
    private void captureImage(){
        BufferedImage bf = webcam.getImage();
        WritableImage wr = null;
        wr = new WritableImage(bf.getWidth(), bf.getHeight());
        PixelWriter pw = wr.getPixelWriter();
        for (int x = 0; x < bf.getWidth(); x++) {
            for (int y = 0; y < bf.getHeight(); y++) {
                pw.setArgb(x, y, bf.getRGB(x, y));
            }
        }
        
        this.image = (Image) wr;
        
        byte[] pixels = ((DataBufferByte) bf.getRaster().getDataBuffer()).getData();

        Mat matImage = new Mat(bf.getHeight(), bf.getWidth(), CvType.CV_8UC3);
        matImage.put(0, 0, pixels);
        
        this.mat = matImage;
        
        this.setChanged();
        this.notifyObservers();
    }
    
    @Override
    public void start() {
        webcam.open(true);
        timer.start();
    }

    @Override
    public void stop() {
        webcam.close();
        timer.stop();
    }

    @Override
    public Image getImage() {
        return image;
    }

    @Override
    public Mat getMat() {
        return mat;
    }
    
}
