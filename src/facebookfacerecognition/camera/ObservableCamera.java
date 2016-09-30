package facebookfacerecognition.camera;

import java.util.Observable;
import javafx.scene.image.Image;
import org.opencv.core.Mat;

/**
 *
 * @author Vinicius Santos
 */
public abstract class ObservableCamera extends Observable {
    
    public abstract void start();
    
    public abstract void stop();
    
    public abstract Image getImage();
    
    public abstract Mat getMat();
    
}
