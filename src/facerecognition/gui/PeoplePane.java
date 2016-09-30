package facerecognition.gui;

import facebookfacerecognition.Person;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.image.WritableImage;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import org.opencv.core.Rect;

/**
 *
 * @author Vinicius Santos
 */
public class PeoplePane extends HBox implements CameraPane.OnFaceDetectionListener {

    private final List<Person> peopleImages;
    private OnPeopleNodesChangeListener changeListener;
    
    public PeoplePane() {
        peopleImages = new ArrayList<>();
        changeListener = null;
        init();
    }
    
    public static double HEIGHT = 100;
    
    private void init(){
        this.setMinHeight(HEIGHT);
    }

    private Node createPersonView(Image image, Rect rect){
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
        
        Person person = new Person(image);
        peopleImages.add(person);
        
        Label personName = new Label();
        personName.setTextFill(Paint.valueOf("#00FF00"));
        personName.setFont(Font.font(16));
        personName.textProperty().bind(person.nameProperty());
        
        StackPane personPane = new StackPane( imageView, personName );
        personPane.setAlignment(Pos.TOP_CENTER);
        personPane.setOnMouseClicked((MouseEvent t) -> {
            if ( changeListener != null ){
                changeListener.personNodeClicked(person);
            }
        });
        return personPane;
    }
    
    private void setFaces(Image image, List<Rect> rects){
        List<Node> images = new LinkedList<>();
        for (Rect rect : rects){
            images.add( createPersonView(image, rect) );
        }
        Platform.runLater(() -> {
            PeoplePane.this.getChildren().setAll(images);
        });
    }
    
    private static int cont = 0;
    @Override
    public void facesDetected(Image image, List<Rect> rects) {
        if ( cont++%10 == 0 ){
            new Thread(() ->
                {
                    this.peopleImages.clear();
                    setFaces(image, rects);
                    if ( changeListener != null ) {
                        changeListener.peopleNodesAdded(this.peopleImages);
                    }
                }
            ).start();
        }
    
    }
    
    public void setOnPeopleNodesAddedListener(OnPeopleNodesChangeListener changeListener){
        this.changeListener = changeListener;
    }
    
    public interface OnPeopleNodesChangeListener
    {
        void peopleNodesAdded(List<Person> people);
        void personNodeClicked(Person person);
    }
    
}
