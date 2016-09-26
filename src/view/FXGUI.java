package view;

import facebookfacerecognition.FaceRecognition;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

/**
 *
 * @author Vinicius Santos
 */
public class FXGUI extends BorderPane {

    private final Stage stage;
    private final Scene scene;
    private final CameraPane cameraPane;
    private final PeoplePane peoplePane;
    
    public FXGUI(Stage stage)
    {
        this.scene = new Scene(this);
        this.stage = stage;
        this.stage.setScene(scene);
        this.cameraPane = new CameraPane();
        this.peoplePane = new PeoplePane();
        initialize();
    }
    
    private void initialize()
    {
        setCenter( cameraPane );
        setBottom( peoplePane );
        
        stage.setMinHeight( 800 );
        stage.setMinWidth(  600 );
        
        Platform.runLater(() -> {
            stage.show();
        });
        
        stage.setOnCloseRequest((WindowEvent t) -> {
            FaceRecognition.getInstance().stop();
        });
    }
    
    
}
