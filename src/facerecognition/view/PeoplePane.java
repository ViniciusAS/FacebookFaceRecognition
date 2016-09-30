package facerecognition.view;

import java.util.LinkedList;
import java.util.List;
import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.image.WritableImage;
import javafx.scene.layout.HBox;
import org.opencv.core.Rect;

/**
 *
 * @author Vinicius Santos
 */
public class PeoplePane extends HBox implements CameraPane.OnFaceDetectionListener {

    public PeoplePane() {
        init();
    }
    
    public static double HEIGHT = 100;
    
    private void init(){
        this.setMinHeight(HEIGHT);
    }

    private Node getImageView(Image image, Rect rect){
        WritableImage wi = new WritableImage(
            image.getPixelReader(),
            rect.x, rect.y,
            rect.width, rect.height
        );
        ImageView imageView = new ImageView(wi);
        imageView.setPreserveRatio(false);
        imageView.setFitHeight(HEIGHT);
        imageView.setFitWidth(HEIGHT);
        imageView.setSmooth(true);
        return imageView;
    }
    
    private void setFaces(Image image, List<Rect> rects){
        List<Node> images = new LinkedList<>();
        for (Rect rect : rects){
            images.add( getImageView(image, rect) );
        }
        Platform.runLater(() -> {
            PeoplePane.this.getChildren().setAll(images);
        });
    }
    
    private static int cont = 0;
    @Override
    public void facesDetected(Image image, List<Rect> rects) {
        if ( cont++%3 == 0 ){
            new Thread(() ->
                {
                    setFaces(image, rects);
                }
            ).start();
        }
    }

}
