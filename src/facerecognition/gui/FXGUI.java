package facerecognition.gui;

import facebookfacerecognition.camera.CameraOpenCV;
import facebookfacerecognition.camera.CameraWebcamCapture;
import facebookfacerecognition.camera.ObservableCamera;
import javafx.application.Platform;
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
    
    private final ObservableCamera cameraSubject;
    
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
        
        cameraSubject = new CameraWebcamCapture();
        cameraSubject.addObserver(cameraPane);
        
        cameraPane.addOnFaceDetectionListener(peoplePane);
        cameraSubject.start();
    }
    
    private void initialize()
    {
        setCenter( cameraPane );
        setBottom( peoplePane );
        
        stage.setMinWidth(  800 );
        stage.setMinHeight( 600 );
        
//        stage.setFullScreen(true);
        
        stage.setOnCloseRequest((WindowEvent t) -> {
            cameraSubject.stop();
        });
        
        
        Platform.runLater(() ->
        {
            stage.show();
        });
    }

    public PeoplePane getPeoplePane() {
        return peoplePane;
    }
    
}
