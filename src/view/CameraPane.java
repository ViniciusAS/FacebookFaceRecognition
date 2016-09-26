package view;

import facebookfacerecognition.FaceRecognition;
import javafx.application.Platform;
import javafx.scene.Node;
import javafx.scene.layout.StackPane;

/**
 *
 * @author Vinicius Santos
 */
public class CameraPane extends StackPane {

    public CameraPane() {
        
        this.setMinWidth(500);
        this.setMinHeight(400);
        
        new Thread(() -> {
            Node node = FaceRecognition.getInstance().getNode();
            Platform.runLater(() -> {
                this.getChildren().add( node );
            });
        }).start();
        
    }
    
    
    
}
