package facebookfacerecognition;

import javafx.application.Application;
import javafx.stage.Stage;
import facerecognition.view.FXGUI;

/**
 *
 * @author viniciusas
 */
public class FacebookFaceRecognition extends  Application{


    @Override
    public void start(Stage stage) throws Exception {
        FXGUI fxgui = new FXGUI(stage);
        
    }
    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        FacebookFaceRecognition.launch();
        
    }
    
}