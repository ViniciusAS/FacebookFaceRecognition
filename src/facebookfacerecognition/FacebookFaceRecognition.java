package facebookfacerecognition;

import javafx.application.Application;
import javafx.stage.Stage;
import facerecognition.gui.FXGUI;
import facerecognition.gui.PeoplePane;
import java.util.List;
import javafx.scene.image.Image;

/**
 *
 * @author viniciusas
 */
public class FacebookFaceRecognition extends  Application{


    @Override
    public void start(Stage stage) throws Exception {
        FXGUI fxgui = new FXGUI(stage);
        PeoplePane peoplePane = fxgui.getPeoplePane();
        peoplePane.setOnPeopleNodesAddedListener(new OnPeopleNodesChangedListener());
    }
    
    private class OnPeopleNodesChangedListener implements PeoplePane.OnPeopleNodesChangeListener {

        @Override
        public void peopleNodesAdded(List<Person> people) {
            recognize(people);
        }

        @Override
        public void personNodeClicked(Person person) {
            // do something, like open facebook page
        }
        
    }
    
    private void recognize(List<Person> people){
        
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        FacebookFaceRecognition.launch();
        
    }
    
}